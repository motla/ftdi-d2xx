#include <stdlib.h>
#include <string.h>

#include "api/FTDI_Device.h"
#include "api/FTDI_Device_close.h"
#include "api/FTDI_Device_read.h"
#include "api/FTDI_Device_setBaudRate.h"
#include "api/FTDI_Device_setDataCharacteristics.h"
#include "api/FTDI_Device_write.h"
#include "utils.h"


// Getter for is_open property
static napi_value is_open(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Return boolean if ftHandle exists
  napi_value handle_is_open;
  utils_check(napi_get_boolean(env, instance_data->ftHandle != NULL, &handle_is_open));
  return handle_is_open;
}

// Getter for info property
static napi_value get_info(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", "deadobj")) return NULL;

  // Get info from FTDI (this is not async but hopefully the data has already been retrieved...)
  FT_DEVICE ftDevice;
  DWORD deviceID;
  char SerialNumber[16];
  char Description[64];
  utils_check(FT_GetDeviceInfo(instance_data->ftHandle, &ftDevice, &deviceID, SerialNumber, Description, NULL));

  // Convert values to JavaScript
  napi_value serial_number, description, type, usb_vid, usb_pid;
  utils_check(napi_create_string_utf8(env, SerialNumber, NAPI_AUTO_LENGTH, &serial_number));
  utils_check(napi_create_string_utf8(env, Description, NAPI_AUTO_LENGTH, &description));
  type = utils_ft_device_to_js_string(env, ftDevice);
  utils_check(napi_create_uint32(env, deviceID >> 16, &usb_vid));
  utils_check(napi_create_uint32(env, deviceID & 0xFFFF, &usb_pid));

  // Return JavaScript info object
  napi_value info_object;
  const napi_property_descriptor props[] = {
    //{ "serial_number", NULL, NULL, NULL, NULL, serial_number, napi_enumerable, NULL }, // omit this as it is already in the constructor
    { "description", NULL, NULL, NULL, NULL, description, napi_enumerable, NULL },
    { "type", NULL, NULL, NULL, NULL, type, napi_enumerable, NULL },
    { "usb_vid", NULL, NULL, NULL, NULL, usb_vid, napi_enumerable, NULL },
    { "usb_pid", NULL, NULL, NULL, NULL, usb_pid, napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  utils_check(napi_create_object(env, &info_object));
  utils_check(napi_define_properties(env, info_object, nb_props, props));
  return info_object;
}


// Utility function to free instance data before it is deleted
static void finalize_cb(napi_env env, void* finalize_data, void* finalize_hint) {
  (void) env, (void) finalize_hint; // hide unused parameter warning
  device_instance_data_t* instance_data = (device_instance_data_t*)finalize_data;

  // Try to close FTDI device now that its device object is deleted
  if(instance_data->ftHandle) {
    FT_Close(instance_data->ftHandle);
  }

  // Free class instance data
  free(instance_data);
}


// Class constructor (runs either the class function is called using `new` or not)
static napi_value constructor(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to the instance of the class and get `argc`/`argv` passed to the constructor
  size_t argc = 1; // size of the argv buffer
  napi_value this_arg, argv[argc];
  utils_check(napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL));
  if(utils_check(argc < 1)) return NULL; // check that all expected arguments were passed

  // Add instance properties
  const napi_property_descriptor props[] = {
    // the first argument passed to the constructor contains the SerialNumber
    { "serial_number", NULL, NULL, NULL, NULL, argv[0], napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  utils_check(napi_define_properties(env, this_arg, nb_props, props));

  // Create and wrap C instance data containing the FTDI device handle that will be set by calling `device_set_instance_handler()`
  device_instance_data_t* instance_data = malloc(sizeof(device_instance_data_t)); // allocate memory for instance data
  if(utils_check(instance_data == NULL, "Malloc failed", "malloc")) return NULL;
  memset(instance_data, 0, sizeof(device_instance_data_t)); // initialize instance data to zeros
  utils_check(napi_wrap(env, this_arg, instance_data, finalize_cb, NULL, NULL));

  // Return class instance
  return this_arg;
}

// Called once to initialize class (then to reference it in module data)
void device_initialize_class(napi_env env, napi_value* result) {

  // Define class prototype
  const napi_property_descriptor props[] = {
    { "is_open", NULL, NULL, is_open, NULL, NULL, napi_enumerable, NULL },
    { "info", NULL, NULL, get_info, NULL, NULL, napi_enumerable, NULL },
    { "close", NULL, device_close, NULL, NULL, NULL, napi_enumerable, NULL },
    { "read", NULL, device_read, NULL, NULL, NULL, napi_enumerable, NULL },
    { "write", NULL, device_write, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setBaudRate", NULL, device_setBaudRate, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setDataCharacteristics", NULL, device_setDataCharacteristics, NULL, NULL, NULL, napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);

  // Create class
  utils_check(napi_define_class(env, "FTDI_Device", NAPI_AUTO_LENGTH, constructor, NULL, nb_props, props, result));
}

// Set the ftHandler of opened FTDI device in class instance data
void device_instance_set_handler(napi_env env, napi_value device_instance, FT_HANDLE ftHandle) {
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, device_instance, (void**)(&instance_data)));
  if(utils_check(instance_data == NULL)) return;
  instance_data->ftHandle = ftHandle;
}
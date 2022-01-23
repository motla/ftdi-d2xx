#include <stdlib.h>
#include <string.h>

#include "api/FTDI_Device.h"
#include "utils.h"
#include "error_check.h"

typedef struct {
  FT_HANDLE ftHandle;
} instance_data_t;


// FTDI Device close function
static napi_value close(napi_env env, napi_callback_info info) {
  return NULL;
}

// FTDI Device read function
static napi_value read(napi_env env, napi_callback_info info) {
  return NULL;
}

// FTDI Device write function
static napi_value write(napi_env env, napi_callback_info info) {
  return NULL;
}

// Getter for info property
static napi_value get_info(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data containing FTDI device handle
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  // Get info from FTDI (this is not async but hopefully the data has already been retrieved...)
  FT_DEVICE ftDevice;
  DWORD deviceID;
  char SerialNumber[16];
  char Description[64];
  error_check(env, FT_GetDeviceInfo(instance_data->ftHandle, &ftDevice, &deviceID, SerialNumber, Description, NULL) == FT_OK);

  // Convert values to JavaScript
  napi_value serial_number, description, type, usb_vid, usb_pid;
  error_check(env, napi_create_string_utf8(env, SerialNumber, sizeof(SerialNumber), &serial_number) == napi_ok);
  error_check(env, napi_create_string_utf8(env, Description, sizeof(Description), &description) == napi_ok);
  type = utils_get_device_type_string(env, ftDevice);
  error_check(env, napi_create_uint32(env, deviceID >> 16, &usb_vid) == napi_ok);
  error_check(env, napi_create_uint32(env, deviceID & 0xFFFF, &usb_pid) == napi_ok);

  // Return JavaScript info object
  napi_value info_object;
  const napi_property_descriptor props[] = {
    { "serial_number", NULL, NULL, NULL, NULL, serial_number, napi_enumerable, NULL },
    { "description", NULL, NULL, NULL, NULL, description, napi_enumerable, NULL },
    { "type", NULL, NULL, NULL, NULL, type, napi_enumerable, NULL },
    { "usb_vid", NULL, NULL, NULL, NULL, usb_vid, napi_enumerable, NULL },
    { "usb_pid", NULL, NULL, NULL, NULL, usb_pid, napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  error_check(env, napi_create_object(env, &info_object) == napi_ok);
  error_check(env, napi_define_properties(env, info_object, nb_props, props) == napi_ok);
  return info_object;
}


// Utility function to free instance data before it is deleted
static void finalize_cb(napi_env env, void* finalize_data, void* finalize_hint) {
  free(finalize_data); // free class instance data
}


// Class constructor (runs either the class function is called using `new` or not)
static napi_value constructor(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to the instance of the class and get `argc`/`argv` passed to the constructor
  size_t argc = 1; // size of the buffer
  napi_value this_arg, argv[argc];
  error_check(env, napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL) == napi_ok);
  error_check(env, argc >= 1); // check that all expected arguments were passed

  // Add instance properties
  const napi_property_descriptor props[] = {
    // the first argument passed to the constructor contains the SerialNumber
    { "sn", NULL, NULL, NULL, NULL, argv[0], napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  error_check(env, napi_define_properties(env, this_arg, nb_props, props) == napi_ok);

  // Create and wrap C instance data containing the FTDI device handle that will be set by calling `device_set_instance_handler()`
  instance_data_t* instance_data = malloc(sizeof(instance_data_t)); // allocate memory for instance data
  memset(instance_data, 0, sizeof(instance_data_t)); // initialize instance data to zeros
  error_check(env, napi_wrap(env, this_arg, instance_data, finalize_cb, NULL, NULL) == napi_ok);

  // Return class instance
  return this_arg;
}

// Called once to initialize class (then to reference it in module data)
void device_initialize_class(napi_env env, napi_value* result) {

  // Define class prototype
  const napi_property_descriptor props[] = {
    { "info", NULL, NULL, get_info, NULL, NULL, napi_enumerable, NULL },
    { "close", NULL, close, NULL, NULL, NULL, napi_enumerable, NULL },
    { "read", NULL, read, NULL, NULL, NULL, napi_enumerable, NULL },
    { "write", NULL, write, NULL, NULL, NULL, napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);

  // Create class
  error_check(env, napi_define_class(env, "FTDI_Device", NAPI_AUTO_LENGTH, constructor, NULL, nb_props, props, result) == napi_ok);
}

// Set the ftHandler of opened FTDI device in class instance data
void device_instance_set_handler(napi_env env, napi_value device_instance, FT_HANDLE ftHandle) {
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, device_instance, (void**)(&instance_data)) == napi_ok);
  instance_data->ftHandle = ftHandle;
}
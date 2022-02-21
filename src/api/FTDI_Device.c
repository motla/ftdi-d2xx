#include <stdlib.h>
#include <string.h>

#include "api/FTDI_Device.h"
#include "api/FTDI_Device_close.h"
#include "api/FTDI_Device_getters.h"
#include "api/FTDI_Device_purge.h"
#include "api/FTDI_Device_read.h"
#include "api/FTDI_Device_readEE.h"
#include "api/FTDI_Device_writeEE.h"
#include "api/FTDI_Device_eraseEE.h"
#include "api/FTDI_Device_setBaudRate.h"
#include "api/FTDI_Device_simpleFunctions.h"
#include "api/FTDI_Device_setDataCharacteristics.h"
#include "api/FTDI_Device_setFlowControl.h"
#include "api/FTDI_Device_setTimeouts.h"
#include "api/FTDI_Device_write.h"
#include "utils.h"


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
  #define NB_ARGS 1 // number of expected arguments
  size_t argc = NB_ARGS; // size of the argv buffer
  napi_value this_arg, argv[NB_ARGS];
  utils_check(napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL));
  if(utils_check(argc < NB_ARGS)) return NULL; // check that all expected arguments were passed

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
    // Getters
    { "is_connected", NULL, NULL, device_get_is_connected, NULL, NULL, napi_enumerable, NULL },
    { "info", NULL, NULL, device_get_info, NULL, NULL, napi_enumerable, NULL },
    { "status", NULL, NULL, device_get_status, NULL, NULL, napi_enumerable, NULL },
    { "modem_status", NULL, NULL, device_get_modem_status, NULL, NULL, napi_enumerable, NULL },
    { "driver_version", NULL, NULL, device_get_driver_version, NULL, NULL, napi_enumerable, NULL },

    // Functions
    { "close", NULL, device_close, NULL, NULL, NULL, napi_enumerable, NULL },
    { "read", NULL, device_read, NULL, NULL, NULL, napi_enumerable, NULL },
    { "write", NULL, device_write, NULL, NULL, NULL, napi_enumerable, NULL },
    { "purge", NULL, device_purge, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setBaudRate", NULL, device_setBaudRate, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setDataCharacteristics", NULL, device_setDataCharacteristics, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setTimeouts", NULL, device_setTimeouts, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setFlowControl", NULL, device_setFlowControl, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setDtr", NULL, device_setDtr, NULL, NULL, NULL, napi_enumerable, NULL },
    { "clrDtr", NULL, device_clrDtr, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setRts", NULL, device_setRts, NULL, NULL, NULL, napi_enumerable, NULL },
    { "clrRts", NULL, device_clrRts, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setBreakOn", NULL, device_setBreakOn, NULL, NULL, NULL, napi_enumerable, NULL },
    { "setBreakOff", NULL, device_setBreakOff, NULL, NULL, NULL, napi_enumerable, NULL },
    { "resetDevice", NULL, device_resetDevice, NULL, NULL, NULL, napi_enumerable, NULL },
    { "readEE", NULL, device_readEE, NULL, NULL, NULL, napi_enumerable, NULL },
    { "writeEE", NULL, device_writeEE, NULL, NULL, NULL, napi_enumerable, NULL },
    { "eraseEE", NULL, device_eraseEE, NULL, NULL, NULL, napi_enumerable, NULL },
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
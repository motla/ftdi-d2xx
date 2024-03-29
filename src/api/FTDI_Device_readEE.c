#include <stdlib.h>

#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

typedef struct {
  // Node-API variables
  napi_async_work async_work;
  napi_deferred deferred;

  // Data passed to execute_callback
  device_instance_data_t* instance_data;
  uint32_t address;
  uint16_t value;

  // Data passed to complete_callback
  FT_STATUS ftStatus;

} async_data_t;


// This function runs on a worker thread.
// It has no access to the JavaScript. Only FTDI functions are called here.
static void execute_callback(napi_env env, void* data) {
  (void) env; // hide unused parameter warning
  async_data_t* async_data = (async_data_t*) data;

  // Read from FTDI device EEPROM
  async_data->ftStatus = FT_ReadEE(async_data->instance_data->ftHandle, async_data->address, &(async_data->value));
}


// This function runs on the main thread after `execute_callback` exits.
// JavaScript functions are called here to convert data generated by FTDI.
static void complete_callback(napi_env env, napi_status status, void* data) {
  (void) status; // hide unused parameter warning
  async_data_t* async_data = (async_data_t*) data;

  // Manage FTDI error if any
  utils_check(FT_|async_data->ftStatus);

  // Resolve the JavaScript `Promise`:
  bool is_exception_pending;
  napi_is_exception_pending(env, &is_exception_pending);
  if(is_exception_pending) {
    // If an exception is pending, clear it to prevent Node.js from crashing
    napi_value error;
    napi_get_and_clear_last_exception(env, &error);

    // Instead reject the JavaScript `Promise` with the error
    napi_reject_deferred(env, async_data->deferred, error);

  } else {
    // Else resolve the JavaScript `Promise` with the return value
    napi_value value;
    napi_create_uint32(env, async_data->value, &value);
    napi_resolve_deferred(env, async_data->deferred, value);
  }

  // Clean up the work item associated with this run
  napi_delete_async_work(env, async_data->async_work);

  // Free async instance data structure
  free(async_data);
}


// Create a deferred JavaScript `Promise` and an async queue work item
napi_value device_readEE(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class and `argc`/`argv` passed to the function
  #define NB_ARGS 1 // number of expected arguments
  size_t argc = NB_ARGS; // size of the argv buffer
  napi_value this_arg, argv[NB_ARGS];
  utils_check(napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL));
  if(utils_check(argc < NB_ARGS, "Missing argument", ERR_MISSARG)) return NULL;

  // Check that the EEPROM location argument is a number
  napi_valuetype type;
  utils_check(napi_typeof(env, argv[0], &type));
  if(utils_check(type != napi_number, "EEPROM location must be a number", ERR_WRONGARG)) return NULL;

  // Allocate memory for async instance data structure
  async_data_t* async_data = malloc(sizeof(async_data_t));
  if(utils_check(async_data == NULL, "Malloc failed", ERR_MALLOC)) return NULL;

  // Get the class instance data containing FTDI device handle
  utils_check(napi_unwrap(env, this_arg, (void**)&(async_data->instance_data)));

  // Set the EEPROM location
  utils_check(napi_get_value_uint32(env, argv[0], &(async_data->address)));

  // Create a deferred `Promise` which we will resolve at the completion of the work
  napi_value promise;
  utils_check(napi_create_promise(env, &(async_data->deferred), &promise));

  // Create an async work item, passing in the addon data, which will give the worker thread access to the `Promise`
  napi_value name;
  utils_check(napi_create_string_utf8(env, "deviceReadEE", NAPI_AUTO_LENGTH, &name));
  utils_check(napi_create_async_work(env, NULL, name, execute_callback, complete_callback, async_data, &(async_data->async_work)));

  // Queue the work item for execution
  utils_check(napi_queue_async_work(env, async_data->async_work));

  // This causes created `Promise` to be returned to JavaScript
  return promise;
}

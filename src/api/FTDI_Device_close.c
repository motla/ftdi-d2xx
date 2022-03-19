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

  // Data passed to complete_callback
  FT_STATUS ftStatus;

} async_data_t;


// This function runs on a worker thread.
// It has no access to the JavaScript. Only FTDI functions are called here.
static void execute_callback(napi_env env, void* data) {
  (void) env; // hide unused parameter warning
  async_data_t* async_data = (async_data_t*) data;

  // Abort if there is no device handle
  if(!async_data->instance_data->ftHandle) return;

  // Close FTDI device
  async_data->ftStatus = FT_Close(async_data->instance_data->ftHandle);

  // Clear device handle
  async_data->instance_data->ftHandle = NULL;
}


// This function runs on the main thread after `execute_callback` exits.
// JavaScript functions are called here to convert data generated by FTDI.
static void complete_callback(napi_env env, napi_status status, void* data) {
  (void) status; // hide unused parameter warning
  async_data_t* async_data = (async_data_t*) data;

  // Check for FTDI error if any
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
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    napi_resolve_deferred(env, async_data->deferred, undefined);
  }

  // Clean up the work item associated with this run
  napi_delete_async_work(env, async_data->async_work);

  // Free async instance data structure
  free(async_data);
}


// Create a deferred JavaScript `Promise` and an async queue work item
napi_value device_close(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Allocate memory for async instance data structure
  async_data_t* async_data = malloc(sizeof(async_data_t));
  if(utils_check(async_data == NULL, "Malloc failed", ERR_MALLOC)) return NULL;

  // Initialize async instance data
  async_data->ftStatus = FT_OK;

  // Get the class instance data containing FTDI device handle
  utils_check(napi_unwrap(env, this_arg, (void**)&(async_data->instance_data)));

  // Create a deferred `Promise` which we will resolve at the completion of the work
  napi_value promise;
  utils_check(napi_create_promise(env, &(async_data->deferred), &promise));

  // Create an async work item, passing in the addon data, which will give the worker thread access to the `Promise`
  napi_value name;
  utils_check(napi_create_string_utf8(env, "deviceClose", NAPI_AUTO_LENGTH, &name));
  utils_check(napi_create_async_work(env, NULL, name, execute_callback, complete_callback, async_data, &(async_data->async_work)));

  // Queue the work item for execution
  utils_check(napi_queue_async_work(env, async_data->async_work));

  // This causes created `Promise` to be returned to JavaScript
  return promise;
}

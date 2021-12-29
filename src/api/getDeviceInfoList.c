#include <stdlib.h>

#include "api/getDeviceInfoList.h"
#include "error_check.h"
#include "module_data.h"
#include "ftd2xx.h"


// This function runs on a worker thread
static void execute_callback(napi_env env, void* data) {
  module_data_t* module_data = (module_data_t*) data;
  DWORD nb_devices = 0;

  // Create FTDI device info list
  error_check(env, FT_CreateDeviceInfoList(&nb_devices) == FT_OK);

  // Create JavaScript array that will be returned containing the device list
  error_check(env, napi_create_array(env, &(module_data->return_value)) == napi_ok);

  // Query device info if devices are detected
  if (nb_devices > 0) {

    // Allocate dynamic memory for device info list based on nb_devices
    FT_DEVICE_LIST_INFO_NODE* device_info = (FT_DEVICE_LIST_INFO_NODE*) malloc(sizeof(FT_DEVICE_LIST_INFO_NODE) * nb_devices);
    
    // Fill the allocated memory with the list of device info
    error_check(env, FT_GetDeviceInfoList(device_info, &nb_devices) == FT_OK);

    // For each device of the list
    for (uint32_t i = 0; i < nb_devices; i++) {
      // Create a JavaScript device object
      napi_value obj;
      error_check(env, napi_create_object(env, &obj) == napi_ok);

      // Fill the device object with info and functions
      napi_value SerialNumber, Description;
      error_check(env, napi_create_string_utf8(env, device_info[i].SerialNumber, sizeof(device_info[i].SerialNumber), &SerialNumber) == napi_ok);
      error_check(env, napi_create_string_utf8(env, device_info[i].Description, sizeof(device_info[i].Description), &Description) == napi_ok);
      error_check(env, napi_set_named_property(env, obj, "SerialNumber", SerialNumber) == napi_ok);
      error_check(env, napi_set_named_property(env, obj, "Description", Description) == napi_ok);
      /*
      printf("Dev %d:\n", i);
      printf("  Flags=0x%x\n", device_info[i].Flags);
      printf("  Type=0x%x\n", device_info[i].Type);
      printf("  ID=0x%x\n", device_info[i].ID);
      printf("  LocId=0x%x\n", device_info[i].LocId);
      printf("  SerialNumber=%s\n", device_info[i].SerialNumber);
      printf("  Description=%s\n", device_info[i].Description);
      printf("  ftHandle=0x%x\n", device_info[i].ftHandle);
      */

      // Add object to device list array
      napi_set_element(env, module_data->return_value, i, obj);
    }

    // Free previously allocated memory
    free(device_info);
  }
}


// This function runs on the main thread after `execute_callback` exits
static void complete_callback(napi_env env, napi_status status, void* data) {
  if (status != napi_ok) return;
  module_data_t* module_data = (module_data_t*) data;

  // Resolve the JavaScript Promise with the return value
  error_check(env, napi_resolve_deferred(env, module_data->deferred, module_data->return_value) == napi_ok);

  // Clean up the work item associated with this run
  error_check(env, napi_delete_async_work(env, module_data->async_work) == napi_ok);

  // Set both values to NULL so JavaScript can order a new run of the thread.
  module_data->async_work = NULL;
  module_data->deferred = NULL;
}


// Create a deferred JavaScript Promise and an async queue work item
napi_value getDeviceInfoList(napi_env env, napi_callback_info info) {
  
  // Get the global module data
  module_data_t* module_data;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, NULL, (void**)(&module_data)) == napi_ok);

  // Ensure that no work is currently in progress
  if(module_data->async_work != NULL) napi_throw_error(env, NULL, "Only one work item must exist at a time");

  // Create a deferred promise which we will resolve at the completion of the work
  napi_value promise;
  error_check(env, napi_create_promise(env, &(module_data->deferred), &promise) == napi_ok);

  // Create an async work item, passing in the addon data, which will give the
  // worker thread access to the Promise
  napi_value name;
  error_check(env, napi_create_string_utf8(env, "getDeviceInfoList", NAPI_AUTO_LENGTH, &name) == napi_ok);
  error_check(env, napi_create_async_work(env, NULL, name, execute_callback, complete_callback, module_data, &(module_data->async_work)) == napi_ok);

  // Queue the work item for execution
  error_check(env, napi_queue_async_work(env, module_data->async_work) == napi_ok);

  // This causes created `promise` to be returned to JavaScript
  return promise;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module_data.h"
#include "utils.h"
#include "api/FTDI_Device.h"
#include "api/FTDI_DeviceInfo.h"

// Function to allocate dynamically and initialize the module data structure
module_data_t* allocate_module_data(napi_env env) {
  module_data_t* module_data = malloc(sizeof(module_data_t)); // allocate memory for module data
  if(utils_check(module_data == NULL, "Malloc failed", ERR_MALLOC)) return NULL;
  memset(module_data, 0, sizeof(module_data_t)); // initialize module data to zeros

  // Initialize FTDI_DeviceInfo class (make it persistent by referencing it to avoid automatic garbage collection)
  napi_value device_info_class;
  device_info_initialize_class(env, &device_info_class);
  utils_check(napi_create_reference(env, device_info_class, 1, &(module_data->device_info_class_ref)));

  // Initialize FTDI_Device class (make it persistent by referencing it to avoid automatic garbage collection)
  napi_value device_class;
  device_initialize_class(env, &device_class);
  utils_check(napi_create_reference(env, device_class, 1, &(module_data->device_class_ref)));

  return module_data;
}

// Handler function to free the module data before module is unloaded
void free_module_data(napi_env env, void* data, void* hint) {
  (void) env, (void) hint; // hide unused parameter warning
  module_data_t* module_data = (module_data_t*) data;
  free(module_data);
}
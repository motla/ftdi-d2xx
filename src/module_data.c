#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module_data.h"
#include "error_check.h"

// Function to allocate dynamically and initialize the module data structure
module_data_t* allocate_module_data(napi_env env) {
  module_data_t* module_data = malloc(sizeof(module_data_t));
  memset(module_data, 0, sizeof(module_data_t));

  // Initialize devices array (we make it persistent by referencing it to avoid automatic garbage collection)
  napi_value devices_array;
  error_check(env, napi_create_array(env, &devices_array) == napi_ok);
  error_check(env, napi_create_reference(env, devices_array, 1, &(module_data->devices_array_ref)) == napi_ok);

  return module_data;
}

// Handler function to free the module data before module is unloaded
void free_module_data(napi_env env, void* data, void* hint) {
  (void) hint; // hide unused parameter warning
  module_data_t* module_data = (module_data_t*) data;
  error_check(env, module_data->async_work == NULL);
  free(module_data);
}
#include <stdlib.h>
#include "module_data.h"
#include "error_check.h"

// Function to allocate dynamically and initialize the module data structure
module_data_t* allocate_module_data(void) {
  module_data_t* module_data = (module_data_t*) malloc(sizeof(module_data_t));
  module_data->async_work = NULL;
  module_data->deferred = NULL;
  return module_data;
}

// Handler function to free the module data before module is unloaded
void free_module_data(napi_env env, void* data, void* hint) {
  module_data_t* module_data = (module_data_t*) data;
  error_check(env, module_data->async_work == NULL);
  free(module_data);
}
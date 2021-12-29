#ifndef module_data_h
#define module_data_h

#include <node_api.h>

// Structure for dynamically allocated module data (needed for asynchronous work)
typedef struct {
  napi_async_work async_work;
  napi_deferred deferred;
  napi_value return_value;
} module_data_t;

// Function to allocate dynamically and initialize the module data structure
module_data_t* allocate_module_data(void);

// Handler function to free the module data before module is unloaded
void free_module_data(napi_env env, void* data, void* hint);

#endif
#ifndef module_data_h
#define module_data_h

#include <node_api.h>

// Structure for dynamically allocated module data (needed for asynchronous work)
typedef struct {
  // Node API variables
  napi_async_work async_work;
  napi_deferred deferred;

  // Representing the JavaScript constructor function for the Device class
  napi_ref device_class_ref;

  // Reference to the JavaScript Array list of detected FTDI devices
  napi_ref devices_array_ref;

  // Variables used to transfer result from the worker to the main thread
  uint32_t count_buffer;
  void* return_buffer;
} module_data_t;

// Function to allocate dynamically and initialize the module data structure
module_data_t* allocate_module_data(napi_env env);

// Handler function to free the module data before module is unloaded
void free_module_data(napi_env env, void* data, void* hint);

#endif
#ifndef module_data_h
#define module_data_h

#include <node_api.h>
#include "ftd2xx.h"

// Structure for dynamically allocated module data
typedef struct {
  
  // Reference to JavaScript constructor function for the FTDI_DeviceInfo class
  napi_ref device_info_class_ref;
  // Reference to JavaScript constructor function for the FTDI_Device class
  napi_ref device_class_ref;

} module_data_t;

// Function to allocate dynamically and initialize the module data structure
module_data_t* allocate_module_data(napi_env env);

// Handler function to free the module data before module is unloaded
void free_module_data(napi_env env, void* data, void* hint);

#endif
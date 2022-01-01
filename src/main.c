#include <node_api.h>

#include "error_check.h"
#include "module_data.h"
#include "api/listDevices.h"

// Function called to initialize the module
static napi_value init_module(napi_env env, napi_value exports) {
  
  // Create the module data structure
  module_data_t* module_data = allocate_module_data(env);

  // Free module data when the module is unloaded
  error_check(env, napi_wrap(env, exports, module_data, free_module_data, NULL, NULL) == napi_ok);

  // Declare JavaScript module object properties and symbol
  napi_property_descriptor props[] = {
    { "listDevices", NULL, listDevices, NULL, NULL, NULL, napi_enumerable, module_data },
  };

  // Add these properties to the `exports` variable
  size_t nb_props = sizeof(props)/sizeof(napi_property_descriptor);
  error_check(env, napi_define_properties(env, exports, nb_props, props) == napi_ok);
  
  return exports;
}

NAPI_MODULE(ftdi_d2xx, init_module)

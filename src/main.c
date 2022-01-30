#include <node_api.h>

#include "utils.h"
#include "module_data.h"
#include "api/getDeviceInfoList.h"
#include "api/openDevice.h"

// Function called to initialize the module
static napi_value init_module(napi_env env, napi_value exports) {
  
  // Create the module data structure, initialize global classes
  module_data_t* module_data = allocate_module_data(env);

  // Wrap the module data to `exports`, and free it when the module is unloaded
  utils_check(napi_wrap(env, exports, module_data, free_module_data, NULL, NULL));

  // Get JavaScript global Symbol.toStringTag
  napi_value global, symbol, symbol_to_string_tag;
  utils_check(napi_get_global(env, &global));
  utils_check(napi_get_named_property(env, global, "Symbol", &symbol));
  utils_check(napi_get_named_property(env, symbol, "toStringTag", &symbol_to_string_tag));

  // Declare JavaScript tag name
  napi_value tag_name;
  utils_check(napi_create_string_utf8(env, "FTDI D2XX Driver", NAPI_AUTO_LENGTH, &tag_name));

  // Declare properties for JavaScript `exports` object
  const napi_property_descriptor props[] = {
    { "getDeviceInfoList", NULL, getDeviceInfoList, NULL, NULL, NULL, napi_enumerable, module_data },
    { "openDevice", NULL, openDevice, NULL, NULL, NULL, napi_enumerable, module_data },
    { NULL, symbol_to_string_tag, NULL, NULL, NULL, tag_name, napi_enumerable, NULL }
  };

  // Write properties to JavaScript `exports` object
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  utils_check(napi_define_properties(env, exports, nb_props, props));
  
  return exports;
}

NAPI_MODULE(ftdi_d2xx, init_module)

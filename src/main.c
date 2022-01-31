#include <node_api.h>

#include "api/getDeviceInfoList.h"
#include "api/openDevice.h"
#include "api/setVIDPID.h"
#include "api/getVIDPID.h"
#include "constants.h"
#include "module_data.h"
#include "ftd2xx.h"
#include "utils.h"

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
  
  // Declare constants
  constants_t constants = initialize_constants(env);

  // Declare properties for JavaScript `exports` object
  const napi_property_descriptor props[] = {
    // Functions
    { "getDeviceInfoList", NULL, getDeviceInfoList, NULL, NULL, NULL, napi_enumerable, module_data },
    { "openDevice", NULL, openDevice, NULL, NULL, NULL, napi_enumerable, module_data },
    { "setVIDPID", NULL, setVIDPID, NULL, NULL, NULL, napi_enumerable, NULL },
    { "getVIDPID", NULL, getVIDPID, NULL, NULL, NULL, napi_enumerable, NULL },

    // Constants
    { "FT_BITS_8", NULL, NULL, NULL, NULL, constants.bits_8, napi_default, NULL },
    { "FT_BITS_7", NULL, NULL, NULL, NULL, constants.bits_7, napi_default, NULL },
    { "FT_STOP_BITS_1", NULL, NULL, NULL, NULL, constants.stop_bits_1, napi_default, NULL },
    { "FT_STOP_BITS_2", NULL, NULL, NULL, NULL, constants.stop_bits_2, napi_default, NULL },
    { "FT_PARITY_NONE", NULL, NULL, NULL, NULL, constants.parity_none, napi_default, NULL },
    { "FT_PARITY_ODD", NULL, NULL, NULL, NULL, constants.parity_odd, napi_default, NULL },
    { "FT_PARITY_EVEN", NULL, NULL, NULL, NULL, constants.parity_even, napi_default, NULL },
    { "FT_PARITY_MARK", NULL, NULL, NULL, NULL, constants.parity_mark, napi_default, NULL },
    { "FT_PARITY_SPACE", NULL, NULL, NULL, NULL, constants.parity_space, napi_default, NULL },
    { "FT_FLOW_NONE", NULL, NULL, NULL, NULL, constants.flow_none, napi_default, NULL },
    { "FT_FLOW_RTS_CTS", NULL, NULL, NULL, NULL, constants.flow_rts_cts, napi_default, NULL },
    { "FT_FLOW_DTR_DSR", NULL, NULL, NULL, NULL, constants.flow_dtr_dsr, napi_default, NULL },
    { "FT_FLOW_XON_XOFF", NULL, NULL, NULL, NULL, constants.flow_xon_xoff, napi_default, NULL },
    { "FT_PURGE_RX", NULL, NULL, NULL, NULL, constants.purge_rx, napi_default, NULL },
    { "FT_PURGE_TX", NULL, NULL, NULL, NULL, constants.purge_tx, napi_default, NULL },

    // Symbol.toStringTag
    { NULL, symbol_to_string_tag, NULL, NULL, NULL, tag_name, napi_enumerable, NULL }
  };

  // Write properties to JavaScript `exports` object
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  utils_check(napi_define_properties(env, exports, nb_props, props));
  
  return exports;
}

NAPI_MODULE(ftdi_d2xx, init_module)

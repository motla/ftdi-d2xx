#include <stdio.h>
#include <node_api.h>

#include "api/getDeviceInfoList.h"
#include "api/openDevice.h"
#include "api/setVIDPID.h"
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

  // Get FTDI library version
  DWORD DLLVersion;
  char buffer[16];
  napi_value version;
  utils_check(FT_GetLibraryVersion(&DLLVersion));
  snprintf(buffer, 16, "%u.%02u.%02u", (DLLVersion >> 16) & 0xFF, (DLLVersion >> 8) & 0xFF, (DLLVersion) & 0xFF);
  utils_check(napi_create_string_utf8(env, buffer, NAPI_AUTO_LENGTH, &version));

  // Declare properties for JavaScript `exports` object
  const napi_property_descriptor props[] = {
    // Functions
    { "getDeviceInfoList", NULL, getDeviceInfoList, NULL, NULL, NULL, napi_enumerable, module_data },
    { "openDevice", NULL, openDevice, NULL, NULL, NULL, napi_enumerable, module_data },
    { "setVIDPID", NULL, setVIDPID, NULL, NULL, NULL, napi_enumerable, NULL },

    // Constants
    { "library_version", NULL, NULL, NULL, NULL, version, napi_default, NULL },
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
    { "FT_BITMODE_RESET", NULL, NULL, NULL, NULL, constants.bit_mode_reset, napi_default, NULL },
    { "FT_BITMODE_ASYNC_BITBANG", NULL, NULL, NULL, NULL, constants.bit_mode_async_bitbang, napi_default, NULL },
    { "FT_BITMODE_MPSSE", NULL, NULL, NULL, NULL, constants.bit_mode_mpsse, napi_default, NULL },
    { "FT_BITMODE_SYNC_BITBANG", NULL, NULL, NULL, NULL, constants.bit_mode_sync_bitbang, napi_default, NULL },
    { "FT_BITMODE_MCU_HOST", NULL, NULL, NULL, NULL, constants.bit_mode_mcu_host, napi_default, NULL },
    { "FT_BITMODE_FAST_SERIAL", NULL, NULL, NULL, NULL, constants.bit_mode_fast_serial, napi_default, NULL },
    { "FT_BITMODE_CBUS_BITBANG", NULL, NULL, NULL, NULL, constants.bit_mode_cbus_bitbang, napi_default, NULL },
    { "FT_BITMODE_SYNC_FIFO", NULL, NULL, NULL, NULL, constants.bit_mode_sync_fifo, napi_default, NULL },

    // Symbol.toStringTag
    { NULL, symbol_to_string_tag, NULL, NULL, NULL, tag_name, napi_enumerable, NULL }
  };

  // Write properties to JavaScript `exports` object
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  utils_check(napi_define_properties(env, exports, nb_props, props));
  
  return exports;
}

NAPI_MODULE(ftdi_d2xx, init_module)

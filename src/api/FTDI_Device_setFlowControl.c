#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

napi_value device_setFlowControl(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class and `argc`/`argv` passed to the function
  #define NB_ARGS 3 // number of expected arguments
  size_t argc = NB_ARGS; // size of the argv buffer
  napi_value this_arg, argv[NB_ARGS];
  utils_check(napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL));
  if(utils_check(argc < NB_ARGS, "Missing argument", ERR_MISSARG)) return NULL;

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", ERR_DEADOBJ)) return NULL;

  // Check arguments, and convert JavaScript values to C values
  uint32_t flow, xon = 0, xoff = 0;
  if(utils_check(
      ((napi_get_value_uint32(env, argv[0], &flow) != napi_ok) ||
        (flow != FT_FLOW_NONE && flow != FT_FLOW_RTS_CTS && flow != FT_FLOW_DTR_DSR && flow != FT_FLOW_XON_XOFF)),
      "Flow control must be FT_FLOW_NONE, FT_FLOW_RTS_CTS, FT_FLOW_DTR_DSR or FT_FLOW_XON_XOFF", ERR_WRONGARG)) return NULL;
  if(flow == FT_FLOW_XON_XOFF) {
    if(utils_check(((napi_get_value_uint32(env, argv[1], &xon) != napi_ok) || xon > 0xFF),
        "Byte to signal Xon must be a byte number (0-255)", ERR_WRONGARG)) return NULL;
    if(utils_check(((napi_get_value_uint32(env, argv[2], &xoff) != napi_ok) || xoff > 0xFF),
        "Byte to signal Xoff must be a byte number (0-255)", ERR_WRONGARG)) return NULL;
  }

  // Update FTDI device
  utils_check(FT_SetFlowControl(instance_data->ftHandle, (USHORT)flow, (UCHAR)xon, (UCHAR)xoff));

  return NULL;
}

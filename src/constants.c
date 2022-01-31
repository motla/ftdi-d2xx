#include "constants.h"
#include "utils.h"
#include "ftd2xx.h"

constants_t initialize_constants(napi_env env) {
  constants_t constants = { 0 };
  utils_check(napi_create_uint32(env, FT_BITS_8, &(constants.bits_8)));
  utils_check(napi_create_uint32(env, FT_BITS_7, &(constants.bits_7)));
  utils_check(napi_create_uint32(env, FT_STOP_BITS_1, &(constants.stop_bits_1)));
  utils_check(napi_create_uint32(env, FT_STOP_BITS_2, &(constants.stop_bits_2)));
  utils_check(napi_create_uint32(env, FT_PARITY_NONE, &(constants.parity_none)));
  utils_check(napi_create_uint32(env, FT_PARITY_ODD, &(constants.parity_odd)));
  utils_check(napi_create_uint32(env, FT_PARITY_EVEN, &(constants.parity_even)));
  utils_check(napi_create_uint32(env, FT_PARITY_MARK, &(constants.parity_mark)));
  utils_check(napi_create_uint32(env, FT_PARITY_SPACE, &(constants.parity_space)));
  utils_check(napi_create_uint32(env, FT_FLOW_NONE, &(constants.flow_none)));
  utils_check(napi_create_uint32(env, FT_FLOW_RTS_CTS, &(constants.flow_rts_cts)));
  utils_check(napi_create_uint32(env, FT_FLOW_DTR_DSR, &(constants.flow_dtr_dsr)));
  utils_check(napi_create_uint32(env, FT_FLOW_XON_XOFF, &(constants.flow_xon_xoff)));
  utils_check(napi_create_uint32(env, FT_PURGE_RX, &(constants.purge_rx)));
  utils_check(napi_create_uint32(env, FT_PURGE_TX, &(constants.purge_tx)));
  return constants;
}
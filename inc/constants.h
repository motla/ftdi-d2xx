#ifndef constants_h
#define constants_h

#include <node_api.h>

typedef struct {
  napi_value bits_8;
  napi_value bits_7;
  napi_value stop_bits_1;
  napi_value stop_bits_2;
  napi_value parity_none;
  napi_value parity_odd;
  napi_value parity_even;
  napi_value parity_mark;
  napi_value parity_space;
  napi_value flow_none;
  napi_value flow_rts_cts;
  napi_value flow_dtr_dsr;
  napi_value flow_xon_xoff;
  napi_value purge_rx;
  napi_value purge_tx;
  napi_value bit_mode_reset;
  napi_value bit_mode_async_bitbang;
  napi_value bit_mode_mpsse;
  napi_value bit_mode_sync_bitbang;
  napi_value bit_mode_mcu_host;
  napi_value bit_mode_fast_serial;
  napi_value bit_mode_cbus_bitbang;
  napi_value bit_mode_sync_fifo;
} constants_t;

constants_t initialize_constants(napi_env env);

#endif
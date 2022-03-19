#ifndef FTDI_Device_h
#define FTDI_Device_h

#include <node_api.h>
#include "ftd2xx.h"

typedef struct {
  FT_HANDLE ftHandle;
} device_instance_data_t;

void device_initialize_class(napi_env env, napi_value* result);
void device_instance_set_handler(napi_env env, napi_value device_instance, FT_HANDLE ftHandle);

// Device getters
napi_value device_get_is_connected(napi_env env, napi_callback_info info);
napi_value device_get_info(napi_env env, napi_callback_info info);
napi_value device_get_modem_status(napi_env env, napi_callback_info info);
napi_value device_get_driver_version(napi_env env, napi_callback_info info);
napi_value device_get_status(napi_env env, napi_callback_info info);
napi_value device_get_bit_mode(napi_env env, napi_callback_info info);
napi_value device_get_latency_timer(napi_env env, napi_callback_info info);

// Device functions
napi_value device_close(napi_env env, napi_callback_info info);
napi_value device_clrDtr(napi_env env, napi_callback_info info);
napi_value device_clrRts(napi_env env, napi_callback_info info);
napi_value device_eraseEE(napi_env env, napi_callback_info info);
napi_value device_purge(napi_env env, napi_callback_info info);
napi_value device_read(napi_env env, napi_callback_info info);
napi_value device_readEE(napi_env env, napi_callback_info info);
napi_value device_setBaudRate(napi_env env, napi_callback_info info);
napi_value device_setBitMode(napi_env env, napi_callback_info info);
napi_value device_setDataCharacteristics(napi_env env, napi_callback_info info);
napi_value device_setFlowControl(napi_env env, napi_callback_info info);
napi_value device_setLatencyTimer(napi_env env, napi_callback_info info);
napi_value device_setTimeouts(napi_env env, napi_callback_info info);
napi_value device_setUSBParameters(napi_env env, napi_callback_info info);
napi_value device_setDtr(napi_env env, napi_callback_info info);
napi_value device_setRts(napi_env env, napi_callback_info info);
napi_value device_setBreakOn(napi_env env, napi_callback_info info);
napi_value device_setBreakOff(napi_env env, napi_callback_info info);
napi_value device_resetDevice(napi_env env, napi_callback_info info);
napi_value device_write(napi_env env, napi_callback_info info);
napi_value device_writeEE(napi_env env, napi_callback_info info);

#endif
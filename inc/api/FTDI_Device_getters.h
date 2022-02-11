#ifndef FTDI_Device_getters_h
#define FTDI_Device_getters_h

#include <node_api.h>

napi_value device_get_is_connected(napi_env env, napi_callback_info info);
napi_value device_get_info(napi_env env, napi_callback_info info);
napi_value device_get_modem_status(napi_env env, napi_callback_info info);
napi_value device_get_driver_version(napi_env env, napi_callback_info info);
napi_value device_get_status(napi_env env, napi_callback_info info);

#endif
#ifndef FTDI_Device_setClrDtrRts_h
#define FTDI_Device_setClrDtrRts_h

#include <node_api.h>

napi_value device_setDtr(napi_env env, napi_callback_info info);
napi_value device_clrDtr(napi_env env, napi_callback_info info);
napi_value device_setRts(napi_env env, napi_callback_info info);
napi_value device_clrRts(napi_env env, napi_callback_info info);

#endif
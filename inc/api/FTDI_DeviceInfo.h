#ifndef FTDI_DeviceInfo_h
#define FTDI_DeviceInfo_h

#include <node_api.h>
#include "ftd2xx.h"

void device_info_initialize_class(napi_env env, napi_value* result);

#endif
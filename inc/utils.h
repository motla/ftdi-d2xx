#ifndef utils_h
#define utils_h

#include "node_api.h"
#include "ftd2xx.h"

napi_value utils_get_device_type_string(napi_env env, FT_DEVICE device);

#endif
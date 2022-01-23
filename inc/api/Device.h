#ifndef device_h
#define device_h

#include <node_api.h>
#include "ftd2xx.h"

void device_initialize_class(napi_env env, napi_value* result);
void device_update_instance_info(napi_env env, napi_value device_object, FT_DEVICE_LIST_INFO_NODE* device_info, bool is_connected);

#endif
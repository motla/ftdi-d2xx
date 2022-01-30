#ifndef FTDI_Device_h
#define FTDI_Device_h

#include <node_api.h>
#include "ftd2xx.h"

typedef struct {
  FT_HANDLE ftHandle;
} device_instance_data_t;

void device_initialize_class(napi_env env, napi_value* result);
void device_instance_set_handler(napi_env env, napi_value device_instance, FT_HANDLE ftHandle);

#endif
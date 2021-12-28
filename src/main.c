#include <assert.h>
#include <node_api.h>

#include <string.h>
#include <stdio.h>
#include "ftd2xx.h"


static napi_value Method(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value world;

  FT_STATUS   ftStatus;
  DWORD       standardDevices = 0;

  char buffer[300] = {0};

  ftStatus = FT_ListDevices(&standardDevices, 
                              NULL, 
                              FT_LIST_NUMBER_ONLY);

  sprintf(buffer, "%d device%s with standard FTDI Vendor and Product Ids detected.\n", (int)standardDevices, standardDevices == 1 ? "" : "s");

  status = napi_create_string_utf8(env, buffer, strlen(buffer), &world);
  assert(status == napi_ok);
  return world;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("hello", Method);
  status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(hello, Init)

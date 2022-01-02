
#include "api/Device.h"
#include "error_check.h"

static napi_value constructor(napi_env env, napi_callback_info info) {
  return NULL;
}

static napi_value open(napi_env env, napi_callback_info info) {
  return NULL;
}

static napi_value close(napi_env env, napi_callback_info info) {
  return NULL;
}

static napi_value read(napi_env env, napi_callback_info info) {
  return NULL;
}

static napi_value write(napi_env env, napi_callback_info info) {
  return NULL;
}

void initialize_device_class(napi_env env, napi_value* result){

  const napi_property_descriptor props[] = {
    { "open", NULL, open, NULL, NULL, NULL, napi_enumerable, NULL },
    { "close", NULL, close, NULL, NULL, NULL, napi_enumerable, NULL },
    { "read", NULL, read, NULL, NULL, NULL, napi_enumerable, NULL },
    { "write", NULL, write, NULL, NULL, NULL, napi_enumerable, NULL },
  };

  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  error_check(env, napi_define_class(env, "Device", NAPI_AUTO_LENGTH, constructor, NULL, nb_props, props, result) == napi_ok);
}
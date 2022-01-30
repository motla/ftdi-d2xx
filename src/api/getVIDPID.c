#include "api/getVIDPID.h"
#include "ftd2xx.h"
#include "utils.h"

napi_value getVIDPID(napi_env env, napi_callback_info info) {

  // Get the current VID/PID combination from FTDI driver
  DWORD vid, pid;
  utils_check(FT_GetVIDPID(&vid, &pid));

  // Convert values to JavaScript
  napi_value vendor_id, product_id;
  utils_check(napi_create_uint32(env, vid, &vendor_id));
  utils_check(napi_create_uint32(env, pid, &product_id));

  // Return JavaScript object containing values
  napi_value object;
  utils_check(napi_create_object(env, &object));
  utils_check(napi_set_named_property(env, object, "vid", vendor_id));
  utils_check(napi_set_named_property(env, object, "pid", product_id));
  return object;
}

#include <stdio.h>
#include "utils.h"
#include "error_check.h"

napi_value utils_get_device_type_string(napi_env env, FT_DEVICE device) {
  char value[32];
  char* value_ptr = value;

  // Get the device type name
  switch (device) {
    case FT_DEVICE_BM: value_ptr = "BM"; break;
    case FT_DEVICE_AM: value_ptr = "AM"; break;
    case FT_DEVICE_100AX: value_ptr = "FT100AX"; break;
    case FT_DEVICE_UNKNOWN: value_ptr = "UNKNOWN"; break;
    case FT_DEVICE_2232C: value_ptr = "FT2232C"; break;
    case FT_DEVICE_232R: value_ptr = "FT232R"; break;
    case FT_DEVICE_2232H: value_ptr = "FT2232H"; break;
    case FT_DEVICE_4232H: value_ptr = "FT4232H"; break;
    case FT_DEVICE_232H: value_ptr = "FT232H"; break;
    case FT_DEVICE_X_SERIES: value_ptr = "X_SERIES"; break;
    case FT_DEVICE_4222H_0: value_ptr = "FT4222H_0"; break;
    case FT_DEVICE_4222H_1_2: value_ptr = "FT4222H_1_2"; break;
    case FT_DEVICE_4222H_3: value_ptr = "FT4222H_3"; break;
    case FT_DEVICE_4222_PROG: value_ptr = "FT4222_PROG"; break;
    case FT_DEVICE_900: value_ptr = "FT900"; break;
    case FT_DEVICE_930: value_ptr = "FT930"; break;
    case FT_DEVICE_UMFTPD3A: value_ptr = "UMFTPD3A"; break;
    case FT_DEVICE_2233HP: value_ptr = "FT2233HP"; break;
    case FT_DEVICE_4233HP: value_ptr = "FT4233HP"; break;
    case FT_DEVICE_2232HP: value_ptr = "FT2232HP"; break;
    case FT_DEVICE_4232HP: value_ptr = "FT4232HP"; break;
    case FT_DEVICE_233HP: value_ptr = "FT233HP"; break;
    case FT_DEVICE_232HP: value_ptr = "FT232HP"; break;
    case FT_DEVICE_2232HA: value_ptr = "FT2232HA"; break;
    case FT_DEVICE_4232HA: value_ptr = "FT4232HA"; break;
    default: snprintf(value, sizeof(value), "UNKNOWN (%u)", device); break;
  }
  
  // Convert to JavaScript string
  napi_value js_value;
  error_check(env, napi_create_string_utf8(env, value_ptr, NAPI_AUTO_LENGTH, &js_value) == napi_ok);
  return js_value;
}
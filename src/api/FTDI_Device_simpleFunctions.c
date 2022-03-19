#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

typedef enum { SET_DTR, CLR_DTR, SET_RTS, CLR_RTS, BREAK_ON, BREAK_OFF, RESET_DEV } type_t;

static napi_value device_simpleFunctions(napi_env env, napi_callback_info info, type_t type) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", ERR_DEADOBJ)) return NULL;

  // Update FTDI device
  switch(type) {
    case SET_DTR: utils_check(FT_SetDtr(instance_data->ftHandle)); break;
    case CLR_DTR: utils_check(FT_ClrDtr(instance_data->ftHandle)); break;
    case SET_RTS: utils_check(FT_SetRts(instance_data->ftHandle)); break;
    case CLR_RTS: utils_check(FT_ClrRts(instance_data->ftHandle)); break;
    case BREAK_ON: utils_check(FT_SetBreakOn(instance_data->ftHandle)); break;
    case BREAK_OFF: utils_check(FT_SetBreakOff(instance_data->ftHandle)); break;
    case RESET_DEV: utils_check(FT_ResetDevice(instance_data->ftHandle)); break;
    default: break;
  }
  return NULL;
}

napi_value device_setDtr(napi_env env, napi_callback_info info) { return device_simpleFunctions(env, info, SET_DTR); }
napi_value device_clrDtr(napi_env env, napi_callback_info info) { return device_simpleFunctions(env, info, CLR_DTR); }
napi_value device_setRts(napi_env env, napi_callback_info info) { return device_simpleFunctions(env, info, SET_RTS); }
napi_value device_clrRts(napi_env env, napi_callback_info info) { return device_simpleFunctions(env, info, CLR_RTS); }
napi_value device_setBreakOn(napi_env env, napi_callback_info info) { return device_simpleFunctions(env, info, BREAK_ON); }
napi_value device_setBreakOff(napi_env env, napi_callback_info info) { return device_simpleFunctions(env, info, BREAK_OFF); }
napi_value device_resetDevice(napi_env env, napi_callback_info info) { return device_simpleFunctions(env, info, RESET_DEV); }
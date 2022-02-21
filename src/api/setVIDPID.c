#include "api/setVIDPID.h"
#include "ftd2xx.h"
#include "utils.h"

napi_value setVIDPID(napi_env env, napi_callback_info info) {
  // Get JavaScript `argc`/`argv` passed to the function
  #define NB_ARGS 2 // number of expected arguments
  size_t argc = NB_ARGS; // size of the argv buffer
  napi_value argv[NB_ARGS];
  utils_check(napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
  if(utils_check(argc < NB_ARGS, "Missing argument", "missarg")) return NULL;

  // Check that the VID/PID arguments are numbers
  napi_valuetype type;
  utils_check(napi_typeof(env, argv[0], &type));
  if(utils_check(type != napi_number, "Vendor ID must be a number", "wrongarg")) return NULL;
  utils_check(napi_typeof(env, argv[1], &type));
  if(utils_check(type != napi_number, "Product ID must be a number", "wrongarg")) return NULL;

  // Convert JavaScript numbers to C values
  uint32_t vid, pid;
  utils_check(napi_get_value_uint32(env, argv[0], &vid));
  utils_check(napi_get_value_uint32(env, argv[1], &pid));

  // Set the custom VID and PID combination to FTDI driver
  #ifdef _WIN32
    utils_check(FT_Reload((WORD)vid, (WORD)pid));
  #else
    utils_check(FT_SetVIDPID((DWORD)vid, (DWORD)pid));
  #endif

  return NULL;
}

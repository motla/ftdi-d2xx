#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

napi_value device_setBaudRate(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class and `argc`/`argv` passed to the function
  #define NB_ARGS 1 // number of expected arguments
  size_t argc = NB_ARGS; // size of the argv buffer
  napi_value this_arg, argv[NB_ARGS];
  utils_check(napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL));
  if(utils_check(argc < NB_ARGS, "Missing argument", ERR_MISSARG)) return NULL;

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", ERR_DEADOBJ)) return NULL;

  // Check arguments, and convert JavaScript values to C values
  uint32_t baud_rate;
  if(utils_check(napi_get_value_uint32(env, argv[0], &baud_rate), "Baud rate must be a number", ERR_WRONGARG)) return NULL;

  // Update FTDI device
  utils_check(FT_SetBaudRate(instance_data->ftHandle, (ULONG)baud_rate));

  return NULL;
}

#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

napi_value device_setBitMode(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class and `argc`/`argv` passed to the function
  #define NB_ARGS 2 // number of expected arguments
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
  uint32_t mask, bit_mode;
  if(utils_check(
    ((napi_get_value_uint32(env, argv[0], &mask) != napi_ok) || (mask > 0xFF)),
    "Mask must be a number and less than 0xFF", ERR_WRONGARG)) return NULL;
  if(utils_check(
    ((napi_get_value_uint32(env, argv[1], &bit_mode) != napi_ok) || (
      bit_mode != FT_BITMODE_RESET && bit_mode != FT_BITMODE_ASYNC_BITBANG &&
      bit_mode != FT_BITMODE_MPSSE && bit_mode != FT_BITMODE_SYNC_BITBANG &&
      bit_mode != FT_BITMODE_MCU_HOST && bit_mode != FT_BITMODE_FAST_SERIAL &&
      bit_mode != FT_BITMODE_CBUS_BITBANG && bit_mode != FT_BITMODE_SYNC_FIFO)),
    "Bit mode must be FT_BITMODE_RESET, FT_BITMODE_ASYNC_BITBANG, FT_BITMODE_MPSSE, FT_BITMODE_SYNC_BITBANG, FT_BITMODE_MCU_HOST, FT_BITMODE_FAST_SERIAL, FT_BITMODE_CBUS_BITBANG or FT_BITMODE_SYNC_FIFO", ERR_WRONGARG))
    return NULL;

  // Update FTDI device
  utils_check(FT_SetBitMode(instance_data->ftHandle, (UCHAR)mask, (UCHAR)bit_mode));

  return NULL;
}

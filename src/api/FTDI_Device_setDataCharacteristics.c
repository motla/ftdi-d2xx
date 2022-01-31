#include "api/FTDI_Device_setDataCharacteristics.h"
#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

napi_value device_setDataCharacteristics(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class and `argc`/`argv` passed to the function
  size_t argc = 3; // size of the argv buffer
  napi_value this_arg, argv[argc];
  utils_check(napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL));
  if(utils_check(argc < 3, "Missing argument")) return NULL;

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object")) return NULL;

  // Check arguments, and convert JavaScript numbers to C values
  uint32_t word_length, stop_bits, parity;
  if(utils_check(
      ((napi_get_value_uint32(env, argv[0], &word_length) != napi_ok) || (word_length != FT_BITS_8 && word_length != FT_BITS_7)),
      "Number of bits per word must be FT_BITS_8 or FT_BITS_7")) return NULL;
  if(utils_check(
      ((napi_get_value_uint32(env, argv[1], &stop_bits) != napi_ok) || (stop_bits != FT_STOP_BITS_1 && stop_bits != FT_STOP_BITS_2)),
      "Number of stop bits must be FT_STOP_BITS_1 or FT_STOP_BITS_2")) return NULL;
  if(utils_check(
      ((napi_get_value_uint32(env, argv[2], &parity) != napi_ok) || (parity > FT_PARITY_SPACE)),
      "Parity must be FT_PARITY_NONE, FT_PARITY_ODD, FT_PARITY_EVEN, FT_PARITY_MARK or FT_PARITY_SPACE")) return NULL;

  // Set FTDI device data characteristics
  utils_check(FT_SetDataCharacteristics(instance_data->ftHandle, word_length, stop_bits, parity));

  return NULL;
}

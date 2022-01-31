#include "api/FTDI_Device_setBaudRate.h"
#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

napi_value device_setBaudRate(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class and `argc`/`argv` passed to the function
  size_t argc = 1; // size of the argv buffer
  napi_value this_arg, argv[argc];
  utils_check(napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL));
  if(utils_check(argc < 1, "Missing argument", "missarg")) return NULL;

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", "deadobj")) return NULL;

  // Check that the baudrate argument is a number
  napi_valuetype type;
  utils_check(napi_typeof(env, argv[0], &type));
  if(utils_check(type != napi_number, "Baud rate must be a number", "wrongarg")) return NULL;

  // Convert JavaScript number to C value
  ULONG baudRate;
  utils_check(napi_get_value_uint32(env, argv[0], &baudRate));

  // Set FTDI device baud rate
  utils_check(FT_SetBaudRate(instance_data->ftHandle, baudRate));

  return NULL;
}

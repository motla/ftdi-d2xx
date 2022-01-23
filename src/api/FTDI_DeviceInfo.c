#include "api/FTDI_DeviceInfo.h"
#include "error_check.h"

// Class constructor (runs either the class function is called using `new` or not)
static napi_value constructor(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to the instance of the class and get `argc`/`argv` passed to the constructor
  size_t argc = 8; // size of the buffer
  napi_value this_arg, argv[argc];
  error_check(env, napi_get_cb_info(env, info, &argc, argv, &this_arg, NULL) == napi_ok);
  error_check(env, argc >= 8); // check that all expected arguments were passed

  // Add instance properties from constructor arguments
  const napi_property_descriptor props[] = {
    { "serial_number", NULL, NULL, NULL, NULL, argv[0], napi_enumerable, NULL },
    { "description", NULL, NULL, NULL, NULL, argv[1], napi_enumerable, NULL },
    { "type", NULL, NULL, NULL, NULL, argv[2], napi_enumerable, NULL },
    { "is_open", NULL, NULL, NULL, NULL, argv[3], napi_enumerable, NULL },
    { "usb_vid", NULL, NULL, NULL, NULL, argv[4], napi_enumerable, NULL },
    { "usb_pid", NULL, NULL, NULL, NULL, argv[5], napi_enumerable, NULL },
    { "usb_loc_id", NULL, NULL, NULL, NULL, argv[6], napi_enumerable, NULL },
    { "usb_speed", NULL, NULL, NULL, NULL, argv[7], napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  error_check(env, napi_define_properties(env, this_arg, nb_props, props) == napi_ok);

  // Return class instance
  return this_arg;
}

// Called once to initialize class (then to reference it in module data)
void device_info_initialize_class(napi_env env, napi_value* result) {
  error_check(env, napi_define_class(env, "FTDI_DeviceInfo", NAPI_AUTO_LENGTH, constructor, NULL, 0, NULL, result) == napi_ok);
}
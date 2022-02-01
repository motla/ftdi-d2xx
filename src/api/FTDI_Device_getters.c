#include <stdio.h>

#include "api/FTDI_Device_getters.h"
#include "api/FTDI_Device.h"
#include "ftd2xx.h"
#include "utils.h"

//TODO remove this functionality: is_open is not correlated to the fact the device is open
napi_value device_get_is_open(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Return boolean if ftHandle exists
  napi_value handle_is_open;
  utils_check(napi_get_boolean(env, instance_data->ftHandle != NULL, &handle_is_open));
  return handle_is_open;
}


napi_value device_get_info(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", "deadobj")) return NULL;

  // Get info from FTDI
  FT_DEVICE ftDevice;
  DWORD deviceID;
  char SerialNumber[16];
  char Description[64];
  utils_check(FT_GetDeviceInfo(instance_data->ftHandle, &ftDevice, &deviceID, SerialNumber, Description, NULL));

  // Convert values to JavaScript
  napi_value serial_number, description, type, usb_vid, usb_pid;
  utils_check(napi_create_string_utf8(env, SerialNumber, NAPI_AUTO_LENGTH, &serial_number));
  utils_check(napi_create_string_utf8(env, Description, NAPI_AUTO_LENGTH, &description));
  type = utils_ft_device_to_js_string(env, ftDevice);
  utils_check(napi_create_uint32(env, deviceID >> 16, &usb_vid));
  utils_check(napi_create_uint32(env, deviceID & 0xFFFF, &usb_pid));

  // Return JavaScript object containing infos
  napi_value object;
  const napi_property_descriptor props[] = {
    //{ "serial_number", NULL, NULL, NULL, NULL, serial_number, napi_enumerable, NULL }, // omit this as it is already in the constructor
    { "description", NULL, NULL, NULL, NULL, description, napi_enumerable, NULL },
    { "type", NULL, NULL, NULL, NULL, type, napi_enumerable, NULL },
    { "usb_vid", NULL, NULL, NULL, NULL, usb_vid, napi_enumerable, NULL },
    { "usb_pid", NULL, NULL, NULL, NULL, usb_pid, napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  utils_check(napi_create_object(env, &object));
  utils_check(napi_define_properties(env, object, nb_props, props));
  return object;
}


napi_value device_get_modem_status(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", "deadobj")) return NULL;

  // Get info from FTDI
  ULONG ModemStatus;
  utils_check(FT_GetModemStatus(instance_data->ftHandle, &ModemStatus));

  // Convert values to JavaScript
  napi_value bool_true, bool_false;
  utils_check(napi_get_boolean(env, true, &bool_true));
  utils_check(napi_get_boolean(env, false, &bool_false));

  // Return JavaScript object containing infos
  napi_value object;
  const napi_property_descriptor props[] = {
    { "clear_to_send", NULL, NULL, NULL, NULL, ModemStatus & 0x10 ? bool_true : bool_false, napi_enumerable, NULL },
    { "data_set_ready", NULL, NULL, NULL, NULL, ModemStatus & 0x20 ? bool_true : bool_false, napi_enumerable, NULL },
    { "ring_indicator", NULL, NULL, NULL, NULL, ModemStatus & 0x40 ? bool_true : bool_false, napi_enumerable, NULL },
    { "data_carrier_detect", NULL, NULL, NULL, NULL, ModemStatus & 0x80 ? bool_true : bool_false, napi_enumerable, NULL },
    { "overrun_error", NULL, NULL, NULL, NULL, ModemStatus & 0x0200 ? bool_true : bool_false, napi_enumerable, NULL },
    { "parity_error", NULL, NULL, NULL, NULL, ModemStatus & 0x0400 ? bool_true : bool_false, napi_enumerable, NULL },
    { "framing_error", NULL, NULL, NULL, NULL, ModemStatus & 0x0800 ? bool_true : bool_false, napi_enumerable, NULL },
    { "break_interrupt", NULL, NULL, NULL, NULL, ModemStatus & 0x1000 ? bool_true : bool_false, napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  utils_check(napi_create_object(env, &object));
  utils_check(napi_define_properties(env, object, nb_props, props));
  return object;
}


napi_value device_get_driver_version(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  utils_check(napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL));

  // Get the class instance data containing FTDI device handle
  device_instance_data_t* instance_data;
  utils_check(napi_unwrap(env, this_arg, (void**)(&instance_data)));

  // Check the device is open if its handle is still there
  if(utils_check(instance_data->ftHandle == NULL, "Dead device object", "deadobj")) return NULL;

  // Get info from FTDI
  DWORD DriverVersion;
  utils_check(FT_GetDriverVersion(instance_data->ftHandle, &DriverVersion));

  // Convert values to JavaScript
  char buffer[16];
  napi_value version;
  snprintf(buffer, 16, "%u.%02u.%02u", (DriverVersion >> 16) & 0xFF, (DriverVersion >> 8) & 0xFF, (DriverVersion) & 0xFF);
  utils_check(napi_create_string_utf8(env, buffer, NAPI_AUTO_LENGTH, &version));
  return version;
}
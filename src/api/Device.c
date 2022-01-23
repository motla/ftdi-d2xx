#include <stdlib.h>
#include <string.h>

#include "api/Device.h"
#include "error_check.h"

typedef struct {
  FT_HANDLE device_ftHandle;
  FT_DEVICE_LIST_INFO_NODE device_info;
  bool is_connected;
} instance_data_t;

// FTDI Device open function
static napi_value open(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  // Try to open FTDI device
  //FT_OpenEx()

  return this_arg;
}

// FTDI Device close function
static napi_value close(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  return NULL;
}

// FTDI Device read function
static napi_value read(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  return NULL;
}

// FTDI Device write function
static napi_value write(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  return NULL;
}

// Getter for isConnected property
static napi_value get_is_connected(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  // Return the info converted in JavaScript
  napi_value value;
  error_check(env, napi_get_boolean(env, instance_data->is_connected, &value) == napi_ok);
  return value;
}

// Getter for SerialNumber property
static napi_value get_serial_number(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  // Return the info converted in JavaScript
  napi_value value;
  error_check(env, napi_create_string_utf8(env, instance_data->device_info.SerialNumber, sizeof(instance_data->device_info.SerialNumber), &value) == napi_ok);
  return value;

      // printf("Dev %d:\n", i);
      // printf("  Flags=0x%x\n", device_info.Flags);
      // printf("  Type=0x%x\n", device_info.Type);
      // printf("  ID=0x%x\n", device_info.ID);
      // printf("  LocId=0x%x\n", device_info.LocId);
      // printf("  SerialNumber=%s\n", device_info.SerialNumber);
      // printf("  Description=%s\n", device_info.Description);
      // printf("  ftHandle=0x%x\n", device_info.ftHandle);
}

// Getter for Description property
static napi_value get_description(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to this instance of the class
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Get the class instance data
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, this_arg, (void**)(&instance_data)) == napi_ok);

  // Return the info converted in JavaScript
  napi_value value;
  error_check(env, napi_create_string_utf8(env, instance_data->device_info.Description, sizeof(instance_data->device_info.Description), &value) == napi_ok);
  return value;
}


// Utility function to free one instance data before it is deleted
static void finalize_cb(napi_env env, void* finalize_data, void* finalize_hint) {
  free(finalize_data); // free class instance data
}


// Class constructor (runs either the class function is called using `new` or not)
static napi_value constructor(napi_env env, napi_callback_info info) {
  // Get JavaScript `this` corresponding to the instance of the class (in this case, `argc`/`argv` are not used)
  napi_value this_arg;
  error_check(env, napi_get_cb_info(env, info, NULL, NULL, &this_arg, NULL) == napi_ok);

  // Create and wrap instance data containing FTDI device handle and info. It will be set when `open()` is called
  instance_data_t* instance_data = malloc(sizeof(instance_data_t)); // allocate memory for instance data
  memset(instance_data, 0, sizeof(instance_data_t)); // initialize instance data to zeros
  error_check(env, napi_wrap(env, this_arg, instance_data, finalize_cb, NULL, NULL) == napi_ok);

  // Add instance properties
  const napi_property_descriptor props[] = {
    { "isConnected", NULL, NULL, get_is_connected, NULL, NULL, napi_enumerable, NULL },
    { "SerialNumber", NULL, NULL, get_serial_number, NULL, NULL, napi_enumerable, NULL },
    { "Description", NULL, NULL, get_description, NULL, NULL, napi_enumerable, NULL },
  };
  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  error_check(env, napi_define_properties(env, this_arg, nb_props, props) == napi_ok);

  // Return class instance
  return this_arg;
}

// Called once to initialize class (then to reference it in module data)
void device_initialize_class(napi_env env, napi_value* result) {

  // Add class prototype
  const napi_property_descriptor props[] = {
    { "open", NULL, open, NULL, NULL, NULL, napi_enumerable, NULL },
    { "close", NULL, close, NULL, NULL, NULL, napi_enumerable, NULL },
    { "read", NULL, read, NULL, NULL, NULL, napi_enumerable, NULL },
    { "write", NULL, write, NULL, NULL, NULL, napi_enumerable, NULL },
  };

  size_t nb_props = sizeof(props) / sizeof(napi_property_descriptor);
  error_check(env, napi_define_class(env, "Device", NAPI_AUTO_LENGTH, constructor, NULL, nb_props, props, result) == napi_ok);
}

// Get the class instance data and copy the new device info to the instance data
void device_update_instance_info(napi_env env, napi_value device_object, FT_DEVICE_LIST_INFO_NODE* device_info, bool is_connected) {
  instance_data_t* instance_data;
  error_check(env, napi_unwrap(env, device_object, (void**)(&instance_data)) == napi_ok);
  if(device_info) memcpy(&(instance_data->device_info), device_info, sizeof(FT_DEVICE_LIST_INFO_NODE));
  instance_data->is_connected = is_connected;
}
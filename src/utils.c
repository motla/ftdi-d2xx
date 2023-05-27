#include <stdio.h>
#include <string.h>
#include "utils.h"

#define MAX_MSG_SIZE 256

// Throw formatted error
bool utils_test_throw(int assertion, const char* assertion_str, napi_env env, const char* file, int line, utils_error_desc_t err_desc) {
  char buffer[MAX_MSG_SIZE];

  // Test assertion, return without error if its result is 0 as expected
  if(assertion == 0) return false;

  // Else, we are throwing an error with a useful message:

  // If a specific message is provided: write it directly
  if(err_desc.message) {
    snprintf(buffer, MAX_MSG_SIZE, "%s (%s:%d)", err_desc.message, file, line);
    napi_throw_error(env, err_desc.code, buffer);
    return true;
  }

  // Else, check Node-API for errors
  const napi_extended_error_info* err_info;
  napi_get_last_error_info(env, &err_info);

  // If the Node-API has an error, write its description
  if(err_info->error_code) {
    snprintf(buffer, MAX_MSG_SIZE, "%s (%s:%d)", err_info->error_message, file, line);
    napi_throw_error(env, utils_napi_status_to_string(err_info->error_code), buffer);
    return true;
  }

  // Else, try to see if we check an FTDI function, then write its explicit status code
  if(strncmp(assertion_str, "FT_", 3) == 0) {
    const char* error_code = utils_ft_status_to_string((FT_STATUS)assertion);
    const char* cut_at = strchr(assertion_str, '('); // cut the expression to keep only the function name (remove arguments)
    int assertion_maxlen = cut_at ? (int)(cut_at - assertion_str) : 100;
    snprintf(buffer, MAX_MSG_SIZE, "`%.*s` returned %s (%s:%d)", assertion_maxlen, assertion_str, error_code, file, line);
    napi_throw_error(env, error_code, buffer);
    return true;
  };

  // Else, write the assertion result and expected result in plain integers
  snprintf(buffer, MAX_MSG_SIZE, "`%s` returned %d instead of 0 (%s:%d)", assertion_str, assertion, file, line);
  napi_throw_error(env, err_desc.code, buffer);
  return true;
}


// Convert napi_status to C string
const char* utils_napi_status_to_string(napi_status status) {
  switch(status) {
    case napi_ok: return "napi_ok";
    case napi_invalid_arg: return "napi_invalid_arg";
    case napi_object_expected: return "napi_object_expected";
    case napi_string_expected: return "napi_string_expected";
    case napi_name_expected: return "napi_name_expected";
    case napi_function_expected: return "napi_function_expected";
    case napi_number_expected: return "napi_number_expected";
    case napi_boolean_expected: return "napi_boolean_expected";
    case napi_array_expected: return "napi_array_expected";
    case napi_generic_failure: return "napi_generic_failure";
    case napi_pending_exception: return "napi_pending_exception";
    case napi_cancelled: return "napi_cancelled";
    case napi_escape_called_twice: return "napi_escape_called_twice";
    case napi_handle_scope_mismatch: return "napi_handle_scope_mismatch";
    case napi_callback_scope_mismatch: return "napi_callback_scope_mismatch";
    case napi_queue_full: return "napi_queue_full";
    case napi_closing: return "napi_closing";
    case napi_bigint_expected: return "napi_bigint_expected";
    case napi_date_expected: return "napi_date_expected";
    case napi_arraybuffer_expected: return "napi_arraybuffer_expected";
    case napi_detachable_arraybuffer_expected: return "napi_detachable_arraybuffer_expected";
    case napi_would_deadlock: return "napi_would_deadlock";
    default: return "an unknown Node-API error";
  }
}

// Convert FT_STATUS to C string
const char* utils_ft_status_to_string(FT_STATUS status) {
  switch(status) {
    case FT_OK: return "FT_OK";
    case FT_INVALID_HANDLE: return "FT_INVALID_HANDLE";
    case FT_DEVICE_NOT_FOUND: return "FT_DEVICE_NOT_FOUND";
    case FT_DEVICE_NOT_OPENED: return "FT_DEVICE_NOT_OPENED";
    case FT_IO_ERROR: return "FT_IO_ERROR";
    case FT_INSUFFICIENT_RESOURCES: return "FT_INSUFFICIENT_RESOURCES";
    case FT_INVALID_PARAMETER: return "FT_INVALID_PARAMETER";
    case FT_INVALID_BAUD_RATE: return "FT_INVALID_BAUD_RATE";
    case FT_DEVICE_NOT_OPENED_FOR_ERASE: return "FT_DEVICE_NOT_OPENED_FOR_ERASE";
    case FT_DEVICE_NOT_OPENED_FOR_WRITE: return "FT_DEVICE_NOT_OPENED_FOR_WRITE";
    case FT_FAILED_TO_WRITE_DEVICE: return "FT_FAILED_TO_WRITE_DEVICE";
    case FT_EEPROM_READ_FAILED: return "FT_EEPROM_READ_FAILED";
    case FT_EEPROM_WRITE_FAILED: return "FT_EEPROM_WRITE_FAILED";
    case FT_EEPROM_ERASE_FAILED: return "FT_EEPROM_ERASE_FAILED";
    case FT_EEPROM_NOT_PRESENT: return "FT_EEPROM_NOT_PRESENT";
    case FT_EEPROM_NOT_PROGRAMMED: return "FT_EEPROM_NOT_PROGRAMMED";
    case FT_INVALID_ARGS: return "FT_INVALID_ARGS";
    case FT_NOT_SUPPORTED: return "FT_NOT_SUPPORTED";
    case FT_OTHER_ERROR: return "FT_OTHER_ERROR";
    case FT_DEVICE_LIST_NOT_READY: return "FT_DEVICE_LIST_NOT_READY";
    default: return "an unknown FTDI error";
  }
}

// Convert FT_DEVICE to JavaScript string
napi_value utils_ft_device_to_js_string(napi_env env, FT_DEVICE device) {
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
  utils_check(napi_create_string_utf8(env, value_ptr, NAPI_AUTO_LENGTH, &js_value));
  return js_value;
}
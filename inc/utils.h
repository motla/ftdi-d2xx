#ifndef utils_h
#define utils_h

#include <stdbool.h>
#include "node_api.h"
#include "ftd2xx.h"

// Error management (SOURCE_PATH_SIZE is set in CMakeLists.txt in order to hide absolute file tree)
typedef struct {
  char* message; // will be NULL if the message argument is omitted
} utils_error_desc_t;
#define utils_check(assertion, ...) \
  utils_test_throw(assertion, #assertion, env, &(__FILE__[SOURCE_PATH_SIZE]), __LINE__, (utils_error_desc_t){__VA_ARGS__})
bool utils_test_throw(int assertion, char* assertion_str, napi_env env, char* file, int line, utils_error_desc_t err_desc);

// To force displaying the explicit FT_STATUS code, write FT_|ftStatus
#define FT_ 0

// Convert FT_STATUS to C string
const char* utils_ft_status_to_string(FT_STATUS status);

// Convert FT_DEVICE to JavaScript string
napi_value utils_ft_device_to_js_string(napi_env env, FT_DEVICE device);

#endif
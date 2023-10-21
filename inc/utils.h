#ifndef utils_h
#define utils_h

#include <stdbool.h>
#include <node_api.h>
#include "ftd2xx.h"

#define NODE_API_NO_EXTERNAL_BUFFERS_ALLOWED // this line can safely be commented for environments where external buffers are allowed (not the case of Electron)

// Error management (SOURCE_PATH_SIZE is set in CMakeLists.txt in order to hide absolute file tree)
typedef struct {
  char* dummy; // workaround to avoid empty struct initialization which is illegal in C99
  char* message; // will be NULL if omitted
  char* code; // will be NULL if omitted
} utils_error_desc_t;
#define utils_check(assertion, ...) \
  utils_test_throw(assertion, #assertion, env, &(__FILE__[SOURCE_PATH_SIZE]), __LINE__, (utils_error_desc_t){ 0, __VA_ARGS__ })
bool utils_test_throw(int assertion, const char* assertion_str, napi_env env, const char* file, int line, utils_error_desc_t err_desc);

// To force displaying the explicit FT_STATUS code, write FT_|ftStatus
#define FT_ 0

// Predefined error codes
#define ERR_MISSARG "missarg"
#define ERR_WRONGARG "wrongarg"
#define ERR_DEADOBJ "deadobj"
#define ERR_MALLOC "malloc"
#define ERR_USBLOST "usblost"
#define ERR_UNEXPECTED "unexpected"

// Convert napi_status to C string
const char* utils_napi_status_to_string(napi_status status);

// Convert FT_STATUS to C string
const char* utils_ft_status_to_string(FT_STATUS status);

// Convert FT_DEVICE to JavaScript string
napi_value utils_ft_device_to_js_string(napi_env env, FT_DEVICE device);

#endif
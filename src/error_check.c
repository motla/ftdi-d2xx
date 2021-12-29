#include <stdio.h>

#include "error_check.h"

#define BUFFER_SIZE 256

void throw_error(napi_env env, char* file, int line, char* assertion) {
  char buffer[BUFFER_SIZE];
  snprintf(buffer, BUFFER_SIZE, "FTDI driver failed at %s:%d:\n    (%s)", file, line, assertion);
  napi_throw_error(env, NULL, buffer);
}

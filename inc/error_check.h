#ifndef error_check_h
#define error_check_h

#include <node_api.h>

#define error_check(env, assertion) if(!(assertion)){ throw_error(env, __FILE__, __LINE__, #assertion); }

void throw_error(napi_env env, char* file, int line, char* assertion);

#endif

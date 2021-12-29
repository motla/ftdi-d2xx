# Configure CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ftdi-d2xx)

# Declare the source files list
list(APPEND SRC "src/main.c")
list(APPEND SRC "src/module_data.c")
list(APPEND SRC "src/error_check.c")
list(APPEND SRC "src/api/getDeviceInfoList.c")

# Declare the include files folder
include_directories("inc")

# Declare FTDI D2XX static library
link_directories("lib")
list(APPEND LIB "ftd2xx")

# Generate a .node library from declared files using CMake.js
include_directories(${CMAKE_JS_INC})
add_library(${PROJECT_NAME} SHARED ${SRC} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${LIB} ${CMAKE_JS_LIB})

# Link macOS native frameworks to the library
target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
target_link_libraries(${PROJECT_NAME} "-framework IOKit")

# Set minimum Node-API version
# Node-API version 3 is a good choice as this is the Node-API version active when Node-API left experimental status.
add_definitions(-DNAPI_VERSION=3)

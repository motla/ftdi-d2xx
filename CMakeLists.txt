# Configure CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ftdi-d2xx)

# Set minimum Node-API version
add_definitions(-DNAPI_VERSION=8)

# Show warnings on compilation
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra)
endif()

# Declare the source files list
list(APPEND SRC "src/main.c")
list(APPEND SRC "src/constants.c")
list(APPEND SRC "src/module_data.c")
list(APPEND SRC "src/utils.c")
list(APPEND SRC "src/api/FTDI_Device_close.c")
list(APPEND SRC "src/api/FTDI_Device_eraseEE.c")
list(APPEND SRC "src/api/FTDI_Device_getters.c")
list(APPEND SRC "src/api/FTDI_Device_purge.c")
list(APPEND SRC "src/api/FTDI_Device_read.c")
list(APPEND SRC "src/api/FTDI_Device_readEE.c")
list(APPEND SRC "src/api/FTDI_Device_setBaudRate.c")
list(APPEND SRC "src/api/FTDI_Device_setBitMode.c")
list(APPEND SRC "src/api/FTDI_Device_setDataCharacteristics.c")
list(APPEND SRC "src/api/FTDI_Device_setFlowControl.c")
list(APPEND SRC "src/api/FTDI_Device_setLatencyTimer.c")
list(APPEND SRC "src/api/FTDI_Device_setTimeouts.c")
list(APPEND SRC "src/api/FTDI_Device_setUSBParameters.c")
list(APPEND SRC "src/api/FTDI_Device_simpleFunctions.c")
list(APPEND SRC "src/api/FTDI_Device_write.c")
list(APPEND SRC "src/api/FTDI_Device_writeEE.c")
list(APPEND SRC "src/api/FTDI_Device.c")
list(APPEND SRC "src/api/FTDI_DeviceInfo.c")
list(APPEND SRC "src/api/getDeviceInfoList.c")
list(APPEND SRC "src/api/openDevice.c")
list(APPEND SRC "src/api/setVIDPID.c")

# Declare the include files folder
include_directories("inc")

# Declare FTDI D2XX static library
link_directories("lib/${CMAKE_SYSTEM_NAME}")
link_directories("lib/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")
list(APPEND LIB "ftd2xx")
add_definitions("-DFTD2XX_STATIC")

# Generate a .node library from declared files using CMake.js
include_directories(${CMAKE_JS_INC})
add_library(${PROJECT_NAME} SHARED ${SRC} ${CMAKE_JS_SRC})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
else()
  set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".${CMAKE_SYSTEM_NAME}.${CMAKE_SYSTEM_PROCESSOR}.node")
endif()
target_link_libraries(${PROJECT_NAME} ${LIB} ${CMAKE_JS_LIB})

# Set SOURCE_PATH_SIZE to hide file paths in error_check messages
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

# Link macOS native frameworks to the library
if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
endif()
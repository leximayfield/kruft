cmake_minimum_required(VERSION 3.25)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(KRUFT_ENABLE_TESTS "Enable tests")
option(KRUFT_ENABLE_BENCHES "Enable benchmarks")
option(KRUFT_ENABLE_COVERAGE "Enable code coverage on tests")

project(kruft LANGUAGES C CXX)

set(KRUFT_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krarg.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krbit.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krbltin.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krbool.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krckdint.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krconfig.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krctype.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krint.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krlib.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krlimits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krmath.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krrand.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krserial.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/krstr.h")

add_library(kruft INTERFACE ${KRUFT_HEADERS})
target_include_directories(kruft INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

if(KRUFT_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
if(KRUFT_ENABLE_BENCHES)
    add_subdirectory(benches)
endif()

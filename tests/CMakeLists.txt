include(CheckCompilerFlag)
include(FindSanitizers)

set(KRUFT_C_STANDARD "90" CACHE STRING "C Standard to use")
set(KRUFT_CXX_STANDARD "14" CACHE STRING "C++ Standard to use")

set(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/t_bit.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_bltin.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_ckdint.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_ctype.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_int.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_lib.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_limits.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_math.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_rand.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_serial.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/t_str.inl")

# Test suite.
add_executable(kruft_test_c
    "${CMAKE_CURRENT_SOURCE_DIR}/test_c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/zztest.c")
add_executable(kruft_test_cxx
    "${CMAKE_CURRENT_SOURCE_DIR}/test_cxx.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/zztest.c")

target_include_directories(kruft_test_c PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(kruft_test_cxx PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(kruft_test_c PRIVATE kruft)
target_link_libraries(kruft_test_cxx PRIVATE kruft)

check_compiler_flag(CXX -Wmost W_MOST)
if(W_MOST)
    target_compile_options(kruft_test_c PRIVATE "-Wmost")
    target_compile_options(kruft_test_cxx PRIVATE "-Wmost")
endif()

check_compiler_flag(CXX -Wconversion W_CONVERSION)
if(W_MOST)
    target_compile_options(kruft_test_c PRIVATE "-Wconversion")
    target_compile_options(kruft_test_cxx PRIVATE "-Wconversion")
endif()

check_compiler_flag(CXX -Werror=c++17-extensions WERROR_CXX17_EXTENSIONS)
if(WERROR_CXX17_EXTENSIONS)
    target_compile_options(kruft_test_cxx PRIVATE "-Werror=c++17-extensions")
endif()

check_compiler_flag(CXX -Werror=c++20-extensions WERROR_CXX20_EXTENSIONS)
if(WERROR_CXX20_EXTENSIONS)
    target_compile_options(kruft_test_cxx PRIVATE "-Werror=c++20-extensions")
endif()

if(MSVC)
    target_compile_options(kruft_test_c PUBLIC /W4 /permissive-)
    target_compile_options(kruft_test_cxx PUBLIC /W4 /permissive-)
else()
    target_compile_options(kruft_test_c PUBLIC -Wall -Wextra -Wno-unknown-pragmas)
    target_compile_options(kruft_test_cxx PUBLIC -Wall -Wextra -Wno-unknown-pragmas)
endif()

set_target_properties(kruft_test_c PROPERTIES C_STANDARD "${KRUFT_C_STANDARD}")
set_target_properties(kruft_test_cxx PROPERTIES CXX_STANDARD "${KRUFT_CXX_STANDARD}")

enable_testing()
add_test(NAME kruft_test_c COMMAND $<TARGET_FILE:kruft_test_c>)
add_test(NAME kruft_test_cxx COMMAND $<TARGET_FILE:kruft_test_cxx>)

if(KRUFT_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        include(CodeCoverage)
        append_coverage_compiler_flags_to_target(kruft_test_c)
        setup_target_for_coverage_lcov(
            NAME kruft_test_c_cov
            EXECUTABLE kruft_test_c
            DEPENDENCIES kruft_test_c
            EXCLUDE "build/*" "tests" "/usr/include/*"
            LCOV_ARGS --ignore-errors mismatch)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        include(LLVMCov)
        append_llvmcov_compiler_flags_to_target(kruft_test_c)
        setup_target_for_coverage_llvmcov(
            NAME kruft_test_c_cov
            EXECUTABLE kruft_test_c
            DEPENDENCIES kruft_test_c
            SOURCES ${KRUFT_HEADERS})
    else()
        message(FATAL_ERROR "KRUFT_ENABLE_COVERAGE not supported by compiler")
    endif()
endif()

# Minimal defines dump.
add_executable(kruft_defs "${CMAKE_CURRENT_SOURCE_DIR}/defs.c")
target_link_libraries(kruft_defs PRIVATE kruft)

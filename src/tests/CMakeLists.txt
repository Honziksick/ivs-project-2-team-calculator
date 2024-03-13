cmake_minimum_required(VERSION 3.16)
project(calm_cat_calc)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage.cmake)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(POSITION_INDEPENDENT_CODE ON)
endif()

include_directories(../CalmCatCalc/core)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(cat_calc_core ../CalmCatCalc/core/cat_calc_core.cpp)
add_executable(cat_calc_core_test cat_calc_core_tests.cpp ../CalmCatCalc/core/cat_calc_core.cpp)
target_link_libraries(cat_calc_core gtest_main gmock_main)
target_link_libraries(cat_calc_core_test gtest_main gmock_main)
gtest_discover_tests(cat_calc_core_test)
if(CMAKE_COMPILER_IS_GNUCXX)
    SETUP_TARGET_FOR_COVERAGE(cat_calc_core_test_coverage cat_calc_core_test cat_calc_core_test_coverage)
endif()

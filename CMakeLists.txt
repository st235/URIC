cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library targets.

add_library(uric INTERFACE)

target_sources(uric INTERFACE
  # Token reader.
  src/token_reader.h
  # Uri parser.
  src/uri_parser.h
  src/uri_parser.cpp
)
target_include_directories(uric INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

#  Enable all possible warnings and treat them as errors.
# if(MSVC)
#   target_compile_options(uric INTERFACE /W4 /WX)
# else()
#   target_compile_options(uric INTERFACE -Wall -Wextra -Wpedantic -Werror)
# endif()

# Test targets.

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(uric_tests
  # Parser tests.
  tests/uri_parser_validation_decOctet.cpp
  tests/uri_parser_validation_pathAbempty.cpp
  tests/uri_parser_validation_pchar.cpp
  tests/uri_parser_validation_pctEncoded.cpp
  tests/uri_parser_validation_queryFragment.cpp
  tests/uri_parser_validation_segment.cpp
  tests/uri_parser_validation_segmentNz.cpp
  tests/uri_parser_validation_segmentNzNc.cpp

  tests/uri_tests.cpp
  tests/uri_parser_tests.cpp
)

target_link_libraries(uric_tests PRIVATE uric)
target_include_directories(uric_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

target_link_libraries(uric_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(uric_tests)

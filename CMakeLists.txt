cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(URIC VERSION 0.9.0 DESCRIPTION "A Uniform Resource Identifier (URI) implementation in C++, designed strictly in compliance with RFC 3986.")

# Library targets.

add_library(uric INTERFACE)

target_sources(uric INTERFACE
  # API implementation.
  src/authority.cpp
  src/uri.cpp
  # Normalisation algorithms.
  src/path_normaliser.h
  # Token reader.
  src/token_reader.h
  # Uri parser.
  src/uri_parser.h
  src/uri_parser.cpp
)
target_include_directories(uric INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Compile test targets, disabled by default.
option(COMPILE_TESTS "Compiled with tests when turned on." OFF)

if (COMPILE_TESTS)
  message("Compiling tests.")

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
    # API tests.
    tests/authority_tests.cpp
    tests/uri_tests.cpp
    tests/url_tests.cpp

    # Path normalisation tests.
    tests/path_normaliser_getHierarchicalSegments.cpp
    tests/path_normaliser_removeDotSegments.cpp
    tests/path_normaliser_codeIfNecessary.cpp
    
    # Parser tests.
    #  Utils.
    tests/parser/utils/parser_test_utils.h
    tests/parser/utils/parser_test_utils.cpp

    tests/parser/uri_parser_validation_absoluteUri.cpp
    tests/parser/uri_parser_validation_authority.cpp
    tests/parser/uri_parser_validation_decOctet.cpp
    tests/parser/uri_parser_validation_h16.cpp
    tests/parser/uri_parser_validation_hierPart.cpp
    tests/parser/uri_parser_validation_host.cpp
    tests/parser/uri_parser_validation_IPLiteral.cpp
    tests/parser/uri_parser_validation_IPv4address.cpp
    tests/parser/uri_parser_validation_IPv6address.cpp
    tests/parser/uri_parser_validation_IPvFuture.cpp
    tests/parser/uri_parser_validation_ls32.cpp
    tests/parser/uri_parser_validation_path.cpp
    tests/parser/uri_parser_validation_pathAbempty.cpp
    tests/parser/uri_parser_validation_pathAbsolute.cpp
    tests/parser/uri_parser_validation_pathEmpty.cpp
    tests/parser/uri_parser_validation_pathNoscheme.cpp
    tests/parser/uri_parser_validation_pathRootless.cpp
    tests/parser/uri_parser_validation_pchar.cpp
    tests/parser/uri_parser_validation_pctEncoded.cpp
    tests/parser/uri_parser_validation_port.cpp
    tests/parser/uri_parser_validation_queryFragment.cpp
    tests/parser/uri_parser_validation_regName.cpp
    tests/parser/uri_parser_validation_relativePart.cpp
    tests/parser/uri_parser_validation_relativeRef.cpp
    tests/parser/uri_parser_validation_scheme.cpp
    tests/parser/uri_parser_validation_segment.cpp
    tests/parser/uri_parser_validation_segmentNz.cpp
    tests/parser/uri_parser_validation_segmentNzNc.cpp
    tests/parser/uri_parser_validation_uri.cpp
    tests/parser/uri_parser_validation_uriReference.cpp
    tests/parser/uri_parser_validation_userInfo.cpp
  )

  target_link_libraries(uric_tests PRIVATE uric)
  target_include_directories(uric_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

  target_link_libraries(uric_tests PRIVATE GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(uric_tests)

  # Enable all possible warnings and treat them as errors.
  if(MSVC)
    target_compile_options(uric_tests PRIVATE /W4 /WX)
  else()
    target_compile_options(uric_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
  endif()

endif()

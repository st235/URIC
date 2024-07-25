cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(uri-validator VERSION 1.0 DESCRIPTION "Validates random URIs.")

add_executable(uri-validator
    main.cpp
)

# Add URIC Dependency

include(FetchContent)

FetchContent_Declare(
  URIC
  GIT_REPOSITORY git@github.com:st235/URIC.git
  GIT_TAG "main"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
)
FetchContent_MakeAvailable(URIC)

target_link_libraries(uri-validator uric)
cmake_minimum_required(VERSION 3.5)

project(test_p LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_e test.cpp)
target_include_directories(test_e PRIVATE ../src)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../lib/gtest" "googletest" EXCLUDE_FROM_ALL)
target_link_libraries(test_e
  #    ${Boost_LIBRARIES}
  gtest_main
)


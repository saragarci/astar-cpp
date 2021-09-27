cmake_minimum_required(VERSION 3.14)
project(AstarSearch)

set(CMAKE_CXX_STANDARD 20)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find all executables
file(GLOB project_SRCS src/*.cpp src/*.h)
add_executable(AstarSearch ${project_SRCS})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Create a library for unit tests
add_library(astar_search OBJECT src/map.cpp src/cell.cpp src/node.cpp src/astarsearch.cpp)
target_include_directories(astar_search PRIVATE)

add_executable(
  utest_astar
  test/utest_astar.cc
)

target_link_libraries(
  utest_astar
  gtest_main
  astar_search
)

include(GoogleTest)
gtest_discover_tests(utest_astar)

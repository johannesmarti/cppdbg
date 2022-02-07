cmake_minimum_required(VERSION 3.10)

# set the project name
project(cppdbg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")
add_executable(play ${SOURCES})

#add_dependencies(play ${SOURCES})

find_package (Boost COMPONENTS unit_test_framework REQUIRED)
#set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED OFF)
set (Boost_USE_STATIC_RUNTIME OFF)
#find_package (Boost COMPONENTS program_options)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

add_executable(cppdbg_test
  test/main.cpp
  test/bitgraph_test.cpp src/bitgraph.cpp
  test/bit_tricks_test.cpp
  test/labeled_bitgraph_test.cpp src/labeled_bitgraph.cpp)

target_link_libraries(cppdbg_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME cppdbg_test COMMAND cppdbg_test)


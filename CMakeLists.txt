cmake_minimum_required(VERSION 3.10)

# set the project name
project(cppdbg)

set(CMAKE_CXX_STANDARD 20)
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

add_executable(bitgraph_test test/bitgraph_test.cpp src/bitgraph.cpp)

target_link_libraries(bitgraph_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME bitgraph_test COMMAND bitgraph_test)


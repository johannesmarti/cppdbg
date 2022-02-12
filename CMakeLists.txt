cmake_minimum_required(VERSION 3.10)

# set the project name
project(cppdbg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_CXX_FLAGS "-Wall -O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories(src)
add_executable(play
  src/play.cpp
  src/bitgraph.cpp
)
add_executable(range
  src/range.cpp
  src/construction_determinism.cpp
  src/question.cpp
  src/labeled_bitgraph.cpp
  src/bitgraph.cpp
)


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
  test/labeled_bitgraph_test.cpp src/labeled_bitgraph.cpp
  test/question_test.cpp src/question.cpp
  test/construction_determinism_test.cpp src/construction_determinism.cpp
)

target_link_libraries(cppdbg_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME cppdbg_test COMMAND cppdbg_test)


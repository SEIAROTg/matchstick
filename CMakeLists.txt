cmake_minimum_required(VERSION 3.3)
project(matchstick)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(LIB_HEADERS matchstick/matchstick.h matchstick/types.h matchstick/types_private.h)
set(LIB_SOURCES matchstick/matchstick.c)
add_library(matchstick ${LIB_HEADERS} ${LIB_SOURCES})

set(TEST_SOURCES test/simple.c)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} matchstick)
endforeach(TEST_SOURCE ${TEST_SOURCES})

cmake_minimum_required(VERSION 3.10)
project(AsyncLoggerExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(SOURCES
	base-interface.cpp
	wrapper.cpp
)

add_executable(AsyncLoggerExample main.cpp ${SOURCES})
#target_link_libraries(AsyncLoggerExample ${GTEST_LIBRARIES} pthread)

add_executable(AsyncLoggerTests perfomance-test.cpp ${SOURCES})
target_link_libraries(AsyncLoggerTests ${GTEST_LIBRARIES} pthread)

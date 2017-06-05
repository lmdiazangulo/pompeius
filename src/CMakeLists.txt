CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
PROJECT(Eternity)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

file(GLOB eternity_src
    "*.h"
    "*.cpp"
	"./core/*.h"
	"./core/*.cpp"
)

ADD_EXECUTABLE(Eternity ${eternity_src})

OPTION(RUN_TESTS "Compile tests" OFF)
if(RUN_TESTS)
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})

	file(COPY ../data DESTINATION ${CMAKE_BINARY_DIR})
	file(GLOB test_src
		"Test/*.h"
		"Test/*.cpp"
		"core/*.h"
		"core/*.cpp"
	)
	
	ADD_EXECUTABLE(Test ${test_src})

	target_link_libraries(Test ${GTEST_LIBRARIES})
endif()




CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
PROJECT(Eternity)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

file(GLOB eternity_src
    "*.h"
    "*.cpp"
	"./core/*.h"
	"./core/*.cpp"
)

if (CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

    check_cxx_compiler_flag("-std=c++11" compiler_supports_cxx11)
    check_cxx_compiler_flag("-std=c++0x" compiler_supports_cxx0X)
    if(compiler_supports_cxx11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(compiler_supports_cxx0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. "
                            "Please use a different C++ compiler.")
    endif()
endif()

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




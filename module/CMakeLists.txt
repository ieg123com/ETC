cmake_minimum_required(VERSION 2.8)
project(module)

include_directories(
    "${PROJECT_SOURCE_DIR}"
)

set(ALL_FILES "")
FILE(GLOB ALL_FILES "./*.cpp" "./*.c" "./*.h" "./*.hpp"
"./*/*.cpp" "./*/*.c" "./*/*.h" "./*/*.hpp"
"./*/*/*.cpp" "./*/*/*.c" "./*/*/*.h" "./*/*/*.hpp")

add_library(module
	${ALL_FILES}
	)
	
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -pthread -std=c++11")
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()
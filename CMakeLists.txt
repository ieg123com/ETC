cmake_minimum_required(VERSION 2.8.9)
project(EtcServer)
set(CMAKE_VERBOSE_MAKEFILE OFF)
# Add the source in project root directory
aux_source_directory(. DIRSRCS)

# Add header file include directories
include_directories(./ ./include ./server ./libgo ./redis ./module)
include_directories(./wepoll/include ./wepoll/src ./wepoll/src/regular ./wepoll/src/combined ./etc)

# Add block directories
#add_subdirectory(server)
add_subdirectory(libgo)
add_subdirectory(etc)
add_subdirectory(server)
add_subdirectory(redis)
add_subdirectory(module)
add_subdirectory(test)

if(MSVC)
	add_subdirectory(wepoll)

	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
#	add_subdirectory(hiredis/win)
else()
#	add_subdirectory(hiredis/linux)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++11)
endif()

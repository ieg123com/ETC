cmake_minimum_required(VERSION 2.8.9)
project(EtcServer)
set(CMAKE_VERBOSE_MAKEFILE OFF)
# Add the source in project root directory
aux_source_directory(. DIRSRCS)

# Add header file include directories
include_directories(./ ./include ./hotfix ./libgo ./redis ./module ./protobuf)
include_directories(./wepoll/include ./wepoll/src ./wepoll/src/regular ./wepoll/src/combined ./model)

# Add block directories
add_subdirectory(libgo)
add_subdirectory(model)
add_subdirectory(hotfix)
add_subdirectory(app)
add_subdirectory(protobuf)
add_subdirectory(redis)
add_subdirectory(test)


if(MSVC)
	add_subdirectory(wepoll)

	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE
    PATH "Directory where all the .lib files are
	dumped." FORCE)
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE
    PATH "Directory where .exe and .dll files are dumped." FORCE)
#	add_subdirectory(hiredis/win)
else()
#	add_subdirectory(hiredis/linux)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++11)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS On)
cmake_minimum_required(VERSION 2.8.9)
project(EtcServer)
set(CMAKE_VERBOSE_MAKEFILE OFF)
# Add the source in project root directory
aux_source_directory(. DIRSRCS)

# Add header file include directories
include_directories(./)
include_directories(./Libs ./Libs/include ./Libs/libgo ./Libs/redis ./Libs/protobuf )
include_directories(./Libs/wepoll/include ./Libs/wepoll/src ./Libs/wepoll/src/regular ./Libs/wepoll/src/combined )
include_directories(./Server ./Server/app ./Server/hotfix ./Server/model)
include_directories(./ThirdParty ./ThirdParty/config_build)



# Add block directories
add_subdirectory(Libs/libgo)
add_subdirectory(Libs/protobuf)
add_subdirectory(Libs/redis)

add_subdirectory(Server/model)
add_subdirectory(Server/hotfix)
add_subdirectory(Server/app)

add_subdirectory(ThirdParty/config_build)
add_subdirectory(Test)


if(MSVC)
	add_subdirectory(Libs/wepoll)

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

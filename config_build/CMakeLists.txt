cmake_minimum_required(VERSION 2.8.9)
project(config_build)


link_directories(../libs/xlnt)
link_directories(../libs/mysql)

#=================================基础加载================================
set(ALL_OBJECT "")
 
#main
set(MAIN_FILES "")
FILE(GLOB MAIN_FILES "./*.cpp" "./*.h")

set(JSON_FILES "")
FILE(GLOB JSON_FILES "./json/*.c" "./json/*.cpp" "./json/*.h" "./json/*.hpp")

set(STRING_FILES "")
FILE(GLOB STRING_FILES "./string/*.cpp" "./string/*.h")

source_group(\\ FILES ${MAIN_FILES} )
source_group(json FILES ${JSON_FILES} )
source_group(string FILES ${STRING_FILES} )


list(APPEND ALL_OBJECT
	${MAIN_FILES}
	${JSON_FILES}
	${STRING_FILES})



# Target
add_executable(config_build
	${ALL_OBJECT})


if(MSVC)
	target_link_libraries(config_build xlnt model)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_SPDLOG_ACTIVE_LEVEL)
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()

cmake_minimum_required(VERSION 2.8.9)
project(test)


include_directories(./ ../libgo)
link_directories(../libs/mysql)

include_directories(../model/etc ../model/etc/common ../model/etc/interface ../model/etc/kernel ../model/etc/system)
include_directories(../model/base)
include_directories(../model/config)


#=================================基础服务加载================================
set(ALL_OBJECT "")
 
#服务底层
set(MAIN_FILES "")
FILE(GLOB MAIN_FILES "./*.cpp" "./*.h")


source_group(main FILES ${MAIN_FILES} )



list(APPEND ALL_OBJECT
	${MAIN_FILES})






# Target
add_executable(test
	${ALL_OBJECT})


if(MSVC)
	target_link_libraries(test libmysql libgo ws2_32 wepoll redis model)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_SPDLOG_ACTIVE_LEVEL)
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
	target_link_libraries(test mysqlclient libgo)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()

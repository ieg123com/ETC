cmake_minimum_required(VERSION 2.8.9)
project(server)


include_directories(./ ../libgo)
link_directories(../libs/mysql)

include_directories(../etc/etc ../etc/etc/common ../etc/etc/interface ../etc/etc/kernel ../etc/etc/system)
include_directories(../etc/base)
include_directories(../etc/config)


#=================================基础服务加载================================
set(ALL_OBJECT "")
 
#服务底层
set(MAIN_FILES "")
FILE(GLOB MAIN_FILES "./main/*.cpp" "./main/*.h")


source_group(main FILES ${MAIN_FILES} )



list(APPEND ALL_OBJECT
	${MAIN_FILES})


#========================Config加载==============================

include_directories(./config)
#config
set(CONFIG_FILES "")
FILE(GLOB CONFIG_FILES "./config/*.cpp" "./config/*.h")


source_group(config						FILES ${CONFIG_FILES})

LIST(APPEND ALL_OBJECT
	${CONFIG_FILES}
	)


#========================网络模块==============================

# 基础网络组件
set(NET_FILES "")
FILE(GLOB NET_FILES "./net/*.cpp" "./net/*.h")

# wepoll
set(NET_WEPOLL_FILES "")
FILE(GLOB NET_WEPOLL_FILES "./net/tcp/wepoll/*.cpp" "./net/tcp/wepoll/*.h")


source_group(net						FILES ${NET_FILES})
source_group(net\\tcp\\wepoll			FILES ${NET_WEPOLL_FILES})

LIST(APPEND ALL_OBJECT
	${NET_FILES}
	${NET_WEPOLL_FILES})




# Target
add_executable(server
	${ALL_OBJECT})


if(MSVC)
	target_link_libraries(server libmysql libgo_static ws2_32 wepoll redis module etc)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_SPDLOG_ACTIVE_LEVEL)
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
	target_link_libraries(server mysqlclient libgo)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()

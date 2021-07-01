cmake_minimum_required(VERSION 2.8.9)
project(etc)


include_directories(./ ../libgo)
link_directories(../libs/mysql)

#=================================基础服务加载================================
set(ALL_OBJECT "")
 

#========================ETC加载==============================

include_directories(./etc ./etc/common ./etc/interface ./etc/kernel ./etc/system)

#etc
set(ETC_FILES "")
FILE(GLOB ETC_FILES "./etc/*.cpp" "./etc/*.h")

#etc核心
set(ETC_KERNEL_FILES "")
FILE(GLOB ETC_KERNEL_FILES "./etc/kernel/*.cpp" "./etc/kernel/*.h")

#事件
set(ETC_COMMON_EVENT_FILES "")
FILE(GLOB ETC_COMMON_EVENT_FILES "./etc/kernel/event/*.cpp" "./etc/kernel/event/*.h")

#etc系统
set(ETC_SYSTEM_FILES "")
FILE(GLOB ETC_SYSTEM_FILES "./etc/system/*.cpp" "./etc/system/*.h")

#计时器
set(ETC_COMMON_TIMER_FILES "")
FILE(GLOB ETC_COMMON_TIMER_FILES "./etc/common/timer/*.cpp" "./etc/common/timer/*.h")

#协程
set(ETC_COMMON_COROUTINE_FILES "")
FILE(GLOB ETC_COMMON_COROUTINE_FILES "./etc/common/coroutine/*.cpp" "./etc/common/coroutine/*.h")

#协程(异步)
set(ETC_COMMON_COROUTINE_ASYNC_FILES "")
FILE(GLOB ETC_COMMON_COROUTINE_ASYNC_FILES "./etc/common/coroutine/async/*.cpp" "./etc/common/coroutine/async/*.h")

#AOI
set(ETC_COMMON_AOI_FILES "")
FILE(GLOB ETC_COMMON_AOI_FILES "./etc/common/aoi/*.cpp" "./etc/common/aoi/*.h")

#AOI用的跳表
set(ETC_COMMON_SKIP_LIST_FILES "")
FILE(GLOB ETC_COMMON_SKIP_LIST_FILES "./etc/common/aoi/skip_list/*.cpp" "./etc/common/aoi/skip_list/*.h")


 



source_group(etc							FILES ${ETC_FILES})
source_group(etc\\kernel					FILES ${ETC_KERNEL_FILES})
source_group(etc\\system					FILES ${ETC_SYSTEM_FILES})
source_group(etc\\kernel\\event				FILES ${ETC_COMMON_EVENT_FILES})
source_group(etc\\common\\timer				FILES ${ETC_COMMON_TIMER_FILES})
source_group(etc\\common\\coroutine			FILES ${ETC_COMMON_COROUTINE_FILES})
source_group(etc\\common\\coroutine\\async	FILES ${ETC_COMMON_COROUTINE_ASYNC_FILES})
source_group(etc\\common\\aoi				FILES ${ETC_COMMON_AOI_FILES})
source_group(etc\\common\\aoi\\skip_list	FILES ${ETC_COMMON_SKIP_LIST_FILES})

LIST(APPEND ALL_OBJECT
	${ETC_FILES}
	${ETC_KERNEL_FILES}
	${ETC_SYSTEM_FILES}
	${ETC_COMMON_EVENT_FILES}
	${ETC_COMMON_TIMER_FILES}
	${ETC_COMMON_COROUTINE_FILES}
	${ETC_COMMON_COROUTINE_ASYNC_FILES}
	${ETC_COMMON_AOI_FILES}
	${ETC_COMMON_SKIP_LIST_FILES})



#========================基础模块==============================

include_directories(./base)

#日志
set(BASE_LOG_FILES "")
FILE(GLOB BASE_LOG_FILES "./base/log/*.cpp" "./base/log/*.h")


source_group(base\\log					FILES ${BASE_LOG_FILES})

LIST(APPEND ALL_OBJECT
	${BASE_LOG_FILES})

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


#========================Module==============================

# 基础网络组件
set(MODULE_FILES "")
FILE(GLOB MODULE_FILES "./module/*.cpp" "./module/*.h")

# actor
set(MODULE_ACTOR_FILES "")
FILE(GLOB MODULE_ACTOR_FILES "./module/actor/*.cpp" "./module/actor/*.h")


source_group(module						FILES ${MODULE_FILES})
source_group(module\\actor				FILES ${MODULE_ACTOR_FILES})

LIST(APPEND ALL_OBJECT
	${MODULE_FILES}
	${MODULE_ACTOR_FILES})


# Target
add_library(etc
	${ALL_OBJECT})


if(MSVC)
	target_link_libraries(etc libmysql libgo_static ws2_32 wepoll redis module)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_SPDLOG_ACTIVE_LEVEL)
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
	target_link_libraries(etc mysqlclient libgo)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()

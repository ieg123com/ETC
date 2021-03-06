cmake_minimum_required(VERSION 2.8.9)
project(model)


link_directories(../../Libs/libs/mysql)

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

#接口
set(ETC_INTERFACE_FILES "")
FILE(GLOB ETC_INTERFACE_FILES "./etc/interface/*.cpp" "./etc/interface/*.h")

#etc系统
set(ETC_SYSTEM_FILES "")
FILE(GLOB ETC_SYSTEM_FILES "./etc/system/*.cpp" "./etc/system/*.h")

#entity
set(ETC_ENTITY_FILES "")
FILE(GLOB ETC_ENTITY_FILES "./etc/entity/*.cpp" "./etc/entity/*.h")

#计时器
set(ETC_COMMON_TIMER_FILES "")
FILE(GLOB ETC_COMMON_TIMER_FILES "./etc/common/timer/*.cpp" "./etc/common/timer/*.h")

#AOI
set(ETC_COMMON_AOI_FILES "")
FILE(GLOB ETC_COMMON_AOI_FILES "./etc/common/aoi/*.cpp" "./etc/common/aoi/*.h")

#AOI用的跳表
set(ETC_COMMON_SKIP_LIST_FILES "")
FILE(GLOB ETC_COMMON_SKIP_LIST_FILES "./etc/common/aoi/skip_list/*.cpp" "./etc/common/aoi/skip_list/*.h")


 



source_group(etc							FILES ${ETC_FILES})
source_group(etc\\kernel					FILES ${ETC_KERNEL_FILES})
source_group(etc\\system					FILES ${ETC_SYSTEM_FILES})
source_group(etc\\entity					FILES ${ETC_ENTITY_FILES})
source_group(etc\\interface					FILES ${ETC_INTERFACE_FILES})
source_group(etc\\kernel\\event				FILES ${ETC_COMMON_EVENT_FILES})
source_group(etc\\common\\timer				FILES ${ETC_COMMON_TIMER_FILES})
source_group(etc\\common\\aoi				FILES ${ETC_COMMON_AOI_FILES})
source_group(etc\\common\\aoi\\skip_list	FILES ${ETC_COMMON_SKIP_LIST_FILES})

LIST(APPEND ALL_OBJECT
	${ETC_FILES}
	${ETC_KERNEL_FILES}
	${ETC_SYSTEM_FILES}
	${ETC_ENTITY_FILES}
	${ETC_INTERFACE_FILES}
	${ETC_COMMON_EVENT_FILES}
	${ETC_COMMON_TIMER_FILES}
	${ETC_COMMON_AOI_FILES}
	${ETC_COMMON_SKIP_LIST_FILES})



#========================基础模块==============================

include_directories(./base)

#日志
set(BASE_FILES "")
FILE(GLOB BASE_FILES "./base/*.cpp" "./base/*.h")

#日志
set(BASE_LOG_FILES "")
FILE(GLOB BASE_LOG_FILES "./base/log/*.cpp" "./base/log/*.h")

#单例模式
set(BASE_SINGLE_FILES "")
FILE(GLOB BASE_SINGLE_FILES "./base/single/*.cpp" "./base/single/*.h")

#对象类型
set(BASE_TYPE_FILES "")
FILE(GLOB BASE_TYPE_FILES "./base/type/*.cpp" "./base/type/*.h")

#反射机制
set(BASE_REFLECTION_FILES "")
FILE(GLOB BASE_REFLECTION_FILES "./base/reflection/*.cpp" "./base/reflection/*.h")

#属性基础
set(BASE_ATTRIBUTE_FILES "")
FILE(GLOB BASE_ATTRIBUTE_FILES "./base/attribute/*.cpp" "./base/attribute/*.h")

#异步
set(BASE_ASYNC_FILES "")
FILE(GLOB BASE_ASYNC_FILES "./base/async/*.cpp" "./base/async/*.h")

#线程
set(BASE_THREAD_FILES "")
FILE(GLOB BASE_THREAD_FILES "./base/thread/*.cpp" "./base/thread/*.h")

#单例模式
set(BASE_SINGLE_FILES "")
FILE(GLOB BASE_SINGLE_FILES "./base/single/*.cpp" "./base/single/*.h")

#helper
set(BASE_HELPER_FILES "")
FILE(GLOB BASE_HELPER_FILES "./base/helper/*.cpp" "./base/helper/*.h")

#dll helper
set(BASE_HELPER_DLL_FILES "")
FILE(GLOB BASE_HELPER_DLL_FILES "./base/helper/dll/*.cpp" "./base/helper/dll/*.h")

#hotfix helper
set(BASE_HELPER_HOTFIX_FILES "")
FILE(GLOB BASE_HELPER_HOTFIX_FILES "./base/helper/hotfix/*.cpp" "./base/helper/hotfix/*.h")


source_group(base						FILES ${BASE_FILES})
source_group(base\\log					FILES ${BASE_LOG_FILES})
source_group(base\\type					FILES ${BASE_TYPE_FILES})
source_group(base\\reflection			FILES ${BASE_REFLECTION_FILES})
source_group(base\\attribute			FILES ${BASE_ATTRIBUTE_FILES})
source_group(base\\task					FILES ${BASE_TASK_FILES})
source_group(base\\async				FILES ${BASE_ASYNC_FILES})
source_group(base\\thread				FILES ${BASE_THREAD_FILES})
source_group(base\\single				FILES ${BASE_SINGLE_FILES})
source_group(base\\helper				FILES ${BASE_HELPER_FILES})
source_group(base\\helper\\dll			FILES ${BASE_HELPER_DLL_FILES})
source_group(base\\helper\\hotfix		FILES ${BASE_HELPER_HOTFIX_FILES})

LIST(APPEND ALL_OBJECT
	${BASE_FILES}
	${BASE_LOG_FILES}
	${BASE_TYPE_FILES}
	${BASE_REFLECTION_FILES}
	${BASE_ATTRIBUTE_FILES}
	${BASE_TASK_FILES}
	${BASE_ASYNC_FILES}
	${BASE_THREAD_FILES}
	${BASE_SINGLE_FILES}
	${BASE_HELPER_FILES}
	${BASE_HELPER_DLL_FILES}
	${BASE_HELPER_HOTFIX_FILES})

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

# tcp
set(NET_TCP_FILES "")
FILE(GLOB NET_TCP_FILES "./net/tcp/*.cpp" "./net/tcp/*.h")

# wepoll
set(NET_WEPOLL_FILES "")
FILE(GLOB NET_WEPOLL_FILES "./net/tcp/wepoll/*.cpp" "./net/tcp/wepoll/*.h")


source_group(net						FILES ${NET_FILES})
source_group(net\\tcp					FILES ${NET_TCP_FILES})
source_group(net\\tcp\\wepoll			FILES ${NET_WEPOLL_FILES})

LIST(APPEND ALL_OBJECT
	${NET_FILES}
	${NET_TCP_FILES}
	${NET_WEPOLL_FILES})


#========================Module==============================

# 基础网络组件
set(MODULE_FILES "")
FILE(GLOB MODULE_FILES "./module/*.cpp" "./module/*.h")

# entity
set(MODULE_ENTITY_FILES "")
FILE(GLOB MODULE_ENTITY_FILES "./module/entity/*.cpp" "./module/entity/*.h")

# actor
set(MODULE_ACTOR_FILES "")
FILE(GLOB MODULE_ACTOR_FILES "./module/actor/*.cpp" "./module/actor/*.h")

# actorlocation
set(MODULE_ACTOR_LOCATION_FILES "")
FILE(GLOB MODULE_ACTOR_LOCATION_FILES "./module/actorlocation/*.cpp" "./module/actorlocation/*.h")

# memory
set(MODULE_MEMORY_FILES "")
FILE(GLOB MODULE_MEMORY_FILES "./module/memory/*.cpp" "./module/memory/*.h")


# message
set(MODULE_MESSAGE_FILES "")
FILE(GLOB MODULE_MESSAGE_FILES "./module/message/*.cpp" "./module/message/*.h")

# message interface
set(MODULE_MESSAGE_INTERFACE_FILES "")
FILE(GLOB MODULE_MESSAGE_INTERFACE_FILES "./module/message/interface/*.cpp" "./module/message/interface/*.h")

# coroutine
set(MODULE_COROUTINE_FILES "")
FILE(GLOB MODULE_COROUTINE_FILES "./module/coroutine/*.cpp" "./module/coroutine/*.h")

# other
set(MODULE_OTHER_FILES "")
FILE(GLOB MODULE_OTHER_FILES "./module/other/*.cpp" "./module/other/*.h")

# component
set(MODULE_COMPONENT_FILES "")
FILE(GLOB MODULE_COMPONENT_FILES "./module/component/*.cpp" "./module/component/*.h")

# component config
set(MODULE_COMPONENT_CONFIG_FILES "")
FILE(GLOB MODULE_COMPONENT_CONFIG_FILES "./module/component/config/*.cpp" "./module/component/config/*.h")

# db
set(MODULE_DB_FILES "")
FILE(GLOB MODULE_DB_FILES "./module/db/*.cpp" "./module/db/*.h")



source_group(module						FILES ${MODULE_FILES})
source_group(module\\entity				FILES ${MODULE_ENTITY_FILES})
source_group(module\\actor				FILES ${MODULE_ACTOR_FILES})
source_group(module\\actorlocation		FILES ${MODULE_ACTOR_LOCATION_FILES})
source_group(module\\memory				FILES ${MODULE_MEMORY_FILES})
source_group(module\\message			FILES ${MODULE_MESSAGE_FILES})
source_group(module\\message\\interface	FILES ${MODULE_MESSAGE_INTERFACE_FILES})
source_group(module\\coroutine			FILES ${MODULE_COROUTINE_FILES})
source_group(module\\other				FILES ${MODULE_OTHER_FILES})
source_group(module\\component			FILES ${MODULE_COMPONENT_FILES})
source_group(module\\component\\config	FILES ${MODULE_COMPONENT_CONFIG_FILES})
source_group(module\\db					FILES ${MODULE_DB_FILES})


LIST(APPEND ALL_OBJECT
	${MODULE_FILES}
	${MODULE_ENTITY_FILES}
	${MODULE_ACTOR_FILES}
	${MODULE_ACTOR_LOCATION_FILES}
	${MODULE_MEMORY_FILES}
	${MODULE_MESSAGE_FILES}
	${MODULE_MESSAGE_INTERFACE_FILES}
	${MODULE_COROUTINE_FILES}
	${MODULE_OTHER_FILES}
	${MODULE_COMPONENT_FILES}
	${MODULE_COMPONENT_CONFIG_FILES}
	${MODULE_DB_FILES})

#========================协议==============================

# 通信协议
set(PROTO_FILES "")
FILE(GLOB PROTO_FILES "./proto/*.cpp" "./proto/*.h")

set(PROTO_OPCODE_FILES "")
FILE(GLOB PROTO_OPCODE_FILES "./proto/opcode/*.cpp" "./proto/opcode/*.h")


source_group(proto						FILES ${PROTO_FILES})
source_group(proto\\opcode				FILES ${PROTO_OPCODE_FILES})


LIST(APPEND ALL_OBJECT
	${PROTO_FILES}
	${PROTO_OPCODE_FILES})

#========================其他==============================
include_directories(./other)

set(OTHER_FILES "")
FILE(GLOB OTHER_FILES "./other/*.cpp" "./other/*.c" "./other/*.h" "./other/*.hpp"
"./other/*/*.cpp" "./other/*/*.c" "./other/*/*.h" "./other/*/*.hpp"
"./other/*/*/*.cpp" "./other/*/*/*.c" "./other/*/*/*.h" "./other/*/*/*.hpp")

source_group(other						FILES ${OTHER_FILES})

LIST(APPEND ALL_OBJECT
	${OTHER_FILES})


#========================Demo==============================
include_directories(./demo)

set(DEMO_FILES "")
FILE(GLOB DEMO_FILES "./demo/*.h" "./demo/*.cpp")

set(DEMO_ENTITY_FILES "")
FILE(GLOB DEMO_ENTITY_FILES "./demo/Entity/*.h")

source_group(demo								FILES ${DEMO_FILES})
source_group(demo\\Entity						FILES ${DEMO_ENTITY_FILES})

LIST(APPEND ALL_OBJECT
	${DEMO_FILES}
	${DEMO_ENTITY_FILES})
 

# Target
add_library(model
	${ALL_OBJECT})
set_target_properties(model PROPERTIES FOLDER "Server")

if(MSVC)
	target_link_libraries(model libmysql libgo ws2_32 wepoll redis protobuf)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_SPDLOG_ACTIVE_LEVEL)
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /EHa")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /EHa")
	add_definitions(-DLIBETC_BUILD -DLIBASYNC_BUILD)
else() 
	target_link_libraries(model mysqlclient libgo)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()

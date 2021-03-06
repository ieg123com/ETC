cmake_minimum_required(VERSION 2.8.9)
project(app)


link_directories(../../Libs/libs/mysql)

include_directories(../model/etc ../model/etc/common ../model/etc/interface ../model/etc/kernel ../model/etc/system)
include_directories(../model/base)
include_directories(../model/config)


#=================================基础服务加载================================
set(ALL_OBJECT "")
 
#基础
set(BASE_FILES "")
FILE(GLOB BASE_FILES "./base/*.cpp" "./base/*.h")


source_group(base FILES ${BASE_FILES} )



list(APPEND ALL_OBJECT
	${BASE_FILES})


#========================Config加载==============================

include_directories(./config)
#config
set(CONFIG_FILES "")
FILE(GLOB CONFIG_FILES "./config/*.cpp" "./config/*.h")
 

source_group(config						FILES ${CONFIG_FILES})

LIST(APPEND ALL_OBJECT
	${CONFIG_FILES}
	)


#========================模块加载==============================

# 基础网络组件
set(MODULE_FILES "")
FILE(GLOB MODULE_FILES "./module/*.cpp" "./module/*.h")

# Message组件
set(MODULE_MESSAGE_FILES "")
FILE(GLOB MODULE_MESSAGE_FILES "./module/message/*.cpp" "./module/message/*.h")

# Message handler 组件
set(MODULE_MESSAGE_HANDLER_FILES "")
FILE(GLOB MODULE_MESSAGE_HANDLER_FILES "./module/message/handler/*.cpp" "./module/message/handler/*.h")

# Component
set(MODULE_COMPONENT_FILES "")
FILE(GLOB MODULE_COMPONENT_FILES "./module/component/*.cpp" "./module/component/*.h")

# Component Config
set(MODULE_COMPONENT_CONFIG_FILES "")
FILE(GLOB MODULE_COMPONENT_CONFIG_FILES "./module/component/config/*.cpp" "./module/component/config/*.h")

# handler
set(MODULE_HANDLER_FILES "")
FILE(GLOB MODULE_HANDLER_FILES "./module/handler/*.cpp" "./module/handler/*.h")

# handler login
set(MODULE_HANDLER_LOGIN_FILES "")
FILE(GLOB MODULE_HANDLER_LOGIN_FILES "./module/handler/login/*.cpp" "./module/handler/login/*.h")

# handler etc_msg
set(MODULE_HANDLER_ETC_MSG_FILES "")
FILE(GLOB MODULE_HANDLER_ETC_MSG_FILES "./module/handler/etc_msg/*.cpp" "./module/handler/etc_msg/*.h")

# init
set(MODULE_INIT_FILES "")
FILE(GLOB MODULE_INIT_FILES "./module/init/*.cpp" "./module/init/*.h")

# actor
set(MODULE_ACTOR_FILES "")
FILE(GLOB MODULE_ACTOR_FILES "./module/actor/*.cpp" "./module/actor/*.h")
 
# actor handler
set(MODULE_ACTOR_HANDLER_FILES "")
FILE(GLOB MODULE_ACTOR_HANDLER_FILES "./module/actor/handler/*.cpp" "./module/actor/handler/*.h")


# actor location
set(MODULE_ACTOR_LOCATION_FILES "")
FILE(GLOB MODULE_ACTOR_LOCATION_FILES "./module/actorlocation/*.cpp" "./module/actorlocation/*.h")

# entity
set(MODULE_ENTITY_FILES "")
FILE(GLOB MODULE_ENTITY_FILES "./module/entity/*.cpp" "./module/entity/*.h")

# db
set(MODULE_DB_FILES "")
FILE(GLOB MODULE_DB_FILES "./module/db/*.cpp" "./module/db/*.h")


source_group(module						FILES ${MODULE_FILES})
source_group(module\\message			FILES ${MODULE_MESSAGE_FILES})
source_group(module\\message\\handler	FILES ${MODULE_MESSAGE_HANDLER_FILES})
source_group(module\\component			FILES ${MODULE_COMPONENT_FILES})
source_group(module\\component\\config	FILES ${MODULE_COMPONENT_CONFIG_FILES})
source_group(module\\handler			FILES ${MODULE_HANDLER_FILES})
source_group(module\\handler\\login		FILES ${MODULE_HANDLER_LOGIN_FILES})
source_group(module\\handler\\etc_msg	FILES ${MODULE_HANDLER_ETC_MSG_FILES})
source_group(module\\init				FILES ${MODULE_INIT_FILES})
source_group(module\\actor				FILES ${MODULE_ACTOR_FILES})
source_group(module\\actor\\handler		FILES ${MODULE_ACTOR_HANDLER_FILES})
source_group(module\\actorlocation		FILES ${MODULE_ACTOR_LOCATION_FILES})
source_group(module\\entity				FILES ${MODULE_ENTITY_FILES})
source_group(module\\db					FILES ${MODULE_DB_FILES})


LIST(APPEND ALL_OBJECT
	${MODULE_FILES}
	${MODULE_MESSAGE_FILES}
	${MODULE_MESSAGE_HANDLER_FILES}
	${MODULE_COMPONENT_FILES}
	${MODULE_COMPONENT_CONFIG_FILES}
	${MODULE_HANDLER_FILES}
	${MODULE_HANDLER_LOGIN_FILES}
	${MODULE_HANDLER_ETC_MSG_FILES}
	${MODULE_INIT_FILES}
	${MODULE_ACTOR_FILES}
	${MODULE_ACTOR_HANDLER_FILES}
	${MODULE_ACTOR_LOCATION_FILES}
	${MODULE_ENTITY_FILES}
	${MODULE_DB_FILES})

#========================Net加载==============================

# net
set(NET_FILES "")
FILE(GLOB NET_FILES "./net/*.cpp" "./net/*.h")

# net tcp
set(NET_TCP_FILES "")
FILE(GLOB NET_TCP_FILES "./net/tcp/*.cpp" "./net/tcp/*.h")

# net tcp wepoll
set(NET_TCP_WEPOLL_FILES "")
FILE(GLOB NET_TCP_WEPOLL_FILES "./net/tcp/wepoll/*.cpp" "./net/tcp/wepoll/*.h")


source_group(net								FILES ${NET_FILES})
source_group(net\\tcp							FILES ${NET_TCP_FILES})
source_group(net\\tcp\\wepoll					FILES ${NET_TCP_WEPOLL_FILES})

LIST(APPEND ALL_OBJECT
	${NET_FILES}
	${NET_TCP_FILES}
	${NET_TCP_WEPOLL_FILES})

#========================Demo加载==============================

# demo message handler
set(DEMO_MESSAGE_HANDLER_FILES "")
FILE(GLOB DEMO_MESSAGE_HANDLER_FILES "./demo/message/handler/*.cpp")

# demo handler
set(DEMO_HANDLER_FILES "")
FILE(GLOB DEMO_HANDLER_FILES "./demo/handler/*.cpp" "./demo/handler/*.h")

source_group(demo\\message\\handler				FILES ${DEMO_MESSAGE_HANDLER_FILES})
source_group(demo\\handler						FILES ${DEMO_HANDLER_FILES})


LIST(APPEND ALL_OBJECT
	${DEMO_MESSAGE_HANDLER_FILES}
	${DEMO_HANDLER_FILES})




# Target
add_executable(app
	${ALL_OBJECT})
set_target_properties(app PROPERTIES FOLDER "Server") 

if(MSVC)
	target_link_libraries(app libmysql libgo ws2_32 wepoll redis model hotfix)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_SPDLOG_ACTIVE_LEVEL)
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /EHa")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /EHa")

	add_definitions(-DLIBETCREF_STATIC)
			# 测试配置生成
	#add_test(app WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
	add_test(app --AppId=1 --AppType=AllServer)
else()
	target_link_libraries(app mysqlclient libgo)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()

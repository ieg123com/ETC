cmake_minimum_required(VERSION 2.8.9)
project(app)


include_directories(./ ../libgo)
link_directories(../libs/mysql)

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

source_group(module						FILES ${MODULE_FILES})
source_group(module\\message			FILES ${MODULE_MESSAGE_FILES})
source_group(module\\component			FILES ${MODULE_COMPONENT_FILES})
source_group(module\\component\\config	FILES ${MODULE_COMPONENT_CONFIG_FILES})
source_group(module\\handler			FILES ${MODULE_HANDLER_FILES})
source_group(module\\handler\\login		FILES ${MODULE_HANDLER_LOGIN_FILES})
source_group(module\\handler\\etc_msg	FILES ${MODULE_HANDLER_ETC_MSG_FILES})
source_group(module\\init				FILES ${MODULE_INIT_FILES})
source_group(module\\actor				FILES ${MODULE_ACTOR_FILES})
source_group(module\\actor\\handler		FILES ${MODULE_ACTOR_HANDLER_FILES})


LIST(APPEND ALL_OBJECT
	${MODULE_FILES}
	${MODULE_MESSAGE_FILES}
	${MODULE_COMPONENT_FILES}
	${MODULE_COMPONENT_CONFIG_FILES}
	${MODULE_HANDLER_FILES}
	${MODULE_HANDLER_LOGIN_FILES}
	${MODULE_HANDLER_ETC_MSG_FILES}
	${MODULE_INIT_FILES}
	${MODULE_ACTOR_FILES}
	${MODULE_ACTOR_HANDLER_FILES})



# Target
add_executable(app
	${ALL_OBJECT})


if(MSVC)
	target_link_libraries(app libmysql libgo ws2_32 wepoll redis model hotfix)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_SPDLOG_ACTIVE_LEVEL)
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /EHa")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /EHa")
else()
	target_link_libraries(app mysqlclient libgo)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()

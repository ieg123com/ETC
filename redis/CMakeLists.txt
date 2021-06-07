cmake_minimum_required(VERSION 2.8)
project(redis)

include_directories(
    "${PROJECT_SOURCE_DIR}"
)

set(hiredis_dir hiredis)

add_library(redis
	hiredis2.cpp
	eredis.cpp
	${hiredis_dir}/async.c
	${hiredis_dir}/dict.c
	${hiredis_dir}/hiredis.c
	${hiredis_dir}/net.c
	${hiredis_dir}/sds.c
	)
	
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -pthread -std=c++11")
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()
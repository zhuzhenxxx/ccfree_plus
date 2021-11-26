cmake_minimum_required(VERSION 2.7)
project(ccfree)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/yaml-cpp)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/jsoncpp-1.8.4)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/sqlite-3.28.0)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/tinyxml2-7.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include_directories(.)
include_directories(/root/ccfree/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/yaml-cpp/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/jsoncpp-1.8.4/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/sqlite-3.28.0)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdpart/tinyxml2-7.0.1)
link_directories(/root/ccfree/lib)
link_directories(/root/ccfree/lib64)

option(BUILD_TEST "ON for complile test" OFF)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(MySQL REQUIRED)
if(MYSQL_FOUND)
    include_directories(${MYSQL_INCLUDE_DIR})
endif()

find_package(Protobuf)
if(Protobuf_FOUND)
    include_directories(${Protobuf_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
endif()

set(LIB_SRC
    ccfree/address.cc
    ccfree/bytearray.cc
    ccfree/config.cc
    ccfree/db/fox_thread.cc
    ccfree/db/mysql.cc
    ccfree/db/redis.cc
    ccfree/db/sqlite3.cc
    ccfree/ds/bitmap.cc
    ccfree/ds/roaring_bitmap.cc
    ccfree/ds/roaring.c
    ccfree/ds/util.cc
    ccfree/email/email.cc
    ccfree/email/smtp.cc
    ccfree/env.cc
    ccfree/daemon.cc
    ccfree/fd_manager.cc
    ccfree/fiber.cc
    ccfree/http/http.cc
    ccfree/http/http_connection.cc
    ccfree/http/http_parser.cc
    ccfree/http/http_session.cc
    ccfree/http/http_server.cc
    ccfree/http/servlet.cc
    ccfree/http/servlets/config_servlet.cc
    ccfree/http/servlets/status_servlet.cc
    ccfree/http/session_data.cc
    ccfree/http/ws_connection.cc
    ccfree/http/ws_session.cc
    ccfree/http/ws_server.cc
    ccfree/http/ws_servlet.cc
    ccfree/hook.cc
    ccfree/iomanager.cc
    ccfree/library.cc
    ccfree/log.cc
    ccfree/module.cc
    ccfree/mutex.cc
    ccfree/ns/name_server_module.cc
    ccfree/ns/ns_client.cc
    ccfree/ns/ns_protocol.cc
    ccfree/protocol.cc
    ccfree/rock/rock_protocol.cc
    ccfree/rock/rock_server.cc
    ccfree/rock/rock_stream.cc
    ccfree/scheduler.cc
    ccfree/socket.cc
    ccfree/stream.cc
    ccfree/streams/async_socket_stream.cc
    ccfree/streams/socket_stream.cc
    ccfree/streams/load_balance.cc
    ccfree/streams/service_discovery.cc
    ccfree/streams/zlib_stream.cc
    ccfree/tcp_server.cc
    ccfree/timer.cc
    ccfree/thread.cc
    ccfree/util.cc
    ccfree/util/crypto_util.cc
    ccfree/util/json_util.cc
    ccfree/util/hash_util.cc
    ccfree/worker.cc
    ccfree/application.cc
    ccfree/zk_client.cc
    )

ragelmaker(ccfree/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ccfree/http)
ragelmaker(ccfree/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ccfree/http)
ragelmaker(ccfree/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ccfree)

protobufmaker(ccfree/ns/ns_protobuf.proto LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR})
#PROTOBUF_GENERATE_CPP(PB_SRCS PB_HDRS ccfree/ns/ns_protobuf.proto)
#message("****${PB_SRCS}***${PB_HDRS}****")
#list(APPEND LIB_SRC ${PB_SRCS})
#
#message(STATUS ${LIB_SRC})

add_library(ccfree SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(ccfree)
#add_library(ccfree_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (ccfree_static PROPERTIES OUTPUT_NAME "ccfree")

#find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS ${LIBS} ccfree)
#set(LIBS ${LIBS} dl)
#set(LIBS ${LIBS} ${YAMLCPP})
#set(LIBS ${LIBS} ${PTHREAD})

set(LIBS
        ccfree
        dl
        pthread
        yaml-cpp
        jsoncpp
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        event
        hiredis_vip
        mysqlclient_r
        zookeeper_mt
        sqlite3
        tinyxml2
        jemalloc
        )
ccfree_add_executable(test_util "tests/test_util.cc" ccfree "${LIBS}")
ccfree_add_executable(test_hashmultimap "tests/test_hashmultimap.cc" ccfree "${LIBS}")
ccfree_add_executable(test_hashmap "tests/test_hashmap.cc" ccfree "${LIBS}")
ccfree_add_executable(test_dict "tests/test_dict.cc" ccfree "${LIBS}")
ccfree_add_executable(test_array "tests/test_array.cc" ccfree "${LIBS}")
if(BUILD_TEST)
ccfree_add_executable(test1 "tests/test.cc" ccfree "${LIBS}")
ccfree_add_executable(test_config "tests/test_config.cc" ccfree "${LIBS}")
ccfree_add_executable(test_thread "tests/test_thread.cc" ccfree "${LIBS}")
ccfree_add_executable(test_fiber "tests/test_fiber.cc" ccfree "${LIBS}")
ccfree_add_executable(test_scheduler "tests/test_scheduler.cc" ccfree "${LIBS}")
ccfree_add_executable(test_iomanager "tests/test_iomanager.cc" ccfree "${LIBS}")
ccfree_add_executable(test_hook "tests/test_hook.cc" ccfree "${LIBS}")
ccfree_add_executable(test_address "tests/test_address.cc" ccfree "${LIBS}")
ccfree_add_executable(test_socket "tests/test_socket.cc" ccfree "${LIBS}")
ccfree_add_executable(test_bytearray "tests/test_bytearray.cc" ccfree "${LIBS}")
ccfree_add_executable(test_http "tests/test_http.cc" ccfree "${LIBS}")
ccfree_add_executable(test_http_parser "tests/test_http_parser.cc" ccfree "${LIBS}")
ccfree_add_executable(test_tcp_server "tests/test_tcp_server.cc" ccfree "${LIBS}")
ccfree_add_executable(echo_server "examples/echo_server.cc" ccfree "${LIBS}")
ccfree_add_executable(test_http_server "tests/test_http_server.cc" ccfree "${LIBS}")
ccfree_add_executable(test_uri "tests/test_uri.cc" ccfree "${LIBS}")
ccfree_add_executable(my_http_server "samples/my_http_server.cc" ccfree "${LIBS}")

ccfree_add_executable(echo_server_udp "examples/echo_server_udp.cc" ccfree "${LIBS}")
ccfree_add_executable(echo_udp_client "examples/echo_udp_client.cc" ccfree "${LIBS}")

ccfree_add_executable(test_daemon "tests/test_daemon.cc" ccfree "${LIBS}")
ccfree_add_executable(test_env "tests/test_env.cc" ccfree "${LIBS}")
ccfree_add_executable(test_ws_server "tests/test_ws_server.cc" ccfree "${LIBS}")
ccfree_add_executable(test_ws_client "tests/test_ws_client.cc" ccfree "${LIBS}")
ccfree_add_executable(test_application "tests/test_application.cc" ccfree "${LIBS}")

ccfree_add_executable(test_http_connection "tests/test_http_connection.cc" ccfree "${LIBS}")
ccfree_add_executable(test_lru "tests/test_lru.cc" ccfree "${LIBS}")
ccfree_add_executable(test_timed_cache "tests/test_timed_cache.cc" ccfree "${LIBS}")
ccfree_add_executable(test_timed_lru_cache "tests/test_timed_lru_cache.cc" ccfree "${LIBS}")
ccfree_add_executable(test_zlib_stream "tests/test_zlib_stream.cc" ccfree "${LIBS}")

endif()
ccfree_add_executable(test_crypto "tests/test_crypto.cc" ccfree "${LIBS}")
ccfree_add_executable(test_sqlite3 "tests/test_sqlite3.cc" ccfree "${LIBS}")
ccfree_add_executable(test_rock "tests/test_rock.cc" ccfree "${LIBS}")
ccfree_add_executable(test_email  "tests/test_email.cc" ccfree "${LIBS}")
ccfree_add_executable(test_mysql "tests/test_mysql.cc" ccfree "${LIBS}")
ccfree_add_executable(test_nameserver "tests/test_nameserver.cc" ccfree "${LIBS}")
ccfree_add_executable(test_bitmap "tests/test_bitmap.cc" ccfree "${LIBS}")
ccfree_add_executable(test_zkclient "tests/test_zookeeper.cc" ccfree "${LIBS}")
ccfree_add_executable(test_service_discovery "tests/test_service_discovery.cc" ccfree "${LIBS}")

set(ORM_SRCS
    ccfree/orm/table.cc
    ccfree/orm/column.cc
    ccfree/orm/index.cc
    ccfree/orm/orm.cc
    ccfree/orm/util.cc
    )
ccfree_add_executable(orm "${ORM_SRCS}" ccfree "${LIBS}")

add_library(test_module SHARED tests/test_module.cc)

ccfree_add_executable(bin_ccfree "ccfree/main.cc" ccfree "${LIBS}")
set_target_properties(bin_ccfree PROPERTIES OUTPUT_NAME "ccfree")

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/orm_out)
#set(OLIBS ${LIBS} orm_data)
#ccfree_add_executable(test_orm "tests/test_orm.cc" orm_data "${OLIBS}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

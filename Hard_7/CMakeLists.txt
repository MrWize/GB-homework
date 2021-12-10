cmake_minimum_required(VERSION 3.20)
project(Hard_7)

set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
link_directories(${PROTOBUF}/lib)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS cmake-build-debug/class.proto)

set(PROJECT_SRC
        main.cpp
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        cmake-build-debug/StudentsGroup.h)

add_executable(Hard_7 "${PROJECT_SRC}")

target_link_libraries(Hard_7 ${Protobuf_LIBRARIES})
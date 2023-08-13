project(dev-comm-init)

cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ${YOCTO_BUILD})
    set(YOCTO_BUILD ON)
endif()

set(SERVICE_NAME ${CMAKE_PROJECT_NAME}-service)

include_directories(
    include/
)

add_executable(${SERVICE_NAME}
    impl/service/src/main.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(${SERVICE_NAME}
    Threads::Threads
)

target_include_directories( ${SERVICE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/service/include
)

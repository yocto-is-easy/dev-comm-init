project(dev-comm-init)

cmake_minimum_required(VERSION 3.10)

set(SERVICE_NAME ${CMAKE_PROJECT_NAME}-service)

include_directories(
    include/
)

add_executable(${SERVICE_NAME}
    impl/service/src/main.cpp
    impl/service/src/SerialFile.cpp
    impl/service/src/SerialDeviceConfigurator.cpp
    impl/service/src/SerialDeviceMonitor.cpp
    impl/service/src/WifiConfigSetuper.cpp
    impl/service/src/WifiData.cpp
)

find_package(Threads REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${SERVICE_NAME}
    Threads::Threads
    spdlog::spdlog_header_only
)

target_include_directories( ${SERVICE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/service/include
)

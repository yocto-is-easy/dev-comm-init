#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <functional>
#include <chrono>

#include "SerialFile.hpp"

class SerialDeviceMonitor {
public:
    static constexpr std::chrono::milliseconds DEAFULT_WAIT_CONNECTED_TIMEOUT = std::chrono::milliseconds(500);
    static constexpr std::chrono::milliseconds DEAFULT_WAIT_DISCONNECTED_TIMEOUT = std::chrono::milliseconds(100);

private:
    SerialFile serialFile_;
    std::function<void(SerialFile&)> onDeviceConnectedCallback_;
    std::function<void(SerialFile&)> onDeviceDesconnectedCallback_;
    std::chrono::milliseconds waitConnectedTimeout_ = SerialDeviceMonitor::DEAFULT_WAIT_CONNECTED_TIMEOUT;
    std::chrono::milliseconds waitDisconnectedTimeout_ = SerialDeviceMonitor::DEAFULT_WAIT_DISCONNECTED_TIMEOUT;

public:
    SerialDeviceMonitor(SerialFile& serialFile);

    void monitor();
    void setOnDeviceConnectedCallback(std::function<void(SerialFile&)> callback);
    void setOnDeviceDesconnectedCallback(std::function<void(SerialFile&)> callback);

    void setWaitConnectedTimeout(uint64_t timeout);
    void setWaitDisconnectedTimeout(uint64_t timeout);

private:
    void waitConnected();
    void waitDisconnected();
};

#include "SerialDeviceMonitor.hpp"

#include <thread>
#include <chrono>

#include <spdlog/spdlog.h>

SerialDeviceMonitor::SerialDeviceMonitor(SerialFile& serialFile) 
    : serialFile_(serialFile) { }

void SerialDeviceMonitor::monitor() {
    while(true) {
        waitConnected();
        waitDisconnected();
    }
}

void SerialDeviceMonitor::waitConnected() {
    uint64_t waitConnectedCounter = 0;
    while(true) {
        try {
            serialFile_.open();
            if(onDeviceConnectedCallback_) {
                onDeviceConnectedCallback_(serialFile_);
            }
            serialFile_.close();
            break;
        } catch(SerialFileException& e) {
            spdlog::debug("No serial file detected, wait({} - {}ms): {}",
                waitConnectedCounter, waitConnectedTimeout_.count(), e.what());

            std::this_thread::sleep_for(waitConnectedTimeout_);
        }
    }
}

void SerialDeviceMonitor::waitDisconnected() {
    uint64_t waitDisconnectedCounter = 0;
    while(true) {
        try {
            serialFile_.open();
            serialFile_.close();
            spdlog::debug("Serial file still detected, wait({} - {}ms)", 
                waitDisconnectedCounter, waitDisconnectedTimeout_.count());

            std::this_thread::sleep_for(waitDisconnectedTimeout_);
        } catch(SerialFileException& e) {
            if(onDeviceDesconnectedCallback_) {
                onDeviceDesconnectedCallback_(serialFile_);
            }
            break;
        }
    }
}

void SerialDeviceMonitor::setOnDeviceConnectedCallback(std::function<void(SerialFile&)> callback) {
    onDeviceConnectedCallback_ = callback;
}

void SerialDeviceMonitor::setOnDeviceDesconnectedCallback(std::function<void(SerialFile&)> callback) {
    onDeviceDesconnectedCallback_ = callback;
}

void SerialDeviceMonitor::setWaitConnectedTimeout(uint64_t timeout) {
    waitConnectedTimeout_ = std::chrono::milliseconds(timeout);
}

void SerialDeviceMonitor::setWaitDisconnectedTimeout(uint64_t timeout) {
    waitDisconnectedTimeout_ = std::chrono::milliseconds(timeout);
}

#include "SerialDeviceMonitor.hpp"

#include <thread>
#include <chrono>

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
            std::cout
                << "No serial file detected("
                << waitConnectedCounter << " - "
                << waitConnectedTimeout_.count()
                << "ms): " << e.what() << std::endl;
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
            std::cout 
                << "Serial file still detected("
                << waitDisconnectedCounter << " - "
                << waitDisconnectedTimeout_.count()
                << "ms): " << std::endl;

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

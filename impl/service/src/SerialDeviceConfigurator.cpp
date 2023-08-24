#include "SerialDeviceConfigurator.hpp"

#include <spdlog/spdlog.h>

SerialDeviceConfigurator::SerialDeviceConfigurator(SerialDeviceMonitor& serialDeviceMonitor) {
    serialDeviceMonitor.setOnDeviceConnectedCallback([this](SerialFile& serialFile) {
        configure(serialFile);
    });
}

void SerialDeviceConfigurator::configure(SerialFile& serialFile) {
    spdlog::info("Configuring serial file: {}", serialFile.getPath());

    for (auto configSetuper : configSetupers_) {
        configSetuper->setup(serialFile);
    }
}

void SerialDeviceConfigurator::addConfigSetuper(std::shared_ptr<IConfigSetuper> configSetuper) {
    configSetupers_.push_back(configSetuper);
}

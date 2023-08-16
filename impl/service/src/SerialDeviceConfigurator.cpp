#include "SerialDeviceConfigurator.hpp"

SerialDeviceConfigurator::SerialDeviceConfigurator(SerialDeviceMonitor& serialDeviceMonitor) {
    serialDeviceMonitor.setOnDeviceConnectedCallback([this](SerialFile& serialFile) {
        configure(serialFile);
    });
}

void SerialDeviceConfigurator::configure(SerialFile& serialFile) {
    std::cout << "Configuring serial file: " << serialFile.getPath() << std::endl;

    for (auto configSetuper : configSetupers_) {
        configSetuper->setup(serialFile);
    }
}

void SerialDeviceConfigurator::addConfigSetuper(std::shared_ptr<IConfigSetuper> configSetuper) {
    configSetupers_.push_back(configSetuper);
}

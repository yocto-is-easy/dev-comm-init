#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "IConfigSetuper.hpp"
#include "SerialDeviceMonitor.hpp"

class SerialDeviceConfigurator {
public:
    SerialDeviceConfigurator(SerialDeviceMonitor& serialDeviceMonitor);

    void configure(SerialFile& serialFile);
    void addConfigSetuper(std::shared_ptr<IConfigSetuper> configSetuper);

private:
    std::vector<std::shared_ptr<IConfigSetuper>> configSetupers_;
};

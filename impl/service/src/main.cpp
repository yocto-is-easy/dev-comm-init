#include <iostream>
#include "SerialFile.hpp"
#include "SerialDeviceMonitor.hpp"
#include "SerialDeviceConfigurator.hpp"
#include "WifiConfigSetuper.hpp"

int main() {
    SerialFile serialFile("/dev/ttyUSB0", B115200);

    SerialDeviceMonitor serialDeviceMonitor(serialFile);
    SerialDeviceConfigurator serialDeviceConfigurator(serialDeviceMonitor);
    serialDeviceConfigurator.addConfigSetuper(std::make_shared<WifiConfigSetuper>());

    serialDeviceMonitor.monitor();

    return 0;
}

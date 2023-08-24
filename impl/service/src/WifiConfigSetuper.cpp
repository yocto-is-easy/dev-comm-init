#include "WifiConfigSetuper.hpp"

#include <spdlog/spdlog.h>

WifiConfigSetuper::WifiConfigSetuper() {
}

void WifiConfigSetuper::setup(SerialFile& serialFile) {
    spdlog::info("WifiConfigSetuper::setup {} - {}", serialFile.getPath(), serialFile.getBaudrate());
    
    spdlog::info("WifiConfigSetuper::setup ssid: {}", wifiData_.ssid());
    spdlog::info("WifiConfigSetuper::setup password: {}", wifiData_.password());
}
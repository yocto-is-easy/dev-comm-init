#include "WifiConfigSetuper.hpp"

#include <spdlog/spdlog.h>

WifiConfigSetuper::WifiConfigSetuper() {
}

void WifiConfigSetuper::setup(SerialFile& serialFile) {
    spdlog::info("WifiConfigSetuper::setup {} - {}", serialFile.getPath(), serialFile.getBaudrate());
    
    spdlog::info("WifiConfigSetuper::setup ssid: {}", wifiData_.ssid());

    try {
        bool isReady = waitForMsdReady(serialFile);
        if(!isReady) {
            spdlog::error("MSD is not ready for configuration");
            return;
        }

        const std::string wifiConfig = prepareWifiConfig();
        sendWifiConfig(serialFile, wifiConfig);

        bool isConfigured = waitForMsdConfigured(serialFile);
        if(!isConfigured) {
            spdlog::error("MSD is not configured");
            return;
        }
    } catch (const std::exception& e) {
        spdlog::error("Could not operate with serial device: {}", e.what());
    }
}

std::string WifiConfigSetuper::prepareWifiConfig() {
    return "[" + wifiData_.ssid() + "$" + wifiData_.password() + "]";
}

bool WifiConfigSetuper::waitForString(SerialFile& serialFile, const std::string& str) {
    int i = 0;
    int maxTries = WAIT_STR_MAX_DELAY_MS / WAIT_STR_DELAY_MS;
    while(true) {
        if(i >= maxTries) {
            return false;
        }
        try {
            std::string line = serialFile.readLine();
            spdlog::info("WifiConfigSetuper::waitForString - line: {}", line);

            size_t n = line.find(str);
            if (n != std::string::npos) {
                break;
            }
        } catch(SerialFileException& e) {
            spdlog::warn("Could not read line from serial file({}): {}", i, e.what());
            i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_STR_DELAY_MS));
        }
    }
    return true;
}

bool WifiConfigSetuper::waitForMsdReady(SerialFile& serialFile) {
    spdlog::info("WifiConfigSetuper::waitForMsdReady");
    bool res = waitForString(serialFile, MSD_READY_MSG);
    if(res) {
        spdlog::info("Found out that MSD is ready for configuration");
    } else {
        spdlog::error("Could not find out that MSD is ready for configuration");
    }
    return res;
}

bool WifiConfigSetuper::waitForMsdConfigured(SerialFile& serialFile) {
    spdlog::info("WifiConfigSetuper::waitForMsdConfigured");
    bool res = waitForString(serialFile, MSD_CONFIGURED_MSG);
    if(res) {
        spdlog::info("Found out that MSD is configured");
    } else {
        spdlog::error("Could not find out that MSD is configured");
    }
    return res;
}

void WifiConfigSetuper::sendWifiConfig(SerialFile& serialFile, const std::string& wifiConfig) {
    spdlog::info("WifiConfigSetuper::sendWifiConfig");
    serialFile.writeLine(wifiConfig);
    spdlog::info("WifiConfigSetuper::sendWifiConfig - done");
}

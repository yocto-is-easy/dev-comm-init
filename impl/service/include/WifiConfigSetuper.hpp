#pragma once

#include "IConfigSetuper.hpp"
#include "WifiData.hpp"

class WifiConfigSetuper : public IConfigSetuper {
private:
    const std::string MSD_READY_MSG = "MSD_READY";
    const std::string MSD_CONFIGURED_MSG = "MSD_CONFIGURED";
    const uint64_t WAIT_STR_DELAY_MS = 5;
    const uint64_t WAIT_STR_MAX_DELAY_MS = 1000;

    WifiData wifiData_;

public:
    WifiConfigSetuper();

    void setup(SerialFile& serialFile) override;

private:
    std::string prepareWifiConfig();

    bool waitForString(SerialFile& serialFile, const std::string& str);
    bool waitForMsdReady(SerialFile& serialFile);
    bool waitForMsdConfigured(SerialFile& serialFile);

    void sendWifiConfig(SerialFile& serialFile, const std::string& wifiConfig);

};

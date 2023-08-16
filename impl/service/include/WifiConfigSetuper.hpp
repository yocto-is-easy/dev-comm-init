#pragma once

#include "IConfigSetuper.hpp"
#include "WifiData.hpp"

class WifiConfigSetuper : public IConfigSetuper {
public:
    WifiConfigSetuper();

    void setup(SerialFile& serialFile) override;

private:
    WifiData wifiData_;
};

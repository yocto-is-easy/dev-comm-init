#pragma once

#include <string>
#include <iostream>

class WifiData {
public:
    WifiData() = default;

    std::string ssid();
    std::string password();
};

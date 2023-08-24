#pragma once

#include <string>
#include <iostream>

class WifiData {
public:
    WifiData();

    std::string ssid();
    std::string password();
};

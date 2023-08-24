#include "WifiData.hpp"

#include "wifi-manager/i-wifi-manager.h"

WifiData::WifiData() {
    wifi_manager::wait_startup();
}

std::string WifiData::ssid() {
    return wifi_manager::get_wifi_ssid();
}

std::string WifiData::password() {
    return wifi_manager::get_wifi_password();
}

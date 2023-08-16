#include "WifiConfigSetuper.hpp"

WifiConfigSetuper::WifiConfigSetuper() {
}

void WifiConfigSetuper::setup(SerialFile& serialFile) {
    // TODO: implement this stub
    std::cout << "WifiConfigSetuper::setup "
        << serialFile.getPath()
        << " - "
        << serialFile.getBaudrate()
        << std::endl;
}
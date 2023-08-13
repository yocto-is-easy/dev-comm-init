#include <iostream>
#include "SerialFile.hpp"

int main() {
    std::string path = "/dev/ttyUSB0";
    uint32_t baudrate = 115200;

    SerialFile serialFile;
    serialFile.waitOpen(path, B115200);

    std::cout << "Serial file is open: " << path << std::endl;

    try {
        while(true) {
            std::string line = serialFile.readLine();
            std::cout << line << std::endl;
        }
    } catch(SerialFileException& e) {
        std::cout << "Serial file exception: " << e.what() << std::endl;
    }

    return 0;
}

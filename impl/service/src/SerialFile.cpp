#include "SerialFile.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <iostream>
#include <thread>
#include <chrono>

SerialFile::SerialFile() : fd_(-1) {
}

SerialFile::SerialFile(const std::string& path, uint32_t baudrate) 
    : fd_(-1), path_(path), baudrate_(baudrate) {
}

SerialFile::~SerialFile() {
    if(isOpen()) {
        close();
    }
}

void SerialFile::open() {
    open(path_, baudrate_);
}

void SerialFile::open(const std::string& path, uint32_t baudrate) {
    if(isOpen()) {
        throw SerialFileException("Serial file is already open: " + path_);
    }

    path_ = path;
    baudrate_ = baudrate;

    fd_ = ::open(path_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if(fd_ < 0) {
        throw SerialFileException("Failed to open serial file: " + path_ + " (" + strerror(errno) + ")");
    }

    memset(&tty_, 0, sizeof(tty_));
    if(tcgetattr(fd_, &tty_) != 0) {
        throw SerialFileException("Failed to get serial file attributes: " + path_ + " (" + strerror(errno) + ")");
    }

    cfsetospeed(&tty_, baudrate_);
    cfsetispeed(&tty_, baudrate_);

    tty_.c_cflag &= ~PARENB;
    tty_.c_cflag &= ~CSTOPB;
    tty_.c_cflag &= ~CSIZE;
    tty_.c_cflag |= CS8;
    tty_.c_cflag &= ~CRTSCTS;
    tty_.c_cflag |= CREAD | CLOCAL;

    tty_.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty_.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    tty_.c_oflag &= ~OPOST;

    tty_.c_cc[VMIN] = 0;
    tty_.c_cc[VTIME] = 0;

    if(tcsetattr(fd_, TCSANOW, &tty_) != 0) {
        throw SerialFileException("Failed to set serial file attributes: " + path_ + " (" + strerror(errno) + ")");
    }
}

void SerialFile::waitOpen(const std::string& path, uint32_t baudrate) {
    for(uint64_t i = 0; true; i++) {
        try {
            open(path, baudrate);
            break;
        } catch(SerialFileException& e) {
            std::cout << "No serial file detected(" << i << "): " << e.what() << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void SerialFile::waitOpen() {
    waitOpen(path_, baudrate_);
}

void SerialFile::close() {
    if(!isOpen()) {
        throw SerialFileException("Serial file is not open: " + path_);
    }

    if(::close(fd_) != 0) {
        throw SerialFileException("Failed to close serial file: " + path_ + " (" + strerror(errno) + ")");
    } else {
        fd_ = -1;
    }
}

bool SerialFile::isOpen() const {
    return fd_ >= 0;
}

void SerialFile::write(std::string& data) {
    if(::write(fd_, data.c_str(), data.size()) < 0) {
        throw SerialFileException("Failed to write to serial file: " + path_ + " (" + strerror(errno) + ")");
    }
}

char SerialFile::read() {
    if(!isOpen()) {
        throw SerialFileException("Serial file is not open: " + path_);
    }

    char c;
    int n = ::read(fd_, &c, 1);
    if(n < 0) {
        throw SerialFileException("Failed to read from serial file: " + path_ + " (" + strerror(errno) + ")");
    } else if(n == 0) {
        throw SerialFileException("Failed to read from serial file: " + path_ + " (no data)");
    } else {
        return c;
    }
}

std::string SerialFile::readLine() {
    if(!isOpen()) {
        throw SerialFileException("Serial file is not open: " + path_);
    }

    std::string line;
    while(true) {
        char c = read();
        if(c == '\r') {
            continue;
        } else if(c == '\n') {
            if(line.size() > 0)
                return line;
            else
                continue;
        } else {
            line += c;
        }
    }

    return "";
}

std::string SerialFile::getPath() const {
    return path_;
}

uint32_t SerialFile::getBaudrate() const {
    return baudrate_;
}

SerialFileException::SerialFileException(const std::string& message) : message_(message) {
}

SerialFileException::~SerialFileException() throw() {
}

const char* SerialFileException::what() const throw() {
    return message_.c_str();
}

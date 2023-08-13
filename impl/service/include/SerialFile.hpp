#pragma once

#include <string>
#include <exception>

#include <stdint.h>
#include <termios.h>

class SerialFile {
public:
    SerialFile();
    SerialFile(const std::string& path, uint32_t baudrate);

    ~SerialFile();

    void open(const std::string& path, uint32_t baudrate);
    void close();
    bool isOpen() const;
    void write(std::string& data);
    char read();
    std::string readLine();

    void waitOpen(const std::string& path, uint32_t baudrate);

private:
    int fd_;
    termios tty_;
    std::string path_;
    uint32_t baudrate_;
};

class SerialFileException : public std::exception {
public:
    SerialFileException(const std::string& message);
    virtual ~SerialFileException() throw();

    virtual const char* what() const throw();

private:
    std::string message_;
};

class SerialFileBuilder {
public:
    SerialFileBuilder();
    ~SerialFileBuilder();

    SerialFileBuilder& path(const std::string& path);
    SerialFileBuilder& baudrate(uint32_t baudrate);
    SerialFile build();

private:
    std::string path_;
    uint32_t baudrate_;
};

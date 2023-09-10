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

    void open();
    void open(const std::string& path, uint32_t baudrate);
    void close();
    bool isOpen() const;
    void write(const std::string& data);
    char read();
    std::string readLine();
    void writeLine(const std::string& data);

    void waitOpen(const std::string& path, uint32_t baudrate);
    void waitOpen();

    std::string getPath() const;
    uint32_t getBaudrate() const;

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

#pragma once

#include "SerialFile.hpp"

class IConfigSetuper {
public:
    virtual ~IConfigSetuper() = default;

    virtual void setup(SerialFile&) = 0;
};

#pragma once

// --------------------------------------------------------------------------------

#include "FlpTypes.h"
#include <istream>

// --------------------------------------------------------------------------------

class Flp
{
public:
    explicit Flp(std::istream &read);

    FLhd header;
    FLdt data;

private:
    std::istream &m_read;
};

// --------------------------------------------------------------------------------

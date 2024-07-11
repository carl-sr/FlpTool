#include "Flp.h"
#include <cassert>

// --------------------------------------------------------------------------------

Flp::Flp(std::istream& read)
    : m_read(read)
{
    read.read((char *)&header, sizeof(header));
    read.read((char *)&data, sizeof(data));

    auto a = header.isValid();
    auto b = data.isValid();

    assert(a);
    assert(b);

}

// --------------------------------------------------------------------------------

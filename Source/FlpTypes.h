#pragma once

// --------------------------------------------------------------------------------

#include <cstdint>
#include <istream>

// --------------------------------------------------------------------------------

#pragma pack(push, 1)

struct FLhd
{
    char magic[4];              // 4 chars which are the letters 'FLhd' for 'FruityLoops header'
    std::uint32_t length;       // The length of this chunk, like in MIDI files. Atm it's 6, but could evolve
    std::uint16_t format;       // Set to 0 for full songs
    std::uint16_t nchannels;    // The total number of channels (not really used)
    std::uint16_t beatdiv;      // Pulses per quarter of the song

    bool isValid() const;
};

struct FLdt
{
    char magic[4]; // 4 chars which are the letters 'FLdt' for 'FruityLoops data'
    std::uint32_t length; // The length of (the rest of) this chunk (i.e. WITHOUT these 2 DWORDS)

    bool isValid() const;
};

#pragma pack(pop)

// --------------------------------------------------------------------------------

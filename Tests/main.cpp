#include <gtest/gtest.h>

//--------------------------------------------------------------------------------

#include "FlpTests.h"

//--------------------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    
    constexpr const char* flilePath{ "D:/code/kaitai/flp/FlpTool/Tests/flpbin/a.flp" };
    // a.flp
    //     160 bpm
    //     plugins :
    // -one sytrus{ color: #FDA73F, name: 'Sytrus' }
    //     - one pattern{ color: #864559, name: 'THIS IS THE PATTERN' }
    //     - one mixer track{ color: #595BB5, name: 'MIXER TRACK' }
    //     - Fruity Limiter(default)

    std::ifstream file{ flilePath, std::ios::beg | std::ios::binary };

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    flp::FlpEventReader flp{ file };

    EXPECT_TRUE(flp.hasEvents());

    int eventCount{ 0 };

    using varType = std::variant<std::uint8_t, std::uint16_t, std::uint32_t, std::vector<std::uint8_t>>;


    std::vector<std::pair<flp::FlpEventType, varType>> recordedEvents;

    
    while (flp.hasEvents())
    {
        ++eventCount;

        if (26024 == eventCount)
            printf("break");

        auto e = flp.getNextEvent();
        

        switch (flp::GetEventSize(e.getType()))
        {
        case flp::FlpEventSize::Byte:
            recordedEvents.push_back(std::make_pair(e.getType(), e.getDataByte()));
            break;
        case flp::FlpEventSize::Word:
            recordedEvents.push_back(std::make_pair(e.getType(), e.getDataWord()));
            break;
        case flp::FlpEventSize::Dword:
            recordedEvents.push_back(std::make_pair(e.getType(), e.getDataDword()));
            break;
        case flp::FlpEventSize::Variable:
            recordedEvents.push_back(std::make_pair(e.getType(), e.getDataVariable()));
            break;

        default:
            assert(false);
            break;
        }
        
        continue;

        // if (e.getType() == flp::FlpEventType::PluginParams)
        //     printf("break");

        switch(flp::GetEventSize(e.getType()))
        {
        case flp::FlpEventSize::Byte:
            printf("0x%02x (BYTE): 0x%02x\n", e.getType(), e.getDataByte());
            break;
        case flp::FlpEventSize::Word:
            printf("0x%02x (WORD): 0x%04x\n", e.getType(), e.getDataWord());
            break;
        case flp::FlpEventSize::Dword:
            printf("0x%02x (DWORD): 0x%08x\n", e.getType(), e.getDataDword());
            break;
        case flp::FlpEventSize::Variable:
        {
            printf("0x%02x (VAR): ", e.getType());
            for (auto u : e.getDataVariable())
                printf("0x%02x ", u);
            printf("\n");
            break;
        }
        
        default:
            assert(false);
            break;
        }
    }

    EXPECT_TRUE(file.eof());

    EXPECT_EQ(eventCount, 26023); // says kaitai
    
    return RUN_ALL_TESTS();
}

//--------------------------------------------------------------------------------

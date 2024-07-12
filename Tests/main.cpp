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

    std::ifstream file{ flilePath };
    flp::FlpEventReader flp{ file };

    EXPECT_TRUE(flp.hasEvents());

    while (flp.hasEvents())
    {
        auto e = flp.getNextEvent();

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
    
    return RUN_ALL_TESTS();
}

//--------------------------------------------------------------------------------

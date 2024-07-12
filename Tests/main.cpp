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
       
    
    return RUN_ALL_TESTS();


}

//--------------------------------------------------------------------------------

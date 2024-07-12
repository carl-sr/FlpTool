#include <gtest/gtest.h>

//--------------------------------------------------------------------------------

#include "Flp/FlpEventReader.h"
#include <fstream>

//--------------------------------------------------------------------------------

TEST(FlpEventReader, GetEventSizeTest)
{
    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::ChanEnabled), flp::FlpEventSize::Byte);
    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::EEAutoMode), flp::FlpEventSize::Byte);

    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::NewChan), flp::FlpEventSize::Word);
    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::SwingMix), flp::FlpEventSize::Word);

    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::PluginColor), flp::FlpEventSize::Dword);
    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::FineTempo), flp::FlpEventSize::Dword);

    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::Text_ChanName), flp::FlpEventSize::Variable);
    EXPECT_EQ(flp::GetEventSize(flp::FlpEventType::Text_PLTrackName), flp::FlpEventSize::Variable);

}

//--------------------------------------------------------------------------------

TEST(FlpEventReader, ReadMetaData)
{
    constexpr const char *flilePath{ "D:/code/kaitai/flp/FlpTool/Tests/flpbin/a.flp" };
    // a.flp
    //     160 bpm
    //     plugins :
    // -one sytrus{ color: #FDA73F, name: 'Sytrus' }
    //     - one pattern{ color: #864559, name: 'THIS IS THE PATTERN' }
    //     - one mixer track{ color: #595BB5, name: 'MIXER TRACK' }
    //     - Fruity Limiter(default)

    std::ifstream file{ flilePath };
    flp::FlpEventReader flp{ file };

    EXPECT_TRUE(flp.header.isValid());
    EXPECT_TRUE(flp.data.isValid());

    // TODO more tests here

}

//--------------------------------------------------------------------------------


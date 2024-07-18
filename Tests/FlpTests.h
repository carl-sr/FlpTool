#pragma once

//--------------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "Flp/EventReader.h"
#include "Flp/EventHandler.h"
#include <fstream>
#include <ranges>
#include <sstream>
#include <array>

//--------------------------------------------------------------------------------

inline std::ifstream GetFileStream()
{
    // a.flp
    //     version: 24.1.1.4234
    //     160 bpm
    //     plugins :
    // -one sytrus{ color: #FDA73F, name: 'Sytrus' }
    //     - one pattern{ color: #864559, name: 'THIS IS THE PATTERN' }
    //     - one mixer track{ color: #595BB5, name: 'MIXER TRACK' }
    //     - Fruity Limiter(default)

    std::ifstream file{ "D:/code/kaitai/flp/FlpTool/Tests/flpbin/a.flp", std::ios::beg | std::ios::binary };
    return file;
}

//--------------------------------------------------------------------------------

TEST(FlpEventReader, GetEventSizeTest)
{
    for (const auto e : {
        flp::EventType::ChanEnabled,
        flp::EventType::NoteOn,
        flp::EventType::ChanVol,
        flp::EventType::ChanPan,
        flp::EventType::MIDIChan,
        flp::EventType::MIDINote,
        flp::EventType::MIDIPatch,
        flp::EventType::MIDIBank,
        flp::EventType::LoopActive,
        flp::EventType::ShowInfo,
        flp::EventType::Shuffle,
        flp::EventType::MainVol,
        flp::EventType::FitToSteps,
        flp::EventType::Pitchable,
        flp::EventType::Zipped,
        flp::EventType::Delay_Flags,
        flp::EventType::TimeSig_Num,
        flp::EventType::TimeSig_Beat,
        flp::EventType::UseLoopPoints,
        flp::EventType::LoopType,
        flp::EventType::ChanType,
        flp::EventType::TargetFXTrack,
        flp::EventType::PanVolTab,
        flp::EventType::nStepsShown,
        flp::EventType::SSLength,
        flp::EventType::SSLoop,
        flp::EventType::FXProps,
        flp::EventType::Registered,
        flp::EventType::APDC,
        flp::EventType::TruncateClipNotes,
        flp::EventType::EEAutoMode,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::EventSize::Byte);
    }

    for (const auto e : {
        flp::EventType::NewChan,
        flp::EventType::NewPat,
        flp::EventType::Tempo,
        flp::EventType::CurrentPatNum,
        flp::EventType::PatData,
        flp::EventType::FX,
        flp::EventType::FXFlags,
        flp::EventType::FXCut,
        flp::EventType::DotVol,
        flp::EventType::DotPan,
        flp::EventType::FXPreamp,
        flp::EventType::FXDecay,
        flp::EventType::FXAttack,
        flp::EventType::DotNote,
        flp::EventType::DotPitch,
        flp::EventType::DotMix,
        flp::EventType::MainPitch,
        flp::EventType::RandChan,
        flp::EventType::MixChan,
        flp::EventType::FXRes,
        flp::EventType::OldSongLoopPos,
        flp::EventType::FXStDel,
        flp::EventType::FX3,
        flp::EventType::DotFRes,
        flp::EventType::DotFCut,
        flp::EventType::ShiftTime,
        flp::EventType::LoopEndBar,
        flp::EventType::Dot,
        flp::EventType::DotShift,
        flp::EventType::Tempo_Fine,
        flp::EventType::LayerChan,
        flp::EventType::FXIcon,
        flp::EventType::DotRel,
        flp::EventType::SwingMix,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::EventSize::Word);
    }

    for (const auto e : {
        flp::EventType::PluginColor,
        flp::EventType::PLItem,
        flp::EventType::Echo,
        flp::EventType::FXSine,
        flp::EventType::CutCutBy,
        flp::EventType::WindowH,
        flp::EventType::MiddleNote,
        flp::EventType::Reserved,
        flp::EventType::MainResCut,
        flp::EventType::DelayFRes,
        flp::EventType::Reverb,
        flp::EventType::StretchTime,
        flp::EventType::SSNote,
        flp::EventType::FineTune,
        flp::EventType::SampleFlags,
        flp::EventType::LayerFlags,
        flp::EventType::ChanFilterNum,
        flp::EventType::CurrentFilterNum,
        flp::EventType::FXOutChanNum,
        flp::EventType::NewTimeMarker,
        flp::EventType::FXColor,
        flp::EventType::PatColor,
        flp::EventType::PatAutoMode,
        flp::EventType::SongLoopPos,
        flp::EventType::AUSmpRate,
        flp::EventType::FXInChanNum,
        flp::EventType::PluginIcon,
        flp::EventType::FineTempo,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::EventSize::Dword);
    }

    for (const auto e : {
        flp::EventType::Text_ChanName,
        flp::EventType::Text_PatName,
        flp::EventType::Text_Title,
        flp::EventType::Text_Comment,
        flp::EventType::Text_SampleFileName,
        flp::EventType::Text_URL,
        flp::EventType::Text_CommentRTF,
        flp::EventType::Version,
        flp::EventType::RegName,
        flp::EventType::Text_DefPluginName,
        flp::EventType::Text_ProjDataPath,
        flp::EventType::Text_PluginName,
        flp::EventType::Text_FXName,
        flp::EventType::Text_TimeMarker,
        flp::EventType::Text_Genre,
        flp::EventType::Text_Author,
        flp::EventType::MIDICtrls,
        flp::EventType::Delay,
        flp::EventType::TS404Params,
        flp::EventType::DelayLine,
        flp::EventType::NewPlugin,
        flp::EventType::PluginParams,
        flp::EventType::Reserved2,
        flp::EventType::ChanParams,
        flp::EventType::CtrlRecChan,
        flp::EventType::PLSel,
        flp::EventType::Envelope,
        flp::EventType::ChanLevels,
        flp::EventType::ChanFilter,
        flp::EventType::ChanPoly,
        flp::EventType::NoteRecChan,
        flp::EventType::PatCtrlRecChan,
        flp::EventType::PatNoteRecChan,
        flp::EventType::InitCtrlRecChan,
        flp::EventType::RemoteCtrl_MIDI,
        flp::EventType::RemoteCtrl_Int,
        flp::EventType::Tracking,
        flp::EventType::ChanOfsLevels,
        flp::EventType::Text_RemoteCtrlFormula,
        flp::EventType::Text_ChanFilter,
        flp::EventType::RegBlackList,
        flp::EventType::PLRecChan,
        flp::EventType::ChanAC,
        flp::EventType::FXRouting,
        flp::EventType::FXParams,
        flp::EventType::ProjectTime,
        flp::EventType::PLTrackInfo,
        flp::EventType::Text_PLTrackName,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::EventSize::Variable);
    }
}

//--------------------------------------------------------------------------------

TEST(FlpEventReader, ReadMetaData)
{
    auto file{ GetFileStream() };
    flp::EventReader flp{ file };

    EXPECT_TRUE(flp.header.isValid());
    EXPECT_TRUE(flp.data.isValid());

    // TODO more tests here

}

//--------------------------------------------------------------------------------

TEST(FlpEventReader, ReadEvents)
{
    auto file{ GetFileStream() };
    flp::EventReader flp{ file };

    EXPECT_TRUE(flp.hasEvents());
}

//--------------------------------------------------------------------------------

TEST(FlpEventReader, VariableLengthBit)
{
    struct Case
    {
        std::vector<std::uint8_t> bytes;
        std::size_t expect;
    };

    constexpr std::uint8_t Mask{ 0b1 << 7 }; // highest beat means the number continues

    const std::vector<Case> testCases{
        { { 0x00, 0x02 }, 0 },
        { { 0x01, 0x02 }, 1 },
        { { 0x01 | Mask, 0x00 }, 1 },
        { { 0x01 | Mask, 0x01 | Mask, 0x01 }, 3 },
        { { 0x02 | Mask, 0x02 | Mask, 0x02 }, 6 },
    };

    for (const auto& testCase: testCases)
    {

        std::stringstream ss;

        for (const auto i : testCase.bytes)
            ss << i;

        std::size_t result{ flp::ReadVarDataLength(ss)};
        EXPECT_EQ(result, testCase.expect);
    }
}

//--------------------------------------------------------------------------------

TEST(FlpEventReader, GoodEventData)
{
    auto file{ GetFileStream() };

    flp::EventReader flp{ file };

    EXPECT_TRUE(flp.hasEvents());

    int eventCount{ 0 };

    while (flp.hasEvents())
    {
        ++eventCount;
        auto e = flp.getNextEvent();
    }

    EXPECT_TRUE(file.eof());

    EXPECT_EQ(eventCount, 26023); // says kaitai
}

//--------------------------------------------------------------------------------

TEST(FlpEventHander, Byte)
{
    auto file{ GetFileStream() };
    flp::EventReader flp{ file };

    flp::EventHandler handler;

    const std::uint8_t expect{ 0x1 };
    std::uint8_t got{ 0 };

    handler.addHandler<flp::EventType::Registered>([&got](auto e)
    {
        got = e.data;
    });
    handler.dispatch(flp);

    EXPECT_EQ(expect, got);
}

//--------------------------------------------------------------------------------

TEST(FlpEventHander, Word)
{
    auto file{ GetFileStream() };
    flp::EventReader flp{ file };

    flp::EventHandler handler;

    constexpr std::uint16_t expect{ 0 };
    std::uint16_t got{ 1 };

    handler.addHandler<flp::EventType::MainPitch>([&got](auto e)
    {
        got = e.data;
    });

    handler.dispatch(flp);

    EXPECT_EQ(expect, got);
}

//--------------------------------------------------------------------------------

TEST(FlpEventHander, Dword)
{
    auto file{ GetFileStream() };
    flp::EventReader flp{ file };

    flp::EventHandler handler;

    constexpr std::uint32_t expectColor{ 0xB55B59 };
    std::uint32_t color;

    handler.addHandler<flp::EventType::FXColor>([&color](auto e)
    {
        color = e.data;
    });
    handler.dispatch(flp);

    EXPECT_EQ(color, expectColor);
}

//--------------------------------------------------------------------------------

TEST(FlpEventHander, Variable)
{
    auto file{ GetFileStream() };
    flp::EventReader flp{ file };

    flp::EventHandler handler;

    const std::string expectVersion{ "24.1.1.4234" };
    std::string gotVersion;

    handler.addHandler<flp::EventType::Version>([&gotVersion](auto e)
    {
        for(auto c : e.data)
        {
            if (c)
                gotVersion += c;
        }
    });

    handler.dispatch(flp);

    EXPECT_FALSE(gotVersion.empty());
    EXPECT_EQ(expectVersion, gotVersion);
}

//--------------------------------------------------------------------------------

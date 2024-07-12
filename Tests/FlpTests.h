#include <gtest/gtest.h>

//--------------------------------------------------------------------------------

#include "Flp/FlpEventReader.h"
#include <fstream>
#include <ranges>
#include <sstream>

//--------------------------------------------------------------------------------

TEST(FlpEventReader, GetEventSizeTest)
{
    for (auto e : {
        flp::FlpEventType::ChanEnabled,
        flp::FlpEventType::NoteOn,
        flp::FlpEventType::ChanVol,
        flp::FlpEventType::ChanPan,
        flp::FlpEventType::MIDIChan,
        flp::FlpEventType::MIDINote,
        flp::FlpEventType::MIDIPatch,
        flp::FlpEventType::MIDIBank,
        flp::FlpEventType::LoopActive,
        flp::FlpEventType::ShowInfo,
        flp::FlpEventType::Shuffle,
        flp::FlpEventType::MainVol,
        flp::FlpEventType::FitToSteps,
        flp::FlpEventType::Pitchable,
        flp::FlpEventType::Zipped,
        flp::FlpEventType::Delay_Flags,
        flp::FlpEventType::TimeSig_Num,
        flp::FlpEventType::TimeSig_Beat,
        flp::FlpEventType::UseLoopPoints,
        flp::FlpEventType::LoopType,
        flp::FlpEventType::ChanType,
        flp::FlpEventType::TargetFXTrack,
        flp::FlpEventType::PanVolTab,
        flp::FlpEventType::nStepsShown,
        flp::FlpEventType::SSLength,
        flp::FlpEventType::SSLoop,
        flp::FlpEventType::FXProps,
        flp::FlpEventType::Registered,
        flp::FlpEventType::APDC,
        flp::FlpEventType::TruncateClipNotes,
        flp::FlpEventType::EEAutoMode,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::FlpEventSize::Byte);
    }
    
    for (auto e : {
        flp::FlpEventType::NewChan,
        flp::FlpEventType::NewPat,
        flp::FlpEventType::Tempo,
        flp::FlpEventType::CurrentPatNum,
        flp::FlpEventType::PatData,
        flp::FlpEventType::FX,
        flp::FlpEventType::FXFlags,
        flp::FlpEventType::FXCut,
        flp::FlpEventType::DotVol,
        flp::FlpEventType::DotPan,
        flp::FlpEventType::FXPreamp,
        flp::FlpEventType::FXDecay,
        flp::FlpEventType::FXAttack,
        flp::FlpEventType::DotNote,
        flp::FlpEventType::DotPitch,
        flp::FlpEventType::DotMix,
        flp::FlpEventType::MainPitch,
        flp::FlpEventType::RandChan,
        flp::FlpEventType::MixChan,
        flp::FlpEventType::FXRes,
        flp::FlpEventType::OldSongLoopPos,
        flp::FlpEventType::FXStDel,
        flp::FlpEventType::FX3,
        flp::FlpEventType::DotFRes,
        flp::FlpEventType::DotFCut,
        flp::FlpEventType::ShiftTime,
        flp::FlpEventType::LoopEndBar,
        flp::FlpEventType::Dot,
        flp::FlpEventType::DotShift,
        flp::FlpEventType::Tempo_Fine,
        flp::FlpEventType::LayerChan,
        flp::FlpEventType::FXIcon,
        flp::FlpEventType::DotRel,
        flp::FlpEventType::SwingMix,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::FlpEventSize::Word);
    }

    for (auto e : {
        flp::FlpEventType::PluginColor,
        flp::FlpEventType::PLItem,
        flp::FlpEventType::Echo,
        flp::FlpEventType::FXSine,
        flp::FlpEventType::CutCutBy,
        flp::FlpEventType::WindowH,
        flp::FlpEventType::MiddleNote,
        flp::FlpEventType::Reserved,
        flp::FlpEventType::MainResCut,
        flp::FlpEventType::DelayFRes,
        flp::FlpEventType::Reverb,
        flp::FlpEventType::StretchTime,
        flp::FlpEventType::SSNote,
        flp::FlpEventType::FineTune,
        flp::FlpEventType::SampleFlags,
        flp::FlpEventType::LayerFlags,
        flp::FlpEventType::ChanFilterNum,
        flp::FlpEventType::CurrentFilterNum,
        flp::FlpEventType::FXOutChanNum,
        flp::FlpEventType::NewTimeMarker,
        flp::FlpEventType::FXColor,
        flp::FlpEventType::PatColor,
        flp::FlpEventType::PatAutoMode,
        flp::FlpEventType::SongLoopPos,
        flp::FlpEventType::AUSmpRate,
        flp::FlpEventType::FXInChanNum,
        flp::FlpEventType::PluginIcon,
        flp::FlpEventType::FineTempo,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::FlpEventSize::Dword);
    }

    for (auto e : {
        flp::FlpEventType::Text_ChanName,
        flp::FlpEventType::Text_PatName,
        flp::FlpEventType::Text_Title,
        flp::FlpEventType::Text_Comment,
        flp::FlpEventType::Text_SampleFileName,
        flp::FlpEventType::Text_URL,
        flp::FlpEventType::Text_CommentRTF,
        flp::FlpEventType::Version,
        flp::FlpEventType::RegName,
        flp::FlpEventType::Text_DefPluginName,
        flp::FlpEventType::Text_ProjDataPath,
        flp::FlpEventType::Text_PluginName,
        flp::FlpEventType::Text_FXName,
        flp::FlpEventType::Text_TimeMarker,
        flp::FlpEventType::Text_Genre,
        flp::FlpEventType::Text_Author,
        flp::FlpEventType::MIDICtrls,
        flp::FlpEventType::Delay,
        flp::FlpEventType::TS404Params,
        flp::FlpEventType::DelayLine,
        flp::FlpEventType::NewPlugin,
        flp::FlpEventType::PluginParams,
        flp::FlpEventType::Reserved2,
        flp::FlpEventType::ChanParams,
        flp::FlpEventType::CtrlRecChan,
        flp::FlpEventType::PLSel,
        flp::FlpEventType::Envelope,
        flp::FlpEventType::ChanLevels,
        flp::FlpEventType::ChanFilter,
        flp::FlpEventType::ChanPoly,
        flp::FlpEventType::NoteRecChan,
        flp::FlpEventType::PatCtrlRecChan,
        flp::FlpEventType::PatNoteRecChan,
        flp::FlpEventType::InitCtrlRecChan,
        flp::FlpEventType::RemoteCtrl_MIDI,
        flp::FlpEventType::RemoteCtrl_Int,
        flp::FlpEventType::Tracking,
        flp::FlpEventType::ChanOfsLevels,
        flp::FlpEventType::Text_RemoteCtrlFormula,
        flp::FlpEventType::Text_ChanFilter,
        flp::FlpEventType::RegBlackList,
        flp::FlpEventType::PLRecChan,
        flp::FlpEventType::ChanAC,
        flp::FlpEventType::FXRouting,
        flp::FlpEventType::FXParams,
        flp::FlpEventType::ProjectTime,
        flp::FlpEventType::PLTrackInfo,
        flp::FlpEventType::Text_PLTrackName,
        })
    {
        EXPECT_EQ(flp::GetEventSize(e), flp::FlpEventSize::Variable);
    }
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

TEST(FlpEventReader, ReadEvents)
{
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
}

//--------------------------------------------------------------------------------


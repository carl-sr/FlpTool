#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include <cstdint>
#include <istream>
#include <span>

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

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

#pragma pack(pop)

// --------------------------------------------------------------------------------

#pragma pack(push, 1)

struct FLdt
{
    char magic[4]; // 4 chars which are the letters 'FLdt' for 'FruityLoops data'
    std::uint32_t length; // The length of (the rest of) this chunk (i.e. WITHOUT these 2 DWORDS)

    bool isValid() const;
};

#pragma pack(pop)

// --------------------------------------------------------------------------------

struct EventDataSize
{
    static constexpr std::uint8_t Byte     = 0b00 << 6;
    static constexpr std::uint8_t Word     = 0b01 << 6;
    static constexpr std::uint8_t Dword    = 0b10 << 6;
    static constexpr std::uint8_t Variable = 0b11 << 6;
};

// --------------------------------------------------------------------------------

enum class EventSize : std::uint8_t
{
    Byte        = EventDataSize::Byte,
    Word        = EventDataSize::Word,
    Dword       = EventDataSize::Dword,
    Variable    = EventDataSize::Variable
};

// --------------------------------------------------------------------------------

enum class EventType : std::uint8_t
{
    // BYTE sized (0..63)
    ChanEnabled         	= EventDataSize::Byte,
    NoteOn              	= EventDataSize::Byte + 1, // +pos
    ChanVol             	= EventDataSize::Byte + 2, // obsolete
    ChanPan             	= EventDataSize::Byte + 3, // obsolete
    MIDIChan            	= EventDataSize::Byte + 4,
    MIDINote            	= EventDataSize::Byte + 5,
    MIDIPatch           	= EventDataSize::Byte + 6,
    MIDIBank            	= EventDataSize::Byte + 7,
    LoopActive          	= EventDataSize::Byte + 9,
    ShowInfo            	= EventDataSize::Byte + 10,
    Shuffle             	= EventDataSize::Byte + 11,
    MainVol             	= EventDataSize::Byte + 12, // obsolete
    FitToSteps          	= EventDataSize::Byte + 13, // obsolete byte version
    Pitchable           	= EventDataSize::Byte + 14, // obsolete
    Zipped              	= EventDataSize::Byte + 15,
    Delay_Flags         	= EventDataSize::Byte + 16, // obsolete
    TimeSig_Num         	= EventDataSize::Byte + 17,
    TimeSig_Beat        	= EventDataSize::Byte + 18,
    UseLoopPoints       	= EventDataSize::Byte + 19,
    LoopType            	= EventDataSize::Byte + 20,
    ChanType            	= EventDataSize::Byte + 21,
    TargetFXTrack       	= EventDataSize::Byte + 22,
    PanVolTab           	= EventDataSize::Byte + 23, // log vol & circular pan tables
    nStepsShown         	= EventDataSize::Byte + 24, // obsolete
    SSLength            	= EventDataSize::Byte + 25, // +length
    SSLoop              	= EventDataSize::Byte + 26,
    FXProps             	= EventDataSize::Byte + 27, // FlipY, ReverseStereo, etc
    Registered          	= EventDataSize::Byte + 28, // reg version
    APDC                	= EventDataSize::Byte + 29,
    TruncateClipNotes   	= EventDataSize::Byte + 30,
    EEAutoMode          	= EventDataSize::Byte + 31,

    // WORD sized (63..127)
    NewChan             	= EventDataSize::Word ,
    NewPat              	= EventDataSize::Word + 1, // +PatNum (word)
    Tempo               	= EventDataSize::Word + 2, // obsolete, replaced by FLP_FineTempo
    CurrentPatNum       	= EventDataSize::Word + 3,
    PatData             	= EventDataSize::Word + 4,
    FX                  	= EventDataSize::Word + 5,
    FXFlags             	= EventDataSize::Word + 6,
    FXCut               	= EventDataSize::Word + 7,
    DotVol              	= EventDataSize::Word + 8,
    DotPan              	= EventDataSize::Word + 9,
    FXPreamp            	= EventDataSize::Word + 10,
    FXDecay             	= EventDataSize::Word + 11,
    FXAttack            	= EventDataSize::Word + 12,
    DotNote             	= EventDataSize::Word + 13,
    DotPitch            	= EventDataSize::Word + 14,
    DotMix              	= EventDataSize::Word + 15,
    MainPitch           	= EventDataSize::Word + 16,
    RandChan            	= EventDataSize::Word + 17, // obsolete
    MixChan             	= EventDataSize::Word + 18, // obsolete
    FXRes               	= EventDataSize::Word + 19,
    OldSongLoopPos      	= EventDataSize::Word + 20, // obsolete
    FXStDel             	= EventDataSize::Word + 21,
    FX3                 	= EventDataSize::Word + 22,
    DotFRes             	= EventDataSize::Word + 23,
    DotFCut             	= EventDataSize::Word + 24,
    ShiftTime           	= EventDataSize::Word + 25,
    LoopEndBar          	= EventDataSize::Word + 26,
    Dot                 	= EventDataSize::Word + 27,
    DotShift            	= EventDataSize::Word + 28,
    Tempo_Fine          	= EventDataSize::Word + 29, // obsolete, replaced by FLP_FineTempo
    LayerChan           	= EventDataSize::Word + 30,
    FXIcon              	= EventDataSize::Word + 31,
    DotRel              	= EventDataSize::Word + 32,
    SwingMix            	= EventDataSize::Word + 33,

    // DWORD sized (128..191)
    PluginColor         	= EventDataSize::Dword,
    PLItem              	= EventDataSize::Dword + 1, // Pos (word) +PatNum (word) (obsolete)
    Echo                	= EventDataSize::Dword + 2,
    FXSine              	= EventDataSize::Dword + 3,
    CutCutBy            	= EventDataSize::Dword + 4,
    WindowH             	= EventDataSize::Dword + 5,
    MiddleNote          	= EventDataSize::Dword + 7,
    Reserved            	= EventDataSize::Dword + 8, // may contain an invalid version info
    MainResCut          	= EventDataSize::Dword + 9, // obsolete
    DelayFRes           	= EventDataSize::Dword + 10,
    Reverb              	= EventDataSize::Dword + 11,
    StretchTime         	= EventDataSize::Dword + 12,
    SSNote              	= EventDataSize::Dword + 13, // SimSynth patch middle note (obsolete)
    FineTune            	= EventDataSize::Dword + 14,
    SampleFlags         	= EventDataSize::Dword + 15,
    LayerFlags          	= EventDataSize::Dword + 16,
    ChanFilterNum       	= EventDataSize::Dword + 17,
    CurrentFilterNum    	= EventDataSize::Dword + 18,
    FXOutChanNum        	= EventDataSize::Dword + 19, // FX track output channel
    NewTimeMarker       	= EventDataSize::Dword + 20, // + Time & Mode in higher bits
    FXColor             	= EventDataSize::Dword + 21,
    PatColor            	= EventDataSize::Dword + 22,
    PatAutoMode         	= EventDataSize::Dword + 23, // obsolete
    SongLoopPos         	= EventDataSize::Dword + 24,
    AUSmpRate           	= EventDataSize::Dword + 25,
    FXInChanNum         	= EventDataSize::Dword + 26, // FX track input channel
    PluginIcon          	= EventDataSize::Dword + 27,
    FineTempo           	= EventDataSize::Dword + 28,

    // Variable size (192..255) - Text is null terminated AnsiString
    Text_ChanName       	= EventDataSize::Variable ,  // obsolete
    Text_PatName        	= EventDataSize::Variable + 1,
    Text_Title          	= EventDataSize::Variable + 2,
    Text_Comment        	= EventDataSize::Variable + 3,
    Text_SampleFileName 	= EventDataSize::Variable + 4,
    Text_URL            	= EventDataSize::Variable + 5,
    Text_CommentRTF     	= EventDataSize::Variable + 6, // comments in Rich Text format
    Version             	= EventDataSize::Variable + 7,
    RegName             	= EventDataSize::Variable + 8, // since 1.3.9 the (scrambled) reg name is stored in the FLP
    Text_DefPluginName  	= EventDataSize::Variable + 9,
    //FLP_Text_CommentRTF_SC 	=FLP_Text+10, // new comments in Rich Text format (obsolete)
    Text_ProjDataPath   	= EventDataSize::Variable + 10,
    Text_PluginName     	= EventDataSize::Variable + 11, // plugin's name
    Text_FXName         	= EventDataSize::Variable + 12, // FX track name
    Text_TimeMarker     	= EventDataSize::Variable + 13, // time marker name
    Text_Genre          	= EventDataSize::Variable + 14,
    Text_Author         	= EventDataSize::Variable + 15,
    MIDICtrls           	= EventDataSize::Variable + 16,
    Delay               	= EventDataSize::Variable + 17,
    TS404Params         	= EventDataSize::Variable + 18,
    DelayLine           	= EventDataSize::Variable + 19, // obsolete
    NewPlugin           	= EventDataSize::Variable + 20, // new VST or DirectX plugin
    PluginParams        	= EventDataSize::Variable + 21,
    Reserved2           	= EventDataSize::Variable + 22, // used once for testing
    ChanParams          	= EventDataSize::Variable + 23, // block of various channel params (can grow)
    CtrlRecChan         	= EventDataSize::Variable + 24, // automated controller events
    PLSel               	= EventDataSize::Variable + 25, // selection in playlist
    Envelope            	= EventDataSize::Variable + 26,
    ChanLevels          	= EventDataSize::Variable + 27, // pan, vol, pitch, filter, filter type
    ChanFilter          	= EventDataSize::Variable + 28, // cut, res, type (obsolete)
    ChanPoly            	= EventDataSize::Variable + 29, // max poly, poly slide, monophonic
    NoteRecChan         	= EventDataSize::Variable + 30, // automated note events
    PatCtrlRecChan      	= EventDataSize::Variable + 31, // automated ctrl events per pattern
    PatNoteRecChan      	= EventDataSize::Variable + 32, // automated note events per pattern
    InitCtrlRecChan     	= EventDataSize::Variable + 33, // init values for automated events
    RemoteCtrl_MIDI     	= EventDataSize::Variable + 34, // remote control entry (MIDI)
    RemoteCtrl_Int      	= EventDataSize::Variable + 35, // remote control entry (internal)
    Tracking            	= EventDataSize::Variable + 36, // vol/kb tracking
    ChanOfsLevels       	= EventDataSize::Variable + 37, // levels offset
    Text_RemoteCtrlFormula 	= EventDataSize::Variable + 38, // remote control entry formula
    Text_ChanFilter     	= EventDataSize::Variable + 39,
    RegBlackList        	= EventDataSize::Variable + 40, // black list of reg codes
    PLRecChan           	= EventDataSize::Variable + 41, // playlist
    ChanAC              	= EventDataSize::Variable + 42, // channel articulator
    FXRouting           	= EventDataSize::Variable + 43,
    FXParams            	= EventDataSize::Variable + 44,
    ProjectTime         	= EventDataSize::Variable + 45,
    PLTrackInfo         	= EventDataSize::Variable + 46,
    Text_PLTrackName    	= EventDataSize::Variable + 47,

};

// --------------------------------------------------------------------------------

bool TypeMatchesSize(EventType type, EventSize size);

// --------------------------------------------------------------------------------

constexpr EventSize GetEventSize(EventType type)
{
    auto u8Type{ static_cast<std::uint8_t>(type) };
    u8Type &= 0b11 << 6;

    return static_cast<EventSize>(u8Type);
}

// --------------------------------------------------------------------------------

std::size_t ReadVarDataLength(std::istream& read);

// --------------------------------------------------------------------------------
// EventTypeDataSize
// given an EventType get its EventSize
// --------------------------------------------------------------------------------

template<EventType Type>
struct EventTypeDataSize
{
    constexpr static EventSize size = GetEventSize(Type);
};

static_assert(EventTypeDataSize<EventType::ChanEnabled>::size == EventSize::Byte);
static_assert(EventTypeDataSize<EventType::NewChan>::size == EventSize::Word);
static_assert(EventTypeDataSize<EventType::PluginColor>::size == EventSize::Dword);
static_assert(EventTypeDataSize<EventType::Text_ChanName>::size == EventSize::Variable);

// --------------------------------------------------------------------------------
// EventSizeDataType
// find the data type associated with a DataSize
// --------------------------------------------------------------------------------

template<EventSize>
struct EventSizeDataType
{
};

template<>
struct EventSizeDataType<EventSize::Byte>
{
    using DataType = const std::uint8_t;
};

template<>
struct EventSizeDataType<EventSize::Word>
{
    using DataType = const std::uint16_t;
};

template<>
struct EventSizeDataType<EventSize::Dword>
{
    using DataType = const std::uint32_t;
};

template<>
struct EventSizeDataType<EventSize::Variable>
{
    using DataType = std::span<const std::uint8_t>;
};


// --------------------------------------------------------------------------------
// EventHandlerDataType
// find the data type associated with an EventType
// --------------------------------------------------------------------------------

template<EventType Type, EventSize Size = EventTypeDataSize<Type>::size>
struct EventDataType
{
    using DataType = typename EventSizeDataType<Size>::DataType;
};

// --------------------------------------------------------------------------------

static_assert(std::is_same_v<EventDataType<EventType::ChanEnabled>::DataType, const std::uint8_t>);
static_assert(std::is_same_v<EventDataType<EventType::NewChan>::DataType, const std::uint16_t>);
static_assert(std::is_same_v<EventDataType<EventType::PluginColor>::DataType, const std::uint32_t>);
static_assert(std::is_same_v<EventDataType<EventType::Text_ChanName>::DataType, std::span<const std::uint8_t>>);

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------

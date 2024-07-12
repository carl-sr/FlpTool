#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include <cstdint>
#include <istream>

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

struct FlpEventDataSize
{
    static constexpr std::uint8_t Byte     = 0b00 << 6;
    static constexpr std::uint8_t Word     = 0b01 << 6;
    static constexpr std::uint8_t Dword    = 0b10 << 6;
    static constexpr std::uint8_t Variable = 0b11 << 6;
};

// --------------------------------------------------------------------------------

enum class FlpEventSize : std::uint8_t
{
    Byte        = FlpEventDataSize::Byte,
    Word        = FlpEventDataSize::Word,
    Dword       = FlpEventDataSize::Dword,
    Variable    = FlpEventDataSize::Variable
};

// --------------------------------------------------------------------------------

enum class FlpEventType : std::uint8_t
{
    // BYTE sized (0..63)
    ChanEnabled         	= FlpEventDataSize::Byte,
    NoteOn              	= FlpEventDataSize::Byte + 1, // +pos
    ChanVol             	= FlpEventDataSize::Byte + 2, // obsolete
    ChanPan             	= FlpEventDataSize::Byte + 3, // obsolete
    MIDIChan            	= FlpEventDataSize::Byte + 4,
    MIDINote            	= FlpEventDataSize::Byte + 5,
    MIDIPatch           	= FlpEventDataSize::Byte + 6,
    MIDIBank            	= FlpEventDataSize::Byte + 7,
    LoopActive          	= FlpEventDataSize::Byte + 9,
    ShowInfo            	= FlpEventDataSize::Byte + 10,
    Shuffle             	= FlpEventDataSize::Byte + 11,
    MainVol             	= FlpEventDataSize::Byte + 12, // obsolete
    FitToSteps          	= FlpEventDataSize::Byte + 13, // obsolete byte version
    Pitchable           	= FlpEventDataSize::Byte + 14, // obsolete
    Zipped              	= FlpEventDataSize::Byte + 15,
    Delay_Flags         	= FlpEventDataSize::Byte + 16, // obsolete
    TimeSig_Num         	= FlpEventDataSize::Byte + 17,
    TimeSig_Beat        	= FlpEventDataSize::Byte + 18,
    UseLoopPoints       	= FlpEventDataSize::Byte + 19,
    LoopType            	= FlpEventDataSize::Byte + 20,
    ChanType            	= FlpEventDataSize::Byte + 21,
    TargetFXTrack       	= FlpEventDataSize::Byte + 22,
    PanVolTab           	= FlpEventDataSize::Byte + 23, // log vol & circular pan tables
    nStepsShown         	= FlpEventDataSize::Byte + 24, // obsolete
    SSLength            	= FlpEventDataSize::Byte + 25, // +length
    SSLoop              	= FlpEventDataSize::Byte + 26,
    FXProps             	= FlpEventDataSize::Byte + 27, // FlipY, ReverseStereo, etc
    Registered          	= FlpEventDataSize::Byte + 28, // reg version
    APDC                	= FlpEventDataSize::Byte + 29,
    TruncateClipNotes   	= FlpEventDataSize::Byte + 30,
    EEAutoMode          	= FlpEventDataSize::Byte + 31,

    // WORD sized (63..127)
    NewChan             	= FlpEventDataSize::Word ,
    NewPat              	= FlpEventDataSize::Word + 1, // +PatNum (word)
    Tempo               	= FlpEventDataSize::Word + 2, // obsolete, replaced by FLP_FineTempo
    CurrentPatNum       	= FlpEventDataSize::Word + 3,
    PatData             	= FlpEventDataSize::Word + 4,
    FX                  	= FlpEventDataSize::Word + 5,
    FXFlags             	= FlpEventDataSize::Word + 6,
    FXCut               	= FlpEventDataSize::Word + 7,
    DotVol              	= FlpEventDataSize::Word + 8,
    DotPan              	= FlpEventDataSize::Word + 9,
    FXPreamp            	= FlpEventDataSize::Word + 10,
    FXDecay             	= FlpEventDataSize::Word + 11,
    FXAttack            	= FlpEventDataSize::Word + 12,
    DotNote             	= FlpEventDataSize::Word + 13,
    DotPitch            	= FlpEventDataSize::Word + 14,
    DotMix              	= FlpEventDataSize::Word + 15,
    MainPitch           	= FlpEventDataSize::Word + 16,
    RandChan            	= FlpEventDataSize::Word + 17, // obsolete
    MixChan             	= FlpEventDataSize::Word + 18, // obsolete
    FXRes               	= FlpEventDataSize::Word + 19,
    OldSongLoopPos      	= FlpEventDataSize::Word + 20, // obsolete
    FXStDel             	= FlpEventDataSize::Word + 21,
    FX3                 	= FlpEventDataSize::Word + 22,
    DotFRes             	= FlpEventDataSize::Word + 23,
    DotFCut             	= FlpEventDataSize::Word + 24,
    ShiftTime           	= FlpEventDataSize::Word + 25,
    LoopEndBar          	= FlpEventDataSize::Word + 26,
    Dot                 	= FlpEventDataSize::Word + 27,
    DotShift            	= FlpEventDataSize::Word + 28,
    Tempo_Fine          	= FlpEventDataSize::Word + 29, // obsolete, replaced by FLP_FineTempo
    LayerChan           	= FlpEventDataSize::Word + 30,
    FXIcon              	= FlpEventDataSize::Word + 31,
    DotRel              	= FlpEventDataSize::Word + 32,
    SwingMix            	= FlpEventDataSize::Word + 33,

    // DWORD sized (128..191)
    PluginColor         	= FlpEventDataSize::Dword,
    PLItem              	= FlpEventDataSize::Dword + 1, // Pos (word) +PatNum (word) (obsolete)
    Echo                	= FlpEventDataSize::Dword + 2,
    FXSine              	= FlpEventDataSize::Dword + 3,
    CutCutBy            	= FlpEventDataSize::Dword + 4,
    WindowH             	= FlpEventDataSize::Dword + 5,
    MiddleNote          	= FlpEventDataSize::Dword + 7,
    Reserved            	= FlpEventDataSize::Dword + 8, // may contain an invalid version info
    MainResCut          	= FlpEventDataSize::Dword + 9, // obsolete
    DelayFRes           	= FlpEventDataSize::Dword + 10,
    Reverb              	= FlpEventDataSize::Dword + 11,
    StretchTime         	= FlpEventDataSize::Dword + 12,
    SSNote              	= FlpEventDataSize::Dword + 13, // SimSynth patch middle note (obsolete)
    FineTune            	= FlpEventDataSize::Dword + 14,
    SampleFlags         	= FlpEventDataSize::Dword + 15,
    LayerFlags          	= FlpEventDataSize::Dword + 16,
    ChanFilterNum       	= FlpEventDataSize::Dword + 17,
    CurrentFilterNum    	= FlpEventDataSize::Dword + 18,
    FXOutChanNum        	= FlpEventDataSize::Dword + 19, // FX track output channel
    NewTimeMarker       	= FlpEventDataSize::Dword + 20, // + Time & Mode in higher bits
    FXColor             	= FlpEventDataSize::Dword + 21,
    PatColor            	= FlpEventDataSize::Dword + 22,
    PatAutoMode         	= FlpEventDataSize::Dword + 23, // obsolete
    SongLoopPos         	= FlpEventDataSize::Dword + 24,
    AUSmpRate           	= FlpEventDataSize::Dword + 25,
    FXInChanNum         	= FlpEventDataSize::Dword + 26, // FX track input channel
    PluginIcon          	= FlpEventDataSize::Dword + 27,
    FineTempo           	= FlpEventDataSize::Dword + 28,

    // Variable size (192..255) - Text is null terminated AnsiString
    Text_ChanName       	= FlpEventDataSize::Variable ,  // obsolete
    Text_PatName        	= FlpEventDataSize::Variable + 1,
    Text_Title          	= FlpEventDataSize::Variable + 2,
    Text_Comment        	= FlpEventDataSize::Variable + 3,
    Text_SampleFileName 	= FlpEventDataSize::Variable + 4,
    Text_URL            	= FlpEventDataSize::Variable + 5,
    Text_CommentRTF     	= FlpEventDataSize::Variable + 6, // comments in Rich Text format
    Version             	= FlpEventDataSize::Variable + 7,
    RegName             	= FlpEventDataSize::Variable + 8, // since 1.3.9 the (scrambled) reg name is stored in the FLP
    Text_DefPluginName  	= FlpEventDataSize::Variable + 9,
    //FLP_Text_CommentRTF_SC 	=FLP_Text+10, // new comments in Rich Text format (obsolete)
    Text_ProjDataPath   	= FlpEventDataSize::Variable + 10,
    Text_PluginName     	= FlpEventDataSize::Variable + 11, // plugin's name
    Text_FXName         	= FlpEventDataSize::Variable + 12, // FX track name
    Text_TimeMarker     	= FlpEventDataSize::Variable + 13, // time marker name
    Text_Genre          	= FlpEventDataSize::Variable + 14,
    Text_Author         	= FlpEventDataSize::Variable + 15,
    MIDICtrls           	= FlpEventDataSize::Variable + 16,
    Delay               	= FlpEventDataSize::Variable + 17,
    TS404Params         	= FlpEventDataSize::Variable + 18,
    DelayLine           	= FlpEventDataSize::Variable + 19, // obsolete
    NewPlugin           	= FlpEventDataSize::Variable + 20, // new VST or DirectX plugin
    PluginParams        	= FlpEventDataSize::Variable + 21,
    Reserved2           	= FlpEventDataSize::Variable + 22, // used once for testing
    ChanParams          	= FlpEventDataSize::Variable + 23, // block of various channel params (can grow)
    CtrlRecChan         	= FlpEventDataSize::Variable + 24, // automated controller events
    PLSel               	= FlpEventDataSize::Variable + 25, // selection in playlist
    Envelope            	= FlpEventDataSize::Variable + 26,
    ChanLevels          	= FlpEventDataSize::Variable + 27, // pan, vol, pitch, filter, filter type
    ChanFilter          	= FlpEventDataSize::Variable + 28, // cut, res, type (obsolete)
    ChanPoly            	= FlpEventDataSize::Variable + 29, // max poly, poly slide, monophonic
    NoteRecChan         	= FlpEventDataSize::Variable + 30, // automated note events
    PatCtrlRecChan      	= FlpEventDataSize::Variable + 31, // automated ctrl events per pattern
    PatNoteRecChan      	= FlpEventDataSize::Variable + 32, // automated note events per pattern
    InitCtrlRecChan     	= FlpEventDataSize::Variable + 33, // init values for automated events
    RemoteCtrl_MIDI     	= FlpEventDataSize::Variable + 34, // remote control entry (MIDI)
    RemoteCtrl_Int      	= FlpEventDataSize::Variable + 35, // remote control entry (internal)
    Tracking            	= FlpEventDataSize::Variable + 36, // vol/kb tracking
    ChanOfsLevels       	= FlpEventDataSize::Variable + 37, // levels offset
    Text_RemoteCtrlFormula 	= FlpEventDataSize::Variable + 38, // remote control entry formula
    Text_ChanFilter     	= FlpEventDataSize::Variable + 39,
    RegBlackList        	= FlpEventDataSize::Variable + 40, // black list of reg codes
    PLRecChan           	= FlpEventDataSize::Variable + 41, // playlist
    ChanAC              	= FlpEventDataSize::Variable + 42, // channel articulator
    FXRouting           	= FlpEventDataSize::Variable + 43,
    FXParams            	= FlpEventDataSize::Variable + 44,
    ProjectTime         	= FlpEventDataSize::Variable + 45,
    PLTrackInfo         	= FlpEventDataSize::Variable + 46,
    Text_PLTrackName    	= FlpEventDataSize::Variable + 47,

};

// --------------------------------------------------------------------------------

bool FlpTypeMatchesSize(FlpEventType type, FlpEventSize size);

// --------------------------------------------------------------------------------

FlpEventSize GetEventSize(FlpEventType type);

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------

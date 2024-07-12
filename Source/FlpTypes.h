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

struct FlpEventSize
{
    static constexpr std::uint8_t Byte     = 0b00 << 6;
    static constexpr std::uint8_t Word     = 0b01 << 6;
    static constexpr std::uint8_t Dword    = 0b10 << 6;
    static constexpr std::uint8_t Variable = 0b11 << 6;
};

// --------------------------------------------------------------------------------

enum class FlpEventType : std::uint8_t
{
    // BYTE sized (0..63)
    ChanEnabled         	= FlpEventSize::Byte,
    NoteOn              	= FlpEventSize::Byte + 1, // +pos
    ChanVol             	= FlpEventSize::Byte + 2, // obsolete
    ChanPan             	= FlpEventSize::Byte + 3, // obsolete
    MIDIChan            	= FlpEventSize::Byte + 4,
    MIDINote            	= FlpEventSize::Byte + 5,
    MIDIPatch           	= FlpEventSize::Byte + 6,
    MIDIBank            	= FlpEventSize::Byte + 7,
    LoopActive          	= FlpEventSize::Byte + 9,
    ShowInfo            	= FlpEventSize::Byte + 10,
    Shuffle             	= FlpEventSize::Byte + 11,
    MainVol             	= FlpEventSize::Byte + 12, // obsolete
    FitToSteps          	= FlpEventSize::Byte + 13, // obsolete byte version
    Pitchable           	= FlpEventSize::Byte + 14, // obsolete
    Zipped              	= FlpEventSize::Byte + 15,
    Delay_Flags         	= FlpEventSize::Byte + 16, // obsolete
    TimeSig_Num         	= FlpEventSize::Byte + 17,
    TimeSig_Beat        	= FlpEventSize::Byte + 18,
    UseLoopPoints       	= FlpEventSize::Byte + 19,
    LoopType            	= FlpEventSize::Byte + 20,
    ChanType            	= FlpEventSize::Byte + 21,
    TargetFXTrack       	= FlpEventSize::Byte + 22,
    PanVolTab           	= FlpEventSize::Byte + 23, // log vol & circular pan tables
    nStepsShown         	= FlpEventSize::Byte + 24, // obsolete
    SSLength            	= FlpEventSize::Byte + 25, // +length
    SSLoop              	= FlpEventSize::Byte + 26,
    FXProps             	= FlpEventSize::Byte + 27, // FlipY, ReverseStereo, etc
    Registered          	= FlpEventSize::Byte + 28, // reg version
    APDC                	= FlpEventSize::Byte + 29,
    TruncateClipNotes   	= FlpEventSize::Byte + 30,
    EEAutoMode          	= FlpEventSize::Byte + 31,

    // WORD sized (63..127)
    NewChan             	= FlpEventSize::Word ,
    NewPat              	= FlpEventSize::Word + 1, // +PatNum (word)
    Tempo               	= FlpEventSize::Word + 2, // obsolete, replaced by FLP_FineTempo
    CurrentPatNum       	= FlpEventSize::Word + 3,
    PatData             	= FlpEventSize::Word + 4,
    FX                  	= FlpEventSize::Word + 5,
    FXFlags             	= FlpEventSize::Word + 6,
    FXCut               	= FlpEventSize::Word + 7,
    DotVol              	= FlpEventSize::Word + 8,
    DotPan              	= FlpEventSize::Word + 9,
    FXPreamp            	= FlpEventSize::Word + 10,
    FXDecay             	= FlpEventSize::Word + 11,
    FXAttack            	= FlpEventSize::Word + 12,
    DotNote             	= FlpEventSize::Word + 13,
    DotPitch            	= FlpEventSize::Word + 14,
    DotMix              	= FlpEventSize::Word + 15,
    MainPitch           	= FlpEventSize::Word + 16,
    RandChan            	= FlpEventSize::Word + 17, // obsolete
    MixChan             	= FlpEventSize::Word + 18, // obsolete
    FXRes               	= FlpEventSize::Word + 19,
    OldSongLoopPos      	= FlpEventSize::Word + 20, // obsolete
    FXStDel             	= FlpEventSize::Word + 21,
    FX3                 	= FlpEventSize::Word + 22,
    DotFRes             	= FlpEventSize::Word + 23,
    DotFCut             	= FlpEventSize::Word + 24,
    ShiftTime           	= FlpEventSize::Word + 25,
    LoopEndBar          	= FlpEventSize::Word + 26,
    Dot                 	= FlpEventSize::Word + 27,
    DotShift            	= FlpEventSize::Word + 28,
    Tempo_Fine          	= FlpEventSize::Word + 29, // obsolete, replaced by FLP_FineTempo
    LayerChan           	= FlpEventSize::Word + 30,
    FXIcon              	= FlpEventSize::Word + 31,
    DotRel              	= FlpEventSize::Word + 32,
    SwingMix            	= FlpEventSize::Word + 33,

    // DWORD sized (128..191)
    PluginColor         	= FlpEventSize::Dword,
    PLItem              	= FlpEventSize::Dword + 1, // Pos (word) +PatNum (word) (obsolete)
    Echo                	= FlpEventSize::Dword + 2,
    FXSine              	= FlpEventSize::Dword + 3,
    CutCutBy            	= FlpEventSize::Dword + 4,
    WindowH             	= FlpEventSize::Dword + 5,
    MiddleNote          	= FlpEventSize::Dword + 7,
    Reserved            	= FlpEventSize::Dword + 8, // may contain an invalid version info
    MainResCut          	= FlpEventSize::Dword + 9, // obsolete
    DelayFRes           	= FlpEventSize::Dword + 10,
    Reverb              	= FlpEventSize::Dword + 11,
    StretchTime         	= FlpEventSize::Dword + 12,
    SSNote              	= FlpEventSize::Dword + 13, // SimSynth patch middle note (obsolete)
    FineTune            	= FlpEventSize::Dword + 14,
    SampleFlags         	= FlpEventSize::Dword + 15,
    LayerFlags          	= FlpEventSize::Dword + 16,
    ChanFilterNum       	= FlpEventSize::Dword + 17,
    CurrentFilterNum    	= FlpEventSize::Dword + 18,
    FXOutChanNum        	= FlpEventSize::Dword + 19, // FX track output channel
    NewTimeMarker       	= FlpEventSize::Dword + 20, // + Time & Mode in higher bits
    FXColor             	= FlpEventSize::Dword + 21,
    PatColor            	= FlpEventSize::Dword + 22,
    PatAutoMode         	= FlpEventSize::Dword + 23, // obsolete
    SongLoopPos         	= FlpEventSize::Dword + 24,
    AUSmpRate           	= FlpEventSize::Dword + 25,
    FXInChanNum         	= FlpEventSize::Dword + 26, // FX track input channel
    PluginIcon          	= FlpEventSize::Dword + 27,
    FineTempo           	= FlpEventSize::Dword + 28,

    // Variable size (192..255) - Text is null terminated AnsiString
    Text_ChanName       	= FlpEventSize::Variable ,  // obsolete
    Text_PatName        	= FlpEventSize::Variable + 1,
    Text_Title          	= FlpEventSize::Variable + 2,
    Text_Comment        	= FlpEventSize::Variable + 3,
    Text_SampleFileName 	= FlpEventSize::Variable + 4,
    Text_URL            	= FlpEventSize::Variable + 5,
    Text_CommentRTF     	= FlpEventSize::Variable + 6, // comments in Rich Text format
    Version             	= FlpEventSize::Variable + 7,
    RegName             	= FlpEventSize::Variable + 8, // since 1.3.9 the (scrambled) reg name is stored in the FLP
    Text_DefPluginName  	= FlpEventSize::Variable + 9,
    //FLP_Text_CommentRTF_SC 	=FLP_Text+10, // new comments in Rich Text format (obsolete)
    Text_ProjDataPath   	= FlpEventSize::Variable + 10,
    Text_PluginName     	= FlpEventSize::Variable + 11, // plugin's name
    Text_FXName         	= FlpEventSize::Variable + 12, // FX track name
    Text_TimeMarker     	= FlpEventSize::Variable + 13, // time marker name
    Text_Genre          	= FlpEventSize::Variable + 14,
    Text_Author         	= FlpEventSize::Variable + 15,
    MIDICtrls           	= FlpEventSize::Variable + 16,
    Delay               	= FlpEventSize::Variable + 17,
    TS404Params         	= FlpEventSize::Variable + 18,
    DelayLine           	= FlpEventSize::Variable + 19, // obsolete
    NewPlugin           	= FlpEventSize::Variable + 20, // new VST or DirectX plugin
    PluginParams        	= FlpEventSize::Variable + 21,
    Reserved2           	= FlpEventSize::Variable + 22, // used once for testing
    ChanParams          	= FlpEventSize::Variable + 23, // block of various channel params (can grow)
    CtrlRecChan         	= FlpEventSize::Variable + 24, // automated controller events
    PLSel               	= FlpEventSize::Variable + 25, // selection in playlist
    Envelope            	= FlpEventSize::Variable + 26,
    ChanLevels          	= FlpEventSize::Variable + 27, // pan, vol, pitch, filter, filter type
    ChanFilter          	= FlpEventSize::Variable + 28, // cut, res, type (obsolete)
    ChanPoly            	= FlpEventSize::Variable + 29, // max poly, poly slide, monophonic
    NoteRecChan         	= FlpEventSize::Variable + 30, // automated note events
    PatCtrlRecChan      	= FlpEventSize::Variable + 31, // automated ctrl events per pattern
    PatNoteRecChan      	= FlpEventSize::Variable + 32, // automated note events per pattern
    InitCtrlRecChan     	= FlpEventSize::Variable + 33, // init values for automated events
    RemoteCtrl_MIDI     	= FlpEventSize::Variable + 34, // remote control entry (MIDI)
    RemoteCtrl_Int      	= FlpEventSize::Variable + 35, // remote control entry (internal)
    Tracking            	= FlpEventSize::Variable + 36, // vol/kb tracking
    ChanOfsLevels       	= FlpEventSize::Variable + 37, // levels offset
    Text_RemoteCtrlFormula 	= FlpEventSize::Variable + 38, // remote control entry formula
    Text_ChanFilter     	= FlpEventSize::Variable + 39,
    RegBlackList        	= FlpEventSize::Variable + 40, // black list of reg codes
    PLRecChan           	= FlpEventSize::Variable + 41, // playlist
    ChanAC              	= FlpEventSize::Variable + 42, // channel articulator
    FXRouting           	= FlpEventSize::Variable + 43,
    FXParams            	= FlpEventSize::Variable + 44,
    ProjectTime         	= FlpEventSize::Variable + 45,
    PLTrackInfo         	= FlpEventSize::Variable + 46,
    Text_PLTrackName    	= FlpEventSize::Variable + 47,

};

// --------------------------------------------------------------------------------

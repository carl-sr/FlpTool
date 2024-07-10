meta:
  id: flp
  title: Image Line FL Studio Project File
  endian: le
  file-extension:
    - flp

doc: |
  The FLP format is loosely based on MIDI and AIFF files.
  Apart from the header, it's just a succession of events.
  Once you understand how to process the file to retrieve
  these events, the only thing you'll need is the list of
  events available. Please note that the format *does not*
  respect theAIFF standard completely, but it's similar.
  DWORD is 4 bytes, WORD is 2 bytes, BYTE is 1 byte. TEXT
  is a sequence of characters. Up to and including version
  11, these were single-byte ansi characters. From version
  12 on, these are 2-byte unicode characters. The exception
  is the FLP_Version event, which remains ansi (for compatibility)

doc-ref:
  - https://forum.image-line.com/viewtopic.php?f=700&t=248115

seq:
  - id: file_header
    type: header
  - id: file_data
    type: data

types:
  header:
    seq:
    - id: chunk_id
      contents: ["FLhd"]
      doc: "4 chars which are the letters 'FLhd' for 'FruityLoops header'"
    - id: length
      type: u4
      doc: "The length of this chunk, like in MIDI files. Atm it's 6, but could evolve"
    - id: format
      type: u2
      doc: "Set to 0 for full songs"
    - id: nchannels
      type: u2
      doc: "The total number of channels (not really used)"
    - id: beatdiv
      type: u2
      doc: "Pulses per quarter of the song"
      
  data:
    seq:
      - id: chunk_id
        contents: ["FLdt"]
        doc: "4 chars which are the letters 'FLdt' for 'FruityLoops data'"
      - id: length
        type: u4
        doc: "The length of (the rest of) this chunk (i.e. WITHOUT these 2 DWORDS)"
      - id: events
        type: event
        repeat: eos


        
        
        
        
  event:
    seq:
      - id: event_data
        type:
          switch-on: event_type_code >> 6
          cases:
            0b00: byte_event
            0b01: word_event
            0b10: dword_event
            0b11: text_event
            

    instances:
      event_type_code:
        pos: _io.pos
        type: u1
        
        
        
            
  byte_event:
    seq:
      - id: type
        type: u1
        enum: byte_event_type
      - id: data
        type: u1
        
  word_event:
    seq:
      - id: type
        type: u1
        enum: word_event_type
      - id: data
        type: u2
        
  dword_event:
    seq:
      - id: type
        type: u1
        enum: dword_event_type
      - id: data
        type: u4
        
  text_event:
    seq:
      - id: type
        type: u1
        enum: text_event_type
      - id: size
        type: u1
      - id: data
        size: size
        

enums:
  byte_event_type:
    # byte sized (0..63)
    0: flp_chan_enabled
    1: flp_note_on # +pos
    2: flp_chan_vol # obsolete
    3: flp_chan_pan # obsolete
    4: flp_midi_chan
    5: flp_midi_note
    6: flp_midi_patch
    7: flp_midi_bank
    9: flp_loop_active
    10: flp_show_info
    11: flp_shuffle
    12: flp_main_vol # obsolete
    13: flp_fit_to_steps # obsolete byteversion
    14: flp_pitchable # obsolete
    15: flp_zipped
    16: flp_delay_flags # obsolete
    17: flp_time_sig_num
    18: flp_time_sig_beat
    19: flp_use_loop_points
    20: flp_loop_type
    21: flp_chan_type
    22: flp_target_fx_track
    23: flp_pan_vol_tab # log vol & circularpan tables
    24: flp_n_steps_shown # obsolete
    25: flp_ss_length # +length
    26: flp_ss_loop
    27: flp_fx_props # flip_y_reverse_stereo etc
    28: flp_registered # reg version
    29: flp_apdc
    30: flp_truncate_clip_notes
    31: flp_ee_auto_mode
  
  word_event_type:    
    # word sized (63..127)
    64: flp_new_chan
    65: flp_new_pat # +pat_num (word)
    66: flp_tempo # obsolete replaced by flp_fine_tempo
    67: flp_current_pat_num
    68: flp_pat_data
    69: flp_fx
    70: flp_fx_flags
    71: flp_fx_cut
    72: flp_dot_vol
    73: flp_dot_pan
    74: flp_fx_preamp
    75: flp_fx_decay
    76: flp_fx_attack
    77: flp_dot_note
    78: flp_dot_pitch
    79: flp_dot_mix
    80: flp_main_pitch
    81: flp_rand_chan # obsolete
    82: flp_mix_chan # obsolete
    83: flp_fx_res
    84: flp_old_song_loop_pos # obsolete
    85: flp_fx_st_del
    86: flp_fx3
    87: flp_dot_f_res
    88: flp_dot_f_cut
    89: flp_shift_time
    90: flp_loop_end_bar
    91: flp_dot
    92: flp_dot_shift
    93: flp_tempo_fine # obsolete replaced by flp_fine_tempo
    94: flp_layer_chan
    95: flp_fx_icon
    96: flp_dot_rel
    97: flp_swing_mix
    
  dword_event_type:
    # dword sized (128..191)
    128: flp_plugin_color
    129: flp_pl_item # pos (word) + pat_num (word) (obsolete)
    130: flp_echo
    131: flp_fx_sine
    132: flp_cut_cut_by
    133: flp_window_h
    135: flp_middle_note
    136: flp_reserved # may containan invalid version info
    137: flp_main_res_cut # obsolete
    138: flp_delay_f_res
    139: flp_reverb
    140: flp_stretch_time
    141: flp_ss_note # sim_synth patch middle note (obsolete)
    142: flp_fine_tune
    143: flp_sample_flags
    144: flp_layer_flags
    145: flp_chan_filter_num
    146: flp_current_filter_num
    147: flp_fx_out_chan_num # fx track outputchannel
    148: flp_new_time_marker # + time & mode in higher bits
    149: flp_fx_color
    150: flp_pat_color
    151: flp_pat_auto_mode # obsolete
    152: flp_song_loop_pos
    153: flp_au_smp_rate
    154: flp_fx_in_chan_num # fx track input channel
    155: flp_plugin_icon
    156: flp_fine_tempo
    
  text_event_type:
    # variable size (192..255)
    192: flp_text_chan_name # obsolete
    193: flp_text_pat_name
    194: flp_text_title
    195: flp_text_comment
    196: flp_text_sample_file_name
    197: flp_text_url
    198: flp_text_comment_rtf # comments in_rich text format
    199: flp_version
    200: flp_reg_name # since 1.3.9 the (scrambled) reg name is stored in the flp
    201: flp_text_def_plugin_name #
    202: flp_text_proj_data_path
    203: flp_text_plugin_name # plugin's name
    204: flp_text_fx_name # fx track name
    205: flp_text_time_marker # time marker name
    206: flp_text_genre
    207: flp_text_author
    208: flp_midi_ctrls
    209: flp_delay
    210: flp_ts404_params
    211: flp_delay_line # obsolete
    212: flp_new_plugin # new vst or direct_xplugin
    213: flp_plugin_params
    214: flp_reserved2 # used once fortesting
    215: flp_chan_params # block of various channel params (can grow)
    216: flp_ctrl_rec_chan # automated controller events
    217: flp_pl_sel # selection in playlist
    218: flp_envelope
    219: flp_chan_levels # pan vol pitch filter filter type
    220: flp_chan_filter # cut res type(obsolete)
    221: flp_chan_poly # max poly poly slide monophonic
    222: flp_note_rec_chan # automated note events
    223: flp_pat_ctrl_rec_chan # automated ctrl events per pattern
    224: flp_pat_note_rec_chan # automated note events per pattern
    225: flp_init_ctrl_rec_chan # init values for automated events
    226: flp_remote_ctrl_midi # remote control entry (midi)
    227: flp_remote_ctrl_int # remote control entry (internal)
    228: flp_tracking # vol/kb tracking
    229: flp_chan_ofs_levels # levels offset
    230: flp_text_remote_ctrl_formula # remote control entry formula
    231: flp_text_chan_filter
    232: flp_reg_black_list # black list of reg codes
    233: flp_pl_rec_chan # playlist
    234: flp_chan_ac # channel articulator
    235: flp_fx_routing
    236: flp_fx_params
    237: flp_project_time
    238: flp_pl_track_info
    239: flp_text_pl_track_name 

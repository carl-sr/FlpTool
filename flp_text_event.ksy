meta:
  id: flp_text_event
  title: Image Line FL Studio Project Text Event
  endian: le

seq:
  - id: type
    type: u1
    enum: text_event_type
  - id: size
    type: u1
  - id: data
    size: size

enums:
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

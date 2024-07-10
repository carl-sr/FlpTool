meta:
  id: flp_dword_event
  title: Image Line FL Studio Project Dword Event
  endian: le

seq:    
  - id: type
    type: u1
    enum: dword_event_type
  - id: data
    type: u4

enums:
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

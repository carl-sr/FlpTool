meta:
  id: flp_word_event
  title: Image Line FL Studio Word Word Event
  endian: le

seq:
  - id: type
    type: u1
    enum: word_event_type
  - id: data
    type: u2

enums:
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

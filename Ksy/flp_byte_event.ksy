meta:
  id: flp_byte_event
  title: Image Line FL Studio Project Byte Event
  endian: le

seq:
  - id: type
    type: u1
    enum: byte_event_type
  - id: data
    type:
      switch-on: type
      cases:
        _: default

types:
  default:
    seq:
      - id: data
        type: u1

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

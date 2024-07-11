meta:
  id: flp
  imports:
    - flp_byte_event
    - flp_word_event
    - flp_dword_event
    - flp_text_event
    
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
            0b00: flp_byte_event
            0b01: flp_word_event
            0b10: flp_dword_event
            0b11: flp_text_event

    instances:
      event_type_code:
        pos: _io.pos
        type: u1
            

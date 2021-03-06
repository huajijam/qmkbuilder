#include "process_music.h"

#ifdef AUDIO_ENABLE
#include "process_audio.h"
#endif
#if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
#include "process_midi.h"
#endif

#if defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))

bool music_activated = false;
uint8_t music_starting_note = 0x0C;
int music_offset = 7;
uint8_t music_mode = MUSIC_MODE_CHROMATIC;

// music sequencer
static bool music_sequence_recording = false;
static bool music_sequence_recorded = false;
static bool music_sequence_playing = false;
static uint8_t music_sequence[16] = {0};
static uint8_t music_sequence_count = 0;
static uint8_t music_sequence_position = 0;

static uint16_t music_sequence_timer = 0;
static uint16_t music_sequence_interval = 100;

#ifdef AUDIO_ENABLE
  #ifndef MUSIC_ON_SONG
    #define MUSIC_ON_SONG SONG(MUSIC_ON_SOUND)
  #endif
  #ifndef MUSIC_OFF_SONG
    #define MUSIC_OFF_SONG SONG(MUSIC_OFF_SOUND)
  #endif
  #ifndef CHROMATIC_SONG
    #define CHROMATIC_SONG SONG(CHROMATIC_SOUND)
  #endif
  #ifndef GUITAR_SONG
    #define GUITAR_SONG SONG(GUITAR_SOUND)
  #endif
  #ifndef VIOLIN_SONG
    #define VIOLIN_SONG SONG(VIOLIN_SOUND)
  #endif
  #ifndef MAJOR_SONG
    #define MAJOR_SONG SONG(MAJOR_SOUND)
  #endif
  float music_mode_songs[NUMBER_OF_MODES][5][2] = {
    CHROMATIC_SONG,
    GUITAR_SONG,
    VIOLIN_SONG,
    MAJOR_SONG
  };
  float music_on_song[][2] = MUSIC_ON_SONG;
  float music_off_song[][2] = MUSIC_OFF_SONG;
#endif

#ifndef MUSIC_MASK
  #define MUSIC_MASK keycode < 0xFF
#endif

static void music_noteon(uint8_t note) {
    #ifdef AUDIO_ENABLE
    process_audio_noteon(note);
    #endif
    #if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_basic_noteon(note);
    #endif
}

static void music_noteoff(uint8_t note) {
    #ifdef AUDIO_ENABLE
    process_audio_noteoff(note);
    #endif
    #if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_basic_noteoff(note);
    #endif
}

void music_all_notes_off(void) {
    #ifdef AUDIO_ENABLE
    process_audio_all_notes_off();
    #endif
    #if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_all_notes_off();
    #endif
}

bool process_music(uint16_t keycode, keyrecord_t *record) {

    if (keycode == MU_ON && record->event.pressed) {
        music_on();
        return false;
    }

    if (keycode == MU_OFF && record->event.pressed) {
        music_off();
        return false;
    }

    if (keycode == MU_TOG && record->event.pressed) {
        if (music_activated) {
            music_off();
        } else {
            music_on();
        }
        return false;
    }

    if (keycode == MU_MOD && record->event.pressed) {
      music_mode_cycle();
      return false;
    }

    if (music_activated) {
      if (record->event.pressed) {
        if (keycode == KC_LCTL) { // Start recording
          music_all_notes_off();
          music_sequence_recording = true;
          music_sequence_recorded = false;
          music_sequence_playing = false;
          music_sequence_count = 0;
          return false;
        }

        if (keycode == KC_LALT) { // Stop recording/playing
          music_all_notes_off();
          if (music_sequence_recording) { // was recording
            music_sequence_recorded = true;
          }
          music_sequence_recording = false;
          music_sequence_playing = false;
          return false;
        }

        if (keycode == KC_LGUI && music_sequence_recorded) { // Start playing
          music_all_notes_off();
          music_sequence_recording = false;
          music_sequence_playing = true;
          music_sequence_position = 0;
          music_sequence_timer = 0;
          return false;
        }

        if (keycode == KC_UP) {
          music_sequence_interval-=10;
          return false;
        }

        if (keycode == KC_DOWN) {
          music_sequence_interval+=10;
          return false;
        }
      }

      uint8_t note;
      if (music_mode == MUSIC_MODE_CHROMATIC) 
        note = (music_starting_note + record->event.key.col + music_offset - 3)+12*(MATRIX_ROWS - record->event.key.row);
      else if (music_mode == MUSIC_MODE_GUITAR)
        note = (music_starting_note + record->event.key.col + music_offset + 32)+5*(MATRIX_ROWS - record->event.key.row);
      else if (music_mode == MUSIC_MODE_VIOLIN)
        note = (music_starting_note + record->event.key.col + music_offset + 32)+7*(MATRIX_ROWS - record->event.key.row);
      else if (music_mode == MUSIC_MODE_MAJOR)
        note = (music_starting_note + SCALE[record->event.key.col + music_offset] - 3)+12*(MATRIX_ROWS - record->event.key.row);
      else
        note = music_starting_note;

      if (record->event.pressed) {
        music_noteon(note);
        if (music_sequence_recording) {
          music_sequence[music_sequence_count] = note;
          music_sequence_count++;
        }
      } else {
        music_noteoff(note);
      }

      if (MUSIC_MASK)
        return false;
    }

    return true;
}

bool is_music_on(void) {
    return (music_activated != 0);
}

void music_toggle(void) {
    if (!music_activated) {
        music_on();
    } else {
        music_off();
    }
}

void music_on(void) {
    music_activated = 1;
    #ifdef AUDIO_ENABLE
      PLAY_SONG(music_on_song);
    #endif
    music_on_user();
}

void music_off(void) {
    music_all_notes_off();
    music_activated = 0;
    #ifdef AUDIO_ENABLE
      PLAY_SONG(music_off_song);
    #endif
}

void music_mode_cycle(void) {
  music_all_notes_off();
  music_mode = (music_mode + 1) % NUMBER_OF_MODES;
  #ifdef AUDIO_ENABLE
    PLAY_SONG(music_mode_songs[music_mode]);
  #endif
}

void matrix_scan_music(void) {
  if (music_sequence_playing) {
    if ((music_sequence_timer == 0) || (timer_elapsed(music_sequence_timer) > music_sequence_interval)) {
      music_sequence_timer = timer_read();
      uint8_t prev_note = music_sequence[(music_sequence_position - 1 < 0)?(music_sequence_position - 1 + music_sequence_count):(music_sequence_position - 1)];
      uint8_t next_note = music_sequence[music_sequence_position];
      music_noteoff(prev_note);
      music_noteon(next_note);
      music_sequence_position = (music_sequence_position + 1) % music_sequence_count;
    }
  }
}

__attribute__ ((weak))
void music_on_user() {}

__attribute__ ((weak))
void music_scale_user() {}

#endif // defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
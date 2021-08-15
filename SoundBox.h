#ifndef SOUNDBOX_H
#define SOUNDBOX_H

#include "SDL_Mixer.h"

class SoundBox{
  bool isMusic;
  Mix_Music *music;
  Mix_Chunk *sound;
public:
  SoundBox();
  SoundBox(const char* path, bool isMusic = true);
  void play();
  void pause();
  void resume();
  void stop();
  ~SoundBox();
};

#endif

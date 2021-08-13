#ifndef SOUNDBOX_H
#define SOUNDBOX_H

#include "SDL_Mixer.h"

class SoundBox{
  Mix_Music *music;

public:
  SoundBox(const char* path);
  void play();
  void pause();
  void resume();
  void stop();
  ~SoundBox();
};

#endif

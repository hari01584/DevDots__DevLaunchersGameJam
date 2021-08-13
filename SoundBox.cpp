#ifndef SOUNDBOX_CPP
#define SOUNDBOX_CPP

#include "SoundBox.h"

SoundBox::SoundBox(const char* path){
  music = Mix_LoadMUS(path);
  if(music == NULL)
  {
      printf("Failed to load %s music! SDL_mixer Error: %s\n", path, Mix_GetError());
  }
}

SoundBox::~SoundBox(){
  stop();
  Mix_FreeMusic(music);
}

void SoundBox::play(){
  if(Mix_PlayingMusic() == 0){
    printf("Playing some moosic\n");
    Mix_PlayMusic(music, -1);
  }
}

void SoundBox::stop(){
  if(Mix_PlayingMusic()){
    Mix_HaltMusic();
  }
}

#endif

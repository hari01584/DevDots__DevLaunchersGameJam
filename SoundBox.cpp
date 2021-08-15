#ifndef SOUNDBOX_CPP
#define SOUNDBOX_CPP

#include "SoundBox.h"

SoundBox::SoundBox(const char* path, bool isMusic){
  this->isMusic = isMusic;
  if(isMusic){
    music = Mix_LoadMUS(path);
    if(music == NULL){
        printf("Failed to load %s music! SDL_mixer Error: %s\n", path, Mix_GetError());
    }
  }
  else{
    sound = Mix_LoadWAV(path);
    if(music == NULL){
        printf("Failed to load %s sound! SDL_mixer Error: %s\n", path, Mix_GetError());
    }
  }
}

SoundBox::~SoundBox(){
  stop();
  if(music && isMusic) Mix_FreeMusic(music);
  if(sound && !isMusic) Mix_FreeChunk(sound);
}

void SoundBox::play(){
  if(isMusic){
    if(Mix_PlayingMusic() == 0){
      Mix_PlayMusic(music, -1);
    }
  }
  else{
    Mix_PlayChannel( -1, sound, 0 );
  }
}

void SoundBox::pause(){
  if(Mix_PausedMusic() == 0 && isMusic){
    Mix_PauseMusic();
  }
}

void SoundBox::resume(){
  if(Mix_PausedMusic() == 1 && isMusic){
    Mix_ResumeMusic();
  }
}

void SoundBox::stop(){
  if(isMusic && Mix_PlayingMusic()){
    Mix_HaltMusic();
  }
}

#endif

#ifndef GAMEOVER_CPP
#define GAMEOVER_CPP

GameOver::GameOver(SDL_Window *window, SDL_Renderer *renderer):SceneLayout(window, renderer){

}

void GameOver::gameloop(float step){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);

  

  SDL_RenderPresent(renderer);
}

void GameOver::eventHandler(const SDL_Event &event){


}

#endif

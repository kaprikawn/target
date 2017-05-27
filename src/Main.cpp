#include <iostream>
#include <cstdlib>
#include "Game.hpp"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main( int argc, char* args[] ) {
  
  Uint32 frameStart, frameTime;
  
  if( !TheGame::Instance() -> init( "Crosshair Shooter Game", 20, 20, 1280, 720, SDL_WINDOW_SHOWN ) ) {
  //if( !TheGame::Instance() -> init( "Crosshair Shooter Game", 20, 20, 100, 100, SDL_WINDOW_SHOWN ) ) {
    std::cout << "Game initialisation failed" << std::endl;
  }
  
  while( TheGame::Instance() -> gameRunning() ) {
    frameStart = SDL_GetTicks();
    
    TheGame::Instance() -> handleEvents();
    TheGame::Instance() -> update();
    TheGame::Instance() -> render();
    
    frameTime = SDL_GetTicks() - frameStart;
    if( frameTime < DELAY_TIME ) {
      SDL_Delay( ( int )( DELAY_TIME - frameTime ) );
    }
  }
  
  return 0;
}

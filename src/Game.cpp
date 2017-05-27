#include <iostream>
#include "Game.hpp"
#include "InputHandler.hpp"
#include "GameStateMachine.hpp"
#include "PlayState.hpp"

Game* Game::s_pInstance = 0;

bool Game::init( const char* title, int xpos, int ypos, int width, int height, int flags ) {
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 ) {
    std::cout << "Failed to load SDL : " << SDL_GetError() << std::endl;
    return false;
  }
  
  m_pWindow = SDL_CreateWindow( title, xpos, ypos, width, height, flags );
  if( !m_pWindow ) {
    std::cout << "Failed to create window : " << SDL_GetError() << std::endl;
    return false;
  }
  
  Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  
  m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, renderFlags );
  if( !m_pRenderer ) {
    std::cout << "Failed to create renderer : " << SDL_GetError() << std::endl;
    return false;
  }
  
  TheTextureManager::Instance() -> init( m_pRenderer );
  TheInputHandler::Instance()   -> initialiseJoysticks();
  
  m_pGameStateMachine = new GameStateMachine();
  m_pGameStateMachine -> changeState( new PlayState() );
  
  running = true;
  
  return true;
}

void Game::handleEvents() {
  TheInputHandler::Instance() -> update();
}

void Game::update() {
  m_pGameStateMachine -> update();
}

void Game::render() {
  SDL_RenderClear( m_pRenderer );
  
  m_pGameStateMachine -> render();
  
  SDL_SetRenderDrawColor( m_pRenderer, 102, 204, 255, 255 );
  SDL_RenderPresent( m_pRenderer );
}

void Game::clean() {
  TheInputHandler::Instance() -> clean();
  SDL_DestroyWindow( m_pWindow );
  SDL_DestroyRenderer( m_pRenderer );
  
  m_pWindow   = nullptr;
  m_pRenderer = nullptr;
}

void Game::quit() {
  TheGame::Instance() -> clean();
  std::cout << "Killing SDL" << std::endl;
  IMG_Quit();
  SDL_Quit();
  running = false;
}


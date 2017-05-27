#include <iostream>
#include "TextureManager.hpp"
#include "SDL_image.h"

TextureManager* TextureManager::s_pInstance = 0;

void TextureManager::init( SDL_Renderer* pRenderer ) {
  SDL_SetRenderDrawColor( pRenderer, 102, 204, 255, 255 );
}

bool TextureManager::load( std::string fileName, std::string id, SDL_Renderer* pRenderer ) {
  
  pTempSurface = IMG_Load( fileName.c_str() );
  
  if( pTempSurface == 0 ) { return false; }
  
  pTexture = SDL_CreateTextureFromSurface( pRenderer, pTempSurface );
  SDL_FreeSurface( pTempSurface );
  
  if( pTexture != 0 ) {
    m_textureMap[id] = pTexture;
    return true;
  }
  return false; // reaching here means something went wrong
}

void TextureManager::draw( std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip ) {
  SDL_Rect srcRect;
  SDL_Rect destRect;
  
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;  
  
  SDL_RenderCopyEx( pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip );
}

void TextureManager::drawFrame( std::string id, int x, int y, int width, int height, float scale, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip ) {
  
  
  srcRect.x = width * currentFrame;
  srcRect.y = height * ( currentRow - 1 );
  srcRect.w = width;
  srcRect.h = height;
  
  destRect.x = x;
  destRect.y = y;
  destRect.w = width  * scale;
  destRect.h = height * scale;
  
  if( id == "player1" ) {
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "width = " << width << std::endl;
    std::cout << "height = " << height << std::endl;
    std::cout << "currentRow = " << currentRow << std::endl;
    std::cout << "srcRect.x = " << srcRect.x << std::endl;
    std::cout << "srcRect.y = " << srcRect.y << std::endl;
    std::cout << "srcect.w = " << srcRect.w << std::endl;
    std::cout << "srcRect.h = " << srcRect.h << std::endl;
  }
  
  SDL_RenderCopyEx( pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip );
}

void TextureManager::clearFromTextureMap( std::string id ) {
  m_textureMap.erase( id );
}

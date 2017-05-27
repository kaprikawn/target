#include <iostream>
#include "Projectile.hpp"
//#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDLHeader.hpp"
#include "Vector2D.hpp"

Projectile::Projectile( ObjectData objectData, int playerX, std::string type ) : Sprite( objectData ) {
  
  //printf( "current x is %d\n", m_position.getX() );
  m_velocity = Vector2D( playerX, 700 ) - m_position.getPosition();
  m_velocity.normalize(); 
  m_velocity *= 100;
  
}

void Projectile::update() {
  Sprite::update();
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {

}




#include <iostream>
#include "Projectile.hpp"
//#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDL.h"
#include "Vector2D.hpp"

Projectile::Projectile( ObjectData objectData, int playerX, int type ) : Sprite( objectData ) {
  projectileType_ = type;
  //printf( "current x is %d\n", m_position.getX() );
  m_velocity = Vector2D( playerX, 700 ) - m_position.getPosition();
  
  m_velocity.normalize();
  
  if( projectileType_ == GRENADE ) {
    m_velocity.setX( m_velocity.getX() * 1.3f ); // give move sideways momentum because the gravity is going to make it fall faster and not reach otherwise
    m_velocity += m_velocity + Vector2D( 0, -5 ); // give some upwards velocity to simulate an arc
    m_velocity *= 100;
  } else {
    m_velocity *= 200;
  }
  
  
}

void Projectile::update() {
  
  if( projectileType_ == GRENADE ) {
    m_velocity = m_velocity + Vector2D( 0, 10 );
  }

  Sprite::update();
  
  if( projectileType_ == GRENADE && m_position.getY() >= 700 ) {
    printf( "grenade has hit the ground\n" );
    v_velocity.setX( 0 );
    v_velocity.setY( 0 );
  }
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {

}




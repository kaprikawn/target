#include <iostream>
#include "Sprite.hpp"
#include "Game.hpp"

Sprite::Sprite( ObjectData objectData ) : 
    m_position( objectData.width, objectData.height, objectData.hb_left_adjust, objectData.hb_right_adjust, objectData.hb_top_adjust, objectData.hb_bottom_adjust )
  , m_velocity( 0, 0 )
  , m_health( 1 )  {
  
  m_animation.loadValues( objectData.stateData );
  
  //std::cout << "initial health for " << objectData.objectType << " is " << objectData.hp << std::endl;
  
  m_health.setInitialHp( objectData.hp );
  m_position.updatePosition( Vector2D( objectData.x, objectData.y ) );
  
  objectData_     = objectData;
  
  m_height        = objectData.height;
  m_width         = objectData.width;
  m_textureID     = objectData.textureID;
  
  m_currentFrame  = 0;
  
}

void Sprite::update() {
  
  float dt = TheGame::Instance() -> getDeltaTime();
  //m_position = m_position + m_velocity * dt;
  
  //std::cout << "x1 is " << m_velocity.getX() << std::endl;
  //std::cout << "x2 is " << m_velocity.getX() << std::endl;
  //std::cout << "dt is " << m_velocity.getX() << std::endl;
  
  m_position.updatePosition( m_position.getPosition() + m_velocity * dt );
  
  if( m_health.getCurrentHp() <= 0 ) {
    m_isDying = true;
    m_spriteState = DYING;
    m_velocity.setX( 0 );
    m_velocity.setY( 0 );
    
  }
  
  // 
  
  if( m_ignoreScale ) {
    m_scale = 1.0;
  } else {
    m_scale = m_position.getScale();
  }
  
  m_destWidth  = m_width * m_scale;
  m_destHeight = m_height * m_scale;
  
  m_drawIndex = m_position.getY() + m_height;
  
  /*
  m_hitbox.setX( m_position.getX() + ( m_hb_left_adjust * m_scale ) );
  m_hitbox.setY( m_position.getY() + ( m_hb_top_adjust * m_scale ) );
  
  m_hitbox_width = ( ( m_width * m_scale ) - ( m_hb_left_adjust * m_scale ) - ( m_hb_right_adjust * m_scale ) );
  m_hitbox_height = ( ( m_height * m_scale ) - ( m_hb_top_adjust * m_scale ) - ( m_hb_bottom_adjust * m_scale ) );
  
  m_bottomY = m_position.getY() + m_destHeight;
  
  
  
  if( m_position.getX() < ( 0 - m_width )
   || m_position.getX() > 1280
   || m_position.getY() < ( 0 - m_height )
   || m_position.getY() > 720 ) {
  
    m_outOfBounds = true;
  } else if ( m_outOfBounds ) {
    m_outOfBounds = false;
  }
  
  
  
  */
  m_currentFrame = m_animation.getFrame( m_spriteState, SDL_GetTicks() );
  m_previousState = m_spriteState;
  
  if( m_currentFrame < 0 && m_isDying ) {
    m_delete = true;
  }
}

void Sprite::render() {
  if( m_velocity.getX() > 0 ) {
    TextureManager::Instance() -> drawFrame( m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_scale, m_currentRow, m_currentFrame, TheGame::Instance() -> getRenderer() );
  } else {
    TextureManager::Instance() -> drawFrame( m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_scale, m_currentRow, m_currentFrame, TheGame::Instance() -> getRenderer(), SDL_FLIP_HORIZONTAL );
  }
}

void Sprite::clean() {

}


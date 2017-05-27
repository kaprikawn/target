#include <iostream>
#include "Enemy.hpp"
#include "Game.hpp"
#include "SDLHeader.hpp"

Enemy::Enemy( ObjectData objectData ) : Sprite( objectData ), destination_( 0, 0 ) {
  
}

void Enemy::calculateVelocity( int pathDataIndex ) {
  destination_.setX( objectData_.pathData[ pathDataIndex_ ].x );
  destination_.setY( objectData_.pathData[ pathDataIndex_ ].y );
  
  m_velocity = destination_ - m_position.getPosition();
  m_velocity.normalize();
  m_velocity *= m_speed;
  //m_spawnProjectile = true;
  
  m_spriteState = MOVING;
  
  pathDataIndex_++;
}

void Enemy::update() {
  if( m_spriteState == DEFAULT ) {
    recalculateVelocity_ = true;
  }
  
  Vector2D distanceFromDest = m_position.getPosition() - destination_;
  int distance = sqrt( pow( distanceFromDest.getX(), 2 ) ) + sqrt( pow( distanceFromDest.getY(), 2 ) );
  
  if( distance < 5 && m_spriteState != FIRING ) {
    m_spriteState = FIRING;
    m_velocity.setX( 0 );
    m_velocity.setY( 0 );
  }
  
  
  if( recalculateVelocity_ ) {
    Enemy::calculateVelocity( pathDataIndex_ );
    recalculateVelocity_ = false;
  }
  
  //std::cout << "next x is " << m_objectData.pathData[0].x << std::endl;
  //std::cout << "size is " << objectData_.pathData.size() << std::endl;
  /*
  m_currentFrame = m_animation.getFrame( m_spriteState, SDL_GetTicks() );
  
  Vector2D distanceFromDest = m_position - m_destination;
  int distance = sqrt( pow( distanceFromDest.getX(), 2 ) ) + sqrt( pow( distanceFromDest.getY(), 2 ) );
  
  if( distance < 5 ) {
    m_destination.setX( m_coordinates[ m_coordinatesIndex ].x );
    m_destination.setY( m_coordinates[ m_coordinatesIndex ].y );
    m_velocity = m_destination - m_position;
    m_velocity.normalize();
    m_velocity *= m_speed;
    m_spawnProjectile = true;
    
    m_coordinatesIndex++;
  }
  
  if( m_outOfBounds && m_hasAppeared ) {
    m_delete = true;
  } else if( !m_outOfBounds ) {
    m_hasAppeared = true;
  }
  
  if( m_isDying ) {
    m_velocity.setX( 0 );
    m_velocity.setY( 0 );
    m_currentRow = 2;
    m_dyingTime++;
    
    if( m_dyingTime > 180 ) {
      m_delete = true;
    } else if( m_dyingTime > 120 ) {
      m_currentFrame = 2;
    } else if( m_dyingTime > 60 ) {
      m_currentFrame = 1;
    } else {
      m_currentFrame = 0;
    }
  }
  */
  Sprite::update();
  
  if( m_currentFrame < 0 ) {
    Enemy::calculateVelocity( pathDataIndex_ );
    m_currentFrame = m_animation.getFrame( m_spriteState, SDL_GetTicks() );
    m_spawnProjectile = true;
    Sprite::update();
  }
}

void Enemy::render() {
  /*
  if( m_health.getCurrentHp() < m_health.getMaxHp() && m_health.getCurrentHp() > 0 ) {
    int yellowWidth = (float)m_hitbox_width * ( (float)m_health.getCurrentHp() / (float)m_health.getMaxHp() );
    int redWidth = m_hitbox_width - yellowWidth;
    
    SDL_SetRenderDrawColor( TheGame::Instance() -> getRenderer(), 255, 255, 0, 255 );
    SDL_Rect yellow;
    yellow.x = m_hitbox.getX();
    yellow.y = m_position.getY() - 10;
    yellow.w = yellowWidth;
    yellow.h = 3;
    SDL_RenderFillRect( TheGame::Instance() -> getRenderer(), &yellow );
    
    SDL_SetRenderDrawColor( TheGame::Instance() -> getRenderer(), 255, 0, 0, 255 );
    SDL_Rect red;
    red.x = yellow.x + yellow.w + 1;
    red.y = yellow.y;
    red.w = redWidth;
    red.h = yellow.h;
    SDL_RenderFillRect( TheGame::Instance() -> getRenderer(), &red );
  }
  */

  Sprite::render();
}

void Enemy::clean() {
  
}


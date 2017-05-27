#include <iostream>
#include <fstream>
#include "Player.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDL.h"
//#include "json.hpp"
//#include "JsonLoader.hpp"

Player::Player( ObjectData objectData ) : Sprite( objectData ) {
  
  m_ignoreScale   = true;
  
}

void Player::handleInput() {

  if( m_isDying ) {
    return;
  }
  
  if( TheInputHandler::Instance() -> isPressed( FIRE ) ) {
    m_isFiring = true;
  } else {
    m_isFiring = false;
  }
  
  if( TheInputHandler::Instance() -> isPressed( ROLL ) ) {
    if( m_spriteState == DEFAULT || m_spriteState == MOVING || m_spriteState == FIRING ) {
      m_spriteState = DODGING;
    }
  }
  
  /*
  if( m_spriteState == DODGING ) {
    m_dodgeFrames++;
    //printf( "here\n" );
    m_velocity.setX( 0 );
    if( m_dodgeFrames > 200 ) {
      m_spriteState = DEFAULT;
      
    } else if( m_dodgeFrames > 160 ) {
      m_spriteState = DODGE1;
    } else if( m_dodgeFrames > 140 ) {
      m_spriteState = DODGE2;
    } else if( m_dodgeFrames > 120 ) {
      m_spriteState = DODGE3;
    } else if( m_dodgeFrames > 100 ) {
      if( m_lastDirection == DIR_LEFT ) {
        m_velocity.setX( -150 );
      } else {
        m_velocity.setX( 150 );
      }
    } else if( m_dodgeFrames > 40 ) {
      m_spriteState = DODGE3;
    } else if( m_dodgeFrames > 20 ) {
      m_spriteState = DODGE2;
    } else if( m_dodgeFrames > 0 ) {
      m_spriteState = DODGE1;
    }
    
  }
  */
  
  if( m_spriteState != DODGING ) {
    if( TheInputHandler::Instance() -> isPressed( RIGHT ) && !m_isFiring && m_position.getX() < 1280 - m_width  ) {
      m_spriteState = MOVING;
      
      m_velocity.setX( 200 );
      m_lastDirection = DIR_RIGHT;
    } else if( TheInputHandler::Instance() -> isPressed( LEFT ) && !m_isFiring && m_position.getX() > 0 ) {
      m_spriteState = MOVING;
      m_velocity.setX( -200 );
      m_lastDirection = DIR_LEFT;
    } else {
      m_velocity.setX( 0 );
      m_spriteState = DEFAULT;
    }
  }
}

void Player::update() {
  
  /*
  if( m_health.getCurrentHp() <= 0 ) {
    m_velocity.setX( 0 );
    m_dyingTime++;
    if( m_isDying ) {
      if( m_dyingTime > 160 ) {
        m_currentLives--;
        m_spriteState = DEFAULT;
        m_dyingTime = 0;
        m_isDying = false;
        m_health.setInitialHp( 1 );
      } else if( m_dyingTime > 120 ) {
        m_spriteState = DYING4;
      } else if( m_dyingTime > 80 ) {
        m_spriteState = DYING3;
      } else if( m_dyingTime > 40 ) {
        m_spriteState = DYING2;
      } else {
        m_spriteState = DYING1;
      }
    } else {
      m_isDying = true;
    }
  }
  */
  handleInput();
  //m_currentFrame = m_animation.getFrame( m_spriteState, SDL_GetTicks() );
  
  if( m_spriteState == DODGING ) {
    m_frameNumber = m_animation.getFrameNumber();
    if( m_frameNumber < 3 ) {
      if( m_lastDirection == DIR_LEFT ) {
        m_velocity.setX( -250 );
      } else {
        m_velocity.setX( 250 );
      }
    } else if( m_frameNumber == 3 ) {
      if( m_lastDirection == DIR_LEFT ) {
        m_velocity.setX( -50 );
      } else if( m_lastDirection == DIR_RIGHT ) {
        m_velocity .setX( 50 );
      }
    } else if( m_frameNumber > 3 ) {
      m_velocity.setX( 0 );
    }
  }
  //std::cout << "state is " << m_spriteState << std::endl;
  //std::cout << "cur frame " << m_currentFrame << std::endl;
  
  if( m_position.getX() >= 1279 - m_width && m_velocity.getX() > 0 ) {
    m_velocity.setX( 0 );
  } else if( m_position.getX() <= 1 && m_velocity.getX() < 0 ) {
    m_velocity.setX( 0 );
  }
  
  //std::cout << "currentState is " << m_spriteState << std::endl;
  
  Sprite::update();
  
  if( m_currentFrame < 0 ) {
    m_spriteState = DEFAULT;
    handleInput();
    m_currentFrame = m_animation.getFrame( m_spriteState, SDL_GetTicks() );
  }
  
  //m_delete = false;
  
}

void Player::render() {
  //std::cout << "rendering player\n";
  //std::cout << "frame" << m_currentFrame << std::endl;
  //std::cout << "row" << m_currentRow << std::endl;
  Sprite::render();
}

void Player::clean() {

}


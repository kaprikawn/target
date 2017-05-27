#include <iostream>
#include "Target.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDLHeader.hpp"

Target::Target( ObjectData objectData ) : Sprite( objectData ) {
  
  m_ignoreScale   = true;
  
}

void Target::handleInput() {
  
  if( TheInputHandler::Instance() -> isPressed( FIRE ) ) {
    m_isFiring  = true;
    //m_numFrames = 2;
    m_spriteState = FIRING;
  } else {
    m_isFiring  = false;
    //m_numFrames = 1;
    m_spriteState = DEFAULT;
  }
  
  //if( TheInputHandler::Instance() -> isKeyDown( SDL_SCANCODE_RIGHT ) ) {
  if( TheInputHandler::Instance() -> isPressed( RIGHT ) && m_position.getX() < 1280 - m_width ) {
    if( m_isFiring ) {
      m_velocity.setX( 150 );
    } else {
      m_velocity.setX( 400 );
    }
    
  } else if( TheInputHandler::Instance() -> isPressed( LEFT ) && m_position.getX() > 0 ) {
    if( m_isFiring ) {
      m_velocity.setX( -150 );
    } else {
      m_velocity.setX( -400 );
    }
  } else {
    m_velocity.setX( 0 );
  }
  
  if( TheInputHandler::Instance() -> isPressed( DOWN ) && m_position.getY() < 720 - m_height ) {
    if( m_isFiring ) {
      m_velocity.setY( 150 );
    } else {
      m_velocity.setY( 400 );
    }
    
  } else if( TheInputHandler::Instance() -> isPressed( UP ) && m_position.getY() > 0 ) {
    if( m_isFiring ) {
      m_velocity.setY( -150 );
    } else {
      m_velocity.setY( -400 );
    }
  } else {
    m_velocity.setY( 0 );
  }
}

void Target::update() {
  handleInput();
  //m_currentFrame = m_currentFrame = m_animation.getFrame( m_spriteState, SDL_GetTicks() );
  Sprite::update();
}

void Target::render() {
  Sprite::render();
}

void Target::clean() {

}


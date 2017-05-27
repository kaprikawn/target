#include <iostream>
#include "Scenary.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDL.h"

Scenary::Scenary( ObjectData objectData ) : Sprite( objectData ) {
  
}

void Scenary::update() {
  //if( m_isDying ) {
    //m_delete = true;
  //}
  
  if( m_health.getCurrentHp() <= 0 ) {
    /*
    m_dyingTime++;
    if( m_isDying ) {
      if( m_dyingTime > 160 ) {
        m_delete = true;
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
    }*/
  } else if( m_health.getCurrentHp() < m_health.getMaxHp() ) {
    if( m_health.getCurrentHp() < 260 ) {
      m_spriteState = DAMAGED3;
    } else if( m_health.getCurrentHp() < 510 ) {
      m_spriteState = DAMAGED2;
    } else if( m_health.getCurrentHp() < 760 ) {
      m_spriteState = DAMAGED1;
    }
  }
  
  //m_currentFrame = m_animation.getFrame( m_spriteState, SDL_GetTicks() );
  
  Sprite::update();
}

void Scenary::render() {
  Sprite::render();
}

void Scenary::clean() {

}


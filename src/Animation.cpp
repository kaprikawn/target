#include <iostream>
#include "Animation.hpp"

void Animation::changeState( int newSpriteState ) {
  m_animationData.clear();
  msSinceChangedAnim_ = 0;
  
  for( int i = 0; i < m_stateData.size(); i++ ) {
    if( m_stateData[i].spriteState == newSpriteState ) {
      m_fixedAnimation = m_stateData[i].fixedAnim;
      for( int a = 0; a < m_stateData[i].animData.size(); a++ ) {
        m_animationData.push_back( m_stateData[i].animData[a] );
      }
      m_lastSpriteState = newSpriteState;
      //printf( "changing state to %d\n", newSpriteState );
      return;
    }
  }
}

void Animation::loadAnimationData( int animationDataIndex ) {
  
}

void Animation::loadValues( std::vector<StateData>& stateData ) {
  m_stateData = stateData;
  
  //std::cout << "stateData size is " << m_stateData.size() << std::endl;
  //std::cout << "anim size is " << m_stateData[0].animData.size() << std::endl;
  //std::cout << "swap after is " << m_stateData[0].animData[0].swapFrameAfter << std::endl;
  
  Animation::changeState( 0 );
}

int Animation::getFrame( int spriteState, Uint32 currentTime ) {
  
  m_changeFrame = false;
  
  if( m_currentIndex == -1 ) {
    Animation::changeState( spriteState );
    m_currentIndex = 0;
  }
  
  // if fixed animation and msSinceChangedAnim > swapAnimAfter
  if( m_fixedAnimation && msSinceChangedAnim_ > m_animationData[ m_currentIndex ].swapAnimAfter ) {
    m_currentIndex++;
    if( m_currentIndex >= m_animationData.size() ) {
      m_currentIndex = 0;
      return -1;
    }
    msSinceChangedAnim_ = 0;
    m_returnFrame       = 0;
    m_changeFrame       = true;
  } else if( msSinceChangedFrame_ > m_animationData[ m_currentIndex ].swapFrameAfter ) {
    m_changeFrame       = true;
  } else if( spriteState != m_lastSpriteState ) {
    m_changeFrame       = true;
    Animation::changeState( spriteState );
  }
  
  //printf( "here Animation.cpp\n" );
  
  if( m_changeFrame ) {
    if( m_animationData[ m_currentIndex ].oscillate ) {
      if( m_frameStep == 1 && m_returnFrame >= m_animationData[ m_currentIndex ].maxFrame ) {
        m_frameStep = -1;
      } else if( m_frameStep == -1 && m_returnFrame <= m_animationData[ m_currentIndex ].minFrame ) {
        m_frameStep = 1;
      } else if( m_frameStep == -1 && m_returnFrame == 0 ) {
        m_frameStep = 1;
      }
    }
    
    m_returnFrame += m_frameStep;
    msSinceChangedFrame_ = 0;
  } else {
    msSinceChangedFrame_  += currentTime - m_previousTime;
    msSinceChangedAnim_   += currentTime - m_previousTime;
  }
  
  //std::cout << "msSinceChangedFrame is " << msSinceChangedFrame_ << std::endl;
  //std::cout << "swapFrameAfter is " << m_animationData[ m_currentIndex ].swapFrameAfter << std::endl;
  
  if( m_returnFrame > m_animationData[ m_currentIndex ].maxFrame ) {
    m_returnFrame = m_animationData[ m_currentIndex ].minFrame;
  }
  
  if( m_returnFrame < m_animationData[ m_currentIndex ].minFrame || m_returnFrame < 0 ) {
    m_returnFrame = m_animationData[ m_currentIndex ].minFrame;
  }
  
  m_previousTime = currentTime;
  
  
  return m_returnFrame;
  
}

int Animation::getFrameNumber() {
  return m_currentIndex + 1;
}
/*
struct AnimationData {
  int   currentRow  = 1;
  int   minFrame    = 0;
  int   maxFrame    = 0;
  int   frameDelay  = 1000;
  bool  oscillate   = false;
  bool  fixedAnim   = false;
};

struct StateData {
  std::string id    = "NULLID";
  int   spriteState;
  std::vector<AnimationData> animData;
};*/

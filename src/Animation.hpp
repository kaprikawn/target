#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <unordered_map>
#include <vector>
#include "SDL.h"
#include "Structs.hpp"

class Animation {
  
  private:
    std::vector<StateData>        m_stateData;
    std::vector<AnimationData>    m_animationData;
    
    Uint32  m_previousTime        = SDL_GetTicks();
    //Uint32  m_currentTime       = SDL_GetTicks();
    
    bool    m_fixedAnimation      = false;
    
    int     m_frameStep           = 1;
    //int     m_msSinceChange     = 0; // milliseconds since last change of frame
    //int     m_msSinceLastFrame    = 0;
    int     m_lastSpriteState     = 0;
    
    int     msSinceChangedAnim_   = 0;
    int     msSinceChangedFrame_  = 0;
    
    int     m_returnFrame         = 0;
    unsigned int m_currentIndex   = -1;
    bool    m_changeFrame         = false;
    
  public:
  
    void  loadValues( std::vector<StateData>& stateData );
    void  changeState( int newSpriteState );
    int   getFrame( int spriteState, Uint32 currentTime );
    int   getFrameNumber();
    void  loadAnimationData( int animationDataIndex );
    
    Animation(){};
    ~Animation(){}
    
    
};

#endif //ANIMATION_HPP

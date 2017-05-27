#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Sprite.hpp"


class Player : public Sprite {
  
  private:
    
    //int   m_currentLives  = 3;
    int   m_lastDirection = 0;
    int   m_frameNumber   = 0;
    
    void  handleInput();
    
    
    
  public:
    
    Player( ObjectData objectData );
    virtual ~Player(){}
    
    virtual void update ();
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //PLAYER_HPP

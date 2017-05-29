#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Sprite.hpp"


class Player : public Sprite {
  
  private:
    
    //int   m_currentLives  = 3;
    int   m_lastDirection = 0;
    int   m_frameNumber   = 0;
    
    void  handleInput();
    bool  throwBomb_ = false;
    Uint32  msSinceLastBomb_ = 0;
   
    
    
  public:
    
    Player( ObjectData objectData );
    virtual ~Player(){}
    
    virtual void update ();
    virtual void render ();
    virtual void clean  ();
    
    bool throwingBomb() {
      return throwBomb_;
    }

    void setThrowBomb( bool throwBomb ) {
      throwBomb_ = throwBomb;
    }
    
};

#endif //PLAYER_HPP

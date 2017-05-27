#ifndef TARGET_HPP
#define TARGET_HPP

#include "Sprite.hpp"

class Target : public Sprite {
  
  private:
    
    void  handleInput();
    
    
  public:
    
    Target( ObjectData objectData );
    virtual ~Target(){}
    
    virtual void update ();
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //TARGET_HPP

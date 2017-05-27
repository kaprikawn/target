#ifndef SCENARY_HPP
#define SCENARY_HPP

#include "Sprite.hpp"
#include "Structs.hpp"

class Scenary : public Sprite {
  private:
    
    
  public:
  
    Scenary( ObjectData objectData );
    virtual ~Scenary(){}
    
    virtual void update ();
    virtual void render ();
    virtual void clean  ();
    
};

#endif //SCENARY_HPP

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Sprite.hpp"

class Projectile : public Sprite {
  
  private:
    int projectileType_ = 0;
    
  public:
    
    //Projectile( int x, int y, int destinationX, int destinationY, int speed, bool deleteAtDestination, bool isHostile, bool isPlayerGenerated );
    Projectile( ObjectData objectData, int playerX, int type );
    virtual ~Projectile(){}
    
    virtual void update ();
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //PROJECTILE_HPP

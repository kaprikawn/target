#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Sprite.hpp"

class Projectile : public Sprite {
  
  private:
    //bool isAtDestination      = false;
    //bool m_deleteAtDestination  = false;
    
    //Vector2D m_destination;
    
    
  public:
    
    //Projectile( int x, int y, int destinationX, int destinationY, int speed, bool deleteAtDestination, bool isHostile, bool isPlayerGenerated );
    Projectile( ObjectData objectData, int playerX, std::string type );
    virtual ~Projectile(){}
    
    virtual void update ();
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //PROJECTILE_HPP

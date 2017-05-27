#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include "Sprite.hpp"
#include "Vector2D.hpp"
#include "Animation.hpp"
#include "JsonLoader.hpp"
#include "Structs.hpp"

class Enemy : public Sprite {

  private:
    int       pathDataIndex_ = 0;
    bool      recalculateVelocity_ = false;
    Vector2D  destination_;
    
    std::vector<Path> paths_;
  public:
  
    Enemy( ObjectData objectData );
    
    void update ();
    void render ();
    void clean  ();
    
    void calculateVelocity( int pathDataIndex );
     
};

#endif //ENEMY_HPP

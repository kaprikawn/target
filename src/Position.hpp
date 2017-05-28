#ifndef POSITION_HPP
#define POSITION_HPP

#include "Vector2D.hpp"
#include "Structs.hpp"

class Position {

  private:
    Vector2D  m_position;
    
    Vector2D  m_hitbox;
    Hitbox    hitbox_;
    Vector2D  spriteCenter_;
    
    int       m_width;
    int       m_height;
    float     m_destWidth;
    float     m_destHeight;
    float     m_scale;
    int       m_bottomY; // y coordinate of the bottom of the sprite
    bool      m_outOfBounds       = false;
    
    //int       m_hitbox_width      = 0;
    //int       m_hitbox_height     = 0;
    
    int       m_hb_left_adjust    = 0;
    int       m_hb_right_adjust   = 0;
    int       m_hb_top_adjust     = 0;
    int       m_hb_bottom_adjust  = 0;
    
  public:
    
    Position( int width, int height, int hb_left_adjust, int hb_right_adjust, int hb_top_adjust, int hb_bottom_adjust );
    ~Position(){}
    
    void updatePosition( Vector2D new_xy );
    
    Vector2D getPosition()  { return m_position; }
    int getX()              { return m_position.getX(); }
    int getY()              { return m_position.getY(); }
    float getScale()        { return m_scale; }
    Hitbox getHitbox()      { return hitbox_; }
    Vector2D getSpriteCenter();
  
};

#endif //POSITION_HPP

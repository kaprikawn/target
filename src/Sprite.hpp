#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Vector2D.hpp"
#include "Animation.hpp"
#include "Health.hpp"
#include "JsonLoader.hpp"
#include "Structs.hpp"
#include "Position.hpp"

class Sprite {

  protected:
    
    ObjectData  objectData_;
  
    Position    m_position;
    Vector2D    m_velocity;
    Animation   m_animation;
    
    int         m_width;
    int         m_height;
    float       m_destWidth;
    float       m_destHeight;
    float       m_scale;
    bool        m_ignoreScale = false;
    int         m_bottomY; // y coordinate of the bottom of the sprite
    int         m_currentRow        = 1;
    int         m_currentFrame      = 0;
    std::string m_textureID;
    
    Health      m_health;
    
    int         m_numFrames         = 1;
    int         m_speed             = 50;
    //int         m_hp                = 1;
    //int         m_max_hp            = 1;
    int         m_drawIndex         = 0;
    int         m_spriteType        = OTHER;
    int         m_spriteState       = DEFAULT;
    int         m_previousState     = DEFAULT;
    
    int         m_spriteID          = 0;
    
    bool        m_spawnProjectile   = false;
    bool        m_hasAppeared       = false;
    bool        m_isDying           = false;
    bool        m_isFiring          = false;
    bool        m_outOfBounds       = false;
    bool        m_delete            = false;
    bool        isHostile_          = false;
    bool        hasSpawned_         = false;
    
  public:
    Sprite( ObjectData objectData );
    virtual ~Sprite(){}
  
    virtual void update ();
    virtual void render ();
    virtual void clean  ();
    
    void  setSpriteID( int spriteID ) {
      m_spriteID = spriteID;
    }
    int   getSpriteID()     { return m_spriteID; }
    
    bool  spawnProjectile() { return m_spawnProjectile; }
    void  setSpawnProjectile( bool spawnProjectile ) {
      m_spawnProjectile = spawnProjectile;
    }
    void  reduceHp( int attackAmount ) { m_health.reduceHp( attackAmount ); }
    
    void  setIsDying()      { m_isDying = true; }
    bool  isFiring()        { return m_isFiring; }
    bool  hasSpawned()      { return hasSpawned_; }
    bool  hasAppeared()     { return m_hasAppeared; }
    bool  isDying()         { return m_isDying; }
    bool  isHostile()       { return isHostile_; }
    bool  needsDeleting()   { return m_delete; }
    int   getDrawIndex()    { return m_drawIndex; }
    int   getBottomY()      { return m_bottomY; }
    int   getSpriteType()   { return m_spriteType; }
    Position getPosition()  { return m_position; }
};

#endif //SPRITE_HPP

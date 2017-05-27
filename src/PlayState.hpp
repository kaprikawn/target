#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <vector>
#include <map>
#include "SDL.h"
#include "GameState.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Target.hpp"
#include "Enemy.hpp"
#include "Structs.hpp"
#include "Collision.hpp"

class PlayState : public GameState {
  private:
    static const std::string  s_playID;
    
    std::vector<ObjectData> enemies_;
    
    Player* player;
    Target* target;
    
    Collision myCollision_;
    std::vector<std::pair<Sprite*, Sprite*>> collisions_;
    
    Uint32 levelStart       = SDL_GetTicks();
    int framesSinceLastFire = 0;
    
    std::map<int, int> src; // map of draw indexes so we know which order to draw
    std::multimap<int, int> dst;
    
    Sprite* spriteHit = nullptr;
    
  public:
    
    
    virtual bool onEnter();
    virtual void update();
    virtual void render();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
    
    void  add( Sprite* sprite );
    void  remove( int spriteID );
    int   getNewSpriteID() { return nextSpriteID++; }
    
    bool loadLevelFromFile( int currentLevel );
    
};



#endif //PLAYSTATE_HPP

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
//#include <memory>
#include "SDLHeader.hpp"
#include "Sprite.hpp"

class GameState {
  protected:
    GameState() {}
    
    std::vector <Sprite*> sprites_;
    
    //std::vector<std::unique_ptr<Sprite>> sprites;
    
    int spritesSize   = 0;
    int nextSpriteID  = 0;
    
    Uint32 previousTime;
    Uint32 currentTime;
    //float  dt = 0.0;
    
  public:
    virtual ~GameState() {}
    
    virtual bool onEnter() = 0;
    virtual void update () = 0;
    virtual void render () = 0;
    virtual bool onExit () = 0;
    virtual std::string getStateID() const = 0;
};

#endif //GAMESTATE_HPP

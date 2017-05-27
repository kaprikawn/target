#ifndef GAMESTATEMACHINE_HPP
#define GAMESTATEMACHINE_HPP

#include <vector>
#include "GameState.hpp"

class GameStateMachine {
  private:
    std::vector<GameState*> m_gameStates;
    
  public:
    void pushState  ( GameState* pState );
    void changeState( GameState* pState );
    void popState   ();
    
    void update     ();
    void render     ();
    
    std::string     getCurrentGameStateID();
};

#endif //GAMESTATEMACHINE_HPP

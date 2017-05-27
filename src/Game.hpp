#ifndef GAME_HPP
#define GAME_HPP

#include "TextureManager.hpp"
#include "GameStateMachine.hpp"

class Game {
  
  private:
    SDL_Window*       m_pWindow;
    SDL_Renderer*     m_pRenderer;
    float             m_dt;
    
    bool              running;
    static Game*      s_pInstance;
    
    GameStateMachine* m_pGameStateMachine;
    
    Game(){}
  public:
    ~Game(){}
    
    bool init( const char* title, int xpos, int ypos, int width, int height, int flags );
    
    void render       ();
    void update       ();
    void handleEvents ();
    void clean        ();
    void quit         ();
    
    int getCurrentLevel() { return 1; }
    bool gameRunning() { return running; }
    
    void setDeltaTime( Uint32 previousTime, Uint32 currentTime ) {
      m_dt = currentTime - previousTime;
      m_dt /= 1000;
    }
    float getDeltaTime() { return m_dt; }
    
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    
    static Game* Instance() {
      if( s_pInstance == 0 ) {
        s_pInstance = new Game();
        return s_pInstance;
      }
      return s_pInstance;
    }
};

typedef Game TheGame;

#endif //GAME_HPP

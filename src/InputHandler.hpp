#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <vector>
#include "SDLHeader.hpp"




class InputHandler {
  private:
    
    // keyboard
    const Uint8*  m_keystates = SDL_GetKeyboardState( NULL );
    void          onKeyDown();
    void          onKeyUp();
    bool          m_gamepadsInitialised = false;
    
    // gamepad
    bool  m_bJoysticksInitialised = false;
    int   whichOne;
    Uint8 currentHat = 0;
    void  onHatMotion( SDL_Event &event );
    
    std::vector<SDL_Joystick*>  m_joysticks;
    std::vector<bool>           m_buttonStates;

    InputHandler  (){}
    ~InputHandler (){}
    static InputHandler* s_pInstance;
  
  public:
    
    // gamepad
    void initialiseJoysticks();
    bool joysticksInitialised() { return m_bJoysticksInitialised; }
    bool getButtonState( int buttonNumber ) { return m_buttonStates[buttonNumber]; }
    
    // keyboard
    bool isKeyDown( SDL_Scancode key );
    
    bool isPressed( int button );
    
    void update();
    void clean();
    
    static InputHandler* Instance() {
      if( s_pInstance == 0 ) {
        s_pInstance = new InputHandler();
      }
      return s_pInstance;
    }
};

typedef InputHandler TheInputHandler;

#endif //INPUTHANDLER_HPP

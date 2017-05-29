#include <iostream>
#include <vector>
#include "InputHandler.hpp"
#include "Game.hpp"

InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::initialiseJoysticks() {
  if( SDL_WasInit( SDL_INIT_JOYSTICK ) == 0 ) {
    SDL_InitSubSystem( SDL_INIT_JOYSTICK );
  }
  
  if( SDL_NumJoysticks() > 0 ) {
    for( int i = 0; i < SDL_NumJoysticks(); i++ ) {
      SDL_Joystick* joy = SDL_JoystickOpen( i );
      if( joy == NULL ) {
        std::cout << SDL_GetError() << std::endl;
      } else {
        m_joysticks.push_back( joy );
        //m_joystickValues.push_back( std::make_pair( new Vector2D( 0, 0 ), new Vector2D( 0, 0 ) ) );
        for( int b = 0; b < SDL_JoystickNumButtons( joy ); b++ ) {
          m_buttonStates.push_back( false );
        }
      }
    }
    
    SDL_JoystickEventState( SDL_ENABLE );
    m_bJoysticksInitialised = true;
  } else {
    m_bJoysticksInitialised = false;
  }
  std::cout << "Initialised " << m_joysticks.size()  << " joystick(s)" << std::endl;
}

void InputHandler::onKeyDown() {
  m_keystates = SDL_GetKeyboardState( NULL );
  
  if( m_keystates[ SDL_SCANCODE_ESCAPE ] == 1 ) {
    TheGame::Instance() -> quit();
  }
}

void InputHandler::onKeyUp() {
  m_keystates = SDL_GetKeyboardState( NULL );
}

bool InputHandler::isKeyDown( SDL_Scancode key ) {
  if( m_keystates != 0 ) {
    if( m_keystates[key] == 1 ) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

bool InputHandler::isPressed( int button ) {
  if( button == 0 ) {
    if( m_keystates[ SDL_SCANCODE_RIGHT ] == 1 || currentHat == SDL_HAT_RIGHT || currentHat == SDL_HAT_RIGHTUP || currentHat == SDL_HAT_RIGHTDOWN ) {
      return true;
    }
  } else if( button == 1 ) {
    if( m_keystates[ SDL_SCANCODE_LEFT ] == 1 || currentHat == SDL_HAT_LEFT || currentHat == SDL_HAT_LEFTUP || currentHat == SDL_HAT_LEFTDOWN ) {
      return true;
    }
  } else if( button == 2 ) {
    if( m_keystates[ SDL_SCANCODE_UP ] == 1 || currentHat == SDL_HAT_UP || currentHat == SDL_HAT_LEFTUP || currentHat == SDL_HAT_RIGHTUP ) {
      return true;
    }
  } else if( button == 3 ) {
    if( m_keystates[ SDL_SCANCODE_DOWN ] == 1 || currentHat == SDL_HAT_DOWN || currentHat == SDL_HAT_LEFTDOWN || currentHat == SDL_HAT_RIGHTDOWN ) {
      return true;
    }
  } else if( button == 4 ) { // fire
    if( m_keystates[ SDL_SCANCODE_Z ] == 1 ) {
      return true;
    }
    if( m_gamepadsInitialised ) {
      if( m_buttonStates[ 2 ] ) {
        return true;
      }
    }
  } else if( button == 5 ) { // roll
    if( m_keystates[ SDL_SCANCODE_X ] == 1 ) {
      return true;
    }
  } else if( button == 6 ) { // bomb
    if( m_keystates[ SDL_SCANCODE_C ] == 1 ) {
      return true;
    }
  } else if( button == 7 ) { // start
    if( m_keystates[ SDL_SCANCODE_S ] == 1 ) {
      return true;
    }
  } else if( button == 8 ) { // quit
    if( m_keystates[ SDL_SCANCODE_Q ] == 1 ) {
      return true;
    }
  } else if( button == 9 ) { // ok
    if( m_keystates[ SDL_SCANCODE_O ] == 1 ) {
      return true;
    }
  } else if( button == 10 ) { // back
    if( m_keystates[ SDL_SCANCODE_BACKSPACE ] == 1 ) {
      return true;
    }
  }
  
  return false;
}

void InputHandler::onHatMotion( SDL_Event &event ) {
  
  if( !m_bJoysticksInitialised ) {
    return;
  }
  
  for( int i = 0; i < m_joysticks.size(); i++ ) {
    currentHat = SDL_JoystickGetHat( m_joysticks[i], 0 );
  }
}

void InputHandler::update() {
  SDL_Event event;
  while( SDL_PollEvent( &event ) ) {
    switch( event.type ) {
      case SDL_QUIT:
        TheGame::Instance() -> quit(); break;
      case SDL_KEYDOWN:
        onKeyDown(); break;
      case SDL_KEYUP:
        onKeyUp(); break;
      case SDL_JOYHATMOTION:
        onHatMotion( event ); break;
      case SDL_JOYBUTTONDOWN:
        whichOne = event.jaxis.which;
        m_buttonStates[ event.jbutton.button ] = true;
        //printf( "%d pressed\n", event.jbutton.button );
        break;
      case SDL_JOYBUTTONUP:
        whichOne = event.jaxis.which;
        m_buttonStates[ event.jbutton.button ] = false;
        break;
      default:
        break;
    }
  }
}

void InputHandler::clean() {
  if( m_gamepadsInitialised ) {
    for( unsigned int i = 0; i < SDL_NumJoysticks(); i++ ) {
      SDL_JoystickClose( m_joysticks[i] );
    }
  }
}

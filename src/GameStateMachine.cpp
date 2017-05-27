#include <iostream>
#include "GameStateMachine.hpp"

void GameStateMachine::pushState( GameState *pState ) {
  m_gameStates.push_back( pState );
  m_gameStates.back() -> onEnter();
}

void GameStateMachine::popState() {
  if( !m_gameStates.empty() ) {
    if( m_gameStates.back() -> onExit() ) {
      delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }
}

std::string GameStateMachine::getCurrentGameStateID() {
  if( !m_gameStates.empty() ) {
    return m_gameStates.back() -> getStateID();
  }
  return NULL;
}

void GameStateMachine::changeState( GameState *pState ) {
  std::cout << "Changing game state to " << pState -> getStateID() << std::endl;
  if( !m_gameStates.empty() ) {
    if( m_gameStates.back() -> getStateID() == pState -> getStateID() ) {
      return;
    }
    if( m_gameStates.back() -> onExit() ) {
      //delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }
  
  //std::cout << "pushing gamestate into array" << std::endl;
  // push back out new state
  m_gameStates.push_back( pState );
  
  // initialise it
  m_gameStates.back() -> onEnter();
  
  std::cout << "finished changing state - stateID is now " << m_gameStates.back() -> getStateID() << std::endl;
}

void GameStateMachine::update() {
  if( !m_gameStates.empty() ) {
    //cout << "GameStateMachine::update - StateID is " << m_gameStates.back() -> getStateID() << endl;
    m_gameStates.back() -> update();
  }
}

void GameStateMachine::render() {
  if( !m_gameStates.empty() ) {
    m_gameStates.back() -> render();
  }
}


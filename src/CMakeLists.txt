ADD_EXECUTABLE( game 
  TextureManager.cpp InputHandler.cpp JsonLoader.cpp 
  Position.cpp 
  Animation.cpp Sprite.cpp Player.cpp Enemy.cpp Target.cpp Scenary.cpp Projectile.cpp 
  GameStateMachine.cpp PlayState.cpp Collision.cpp 
  Game.cpp Main.cpp )


target_link_libraries(hellocmake ${SDL2_LIBRARY})
install(TARGETS game RUNTIME DESTINATION ${BIN_DIR})


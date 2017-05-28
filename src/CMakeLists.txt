CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
 
PROJECT(target)
 
ADD_EXECUTABLE(game 
  TextureManager.cpp InputHandler.cpp JsonLoader.cpp 
  Position.cpp 
  Animation.cpp Sprite.cpp Player.cpp Enemy.cpp Target.cpp Scenary.cpp Projectile.cpp 
  GameStateMachine.cpp PlayState.cpp Collision.cpp 
  Game.cpp Main.cpp
)
 
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(game ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})


set_property(TARGET game PROPERTY CXX_STANDARD 11)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )

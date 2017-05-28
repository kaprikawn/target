#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <vector>

struct Path {
  int x;
  int y;
  Path( int p_x, int p_y ) : x( p_x ), y( p_y ) {}
};

enum buttons {
    RIGHT = 0
  , LEFT  = 1
  , UP    = 2
  , DOWN  = 3
  , FIRE  = 4
  , ROLL  = 5
  , BOMB  = 6
  , START = 7
  , QUIT  = 8
  , OK    = 9
  , BACK  = 10
};

struct stateDataValues {
  std::string id    = "NULLID";
  int   spriteState;
  int   minFrame        = 0;
  int   maxFrame        = 0;
  int   currentRow      = 1;
  int   frameDelay      = 1;
  bool  oscillate       = false;
  bool  fixedAnimation  = false;
};

struct AnimationData {
  int   currentRow      = 1;
  int   minFrame        = 0;
  int   maxFrame        = 0;
  int   frameDelay      = 1000;
  int   swapFrameAfter  = 1000;
  int   swapAnimAfter   = 1000;
  bool  oscillate       = false;
  
};

struct StateData {
  int   spriteState;
  std::string id    = "NULLID";
  bool  fixedAnim   = false;
  std::vector<AnimationData> animData;
};

struct  ObjectData {
  int   width;
  int   height;
  int   x;
  int   y;
  int   hb_left_adjust    = 0;
  int   hb_right_adjust   = 0;
  int   hb_top_adjust     = 0;
  int   hb_bottom_adjust  = 0;
  int   spawnTime         = 0;
  int   speed             = 1;
  int   hp                = 1;
  int   animDataIndex     = 0;
  bool  hasSpawned        = false;
  
  std::string   objectType;
  std::string   textureID;
  std::string   filename;
  std::string   name = "noname";
  
  std::vector<StateData>  stateData;
  std::vector<Path>       pathData;
};

struct Hitbox {
  int left;
  int right;
  int top;
  int bottom;
};

enum lastDirection {
  DIR_LEFT, DIR_RIGHT
};

enum spriteTypes {
  PLAYER, TARGET, PROJECTILE, ENEMY, SCENARY, OTHER
};

enum spriteStates {
    DEFAULT   = 0
  , MOVING    = 1
  , FIRING    = 2
  , DYING     = 3
  , DODGING   = 4
  , DYING1    = 5
  , DYING2    = 6
  , DYING3    = 7
  , DYING4    = 8
  , DAMAGED1  = 9
  , DAMAGED2  = 10
  , DAMAGED3  = 11
  , DODGE1    = 12
  , DODGE2    = 13
  , DODGE3    = 14
};

enum ProjectileTypes {
    BULLET, GRENADE
};

#endif //STRUCTS_HPP

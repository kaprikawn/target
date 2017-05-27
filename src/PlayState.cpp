#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

//#include <stdlib.h>
#include <time.h>
#include "json.hpp"

#include "PlayState.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "Vector2D.hpp"
#include "Projectile.hpp"
#include "Scenary.hpp"
#include "JsonLoader.hpp"

const std::string PlayState::s_playID = "PLAY";

void PlayState::add( Sprite* sprite ) {
  
  sprite -> setSpriteID( getNewSpriteID() );
  
  sprites_.push_back( std::move( sprite ) );
  spritesSize = sprites_.size();
  
  //std::cout << "spawning spriteID " << sprite -> getSpriteID() << std::endl;
}

bool PlayState::onEnter() {

  JsonLoader testJsonLoader;
  std::vector<ObjectData> objectData = testJsonLoader.getObjectData( "assets/dataTest.json" );
  for( int i = 0; i < objectData.size(); i++ ) {
    if( objectData[i].objectType == "Player" ) {
      player = new Player( objectData[i] );
      PlayState::add( player );
    } else if( objectData[i].objectType == "Target" ) {
      target = new Target( objectData[i] );
      PlayState::add( target );
    }
    TheTextureManager::Instance() -> load( objectData[i].filename, objectData[i].textureID, TheGame::Instance() -> getRenderer() );
  }
  
  TheTextureManager::Instance() -> load( "assets/grass.png", "background", TheGame::Instance() -> getRenderer() );
  
  PlayState::loadLevelFromFile( 1 );
  
  spritesSize   = sprites_.size();
  levelStart    = SDL_GetTicks();
  previousTime  = levelStart;
  
  std::cout << "entering PlayState" << std::endl;
  return true;
}

bool PlayState::loadLevelFromFile( int currentLevel ) {
  
  std::vector<std::string> loadedTextures;
  bool textureLoaded = false;
  std::string currentLevelChar = std::to_string( currentLevel );
  
  JsonLoader newJsonLoader;
  std::vector<ObjectData> objectData = newJsonLoader.getObjectData( "assets/dataLevel1.json" );
  for( int i = 0; i < objectData.size(); i++ ) {
    if( objectData[i].objectType == "Scenary" ) {
      Scenary* newScenary = new Scenary( objectData[i] );
      PlayState::add( newScenary );
    } else if( objectData[i].objectType == "Enemy" ) {
      //ObjectData* newEnemyObjectData = new ObjectData( objectData[i] );
      //newEnemyObjectData = objectData[i];
      enemies_.push_back( objectData[i] );
      //printf( "x is now %d\n", enemies_[0].pathData[0].x );
      //Enemy* newEnemy = new Enemy( objectData[i] );
      //PlayState::add( newEnemy );
    }
    
    textureLoaded = false;
    if( !loadedTextures.empty() ) {
      for( int t = 0; t < loadedTextures.size(); t++ ) {
        if( loadedTextures[t] == objectData[i].textureID ) {
          textureLoaded = true;
        }
      }
    }
    
    if( !textureLoaded ) {
      if( !TheTextureManager::Instance() -> load( objectData[i].filename, objectData[i].textureID, TheGame::Instance() -> getRenderer() ) ) {
        return false;
      }
      loadedTextures.push_back( objectData[i].textureID );
    }
  }
  
  if( !TheTextureManager::Instance() -> load( "assets/projectile.png", "grenade", TheGame::Instance() -> getRenderer() ) ) {
    return false;
  }
  
  return true;
}

void PlayState::update() {
  if( spritesSize == 0 ) { return; }
  
  for( int i = 0; i < spritesSize; i++ ) {
    sprites_[i] -> update();
  }
  
  previousTime = currentTime;
  currentTime = SDL_GetTicks();
  TheGame::Instance() -> setDeltaTime( previousTime, currentTime );
  
  //delete dead stuff
  for( unsigned i = spritesSize; i-- > 0; ) {
    if( sprites_[i] -> needsDeleting() ) {
      //printf( "deleting %d\n", i );
      delete sprites_[i];
      sprites_.erase( sprites_.begin() + i );
    }
  }
  spritesSize = sprites_.size();
  
  collisions_ = myCollision_.getCollisions( sprites_, spritesSize );
  //std::vector<std::pair<Sprite*, Sprite*> > collisions_
  
  spriteHit = nullptr;
  
  if( !collisions_.empty() ) {
    for( int c = 0; c < collisions_.size(); c++ ) {
      //std::cout << collisions_[c].first -> getSpriteID() << " has collided with " << collisions_[c].second -> getSpriteID() << std::endl;
      
      int id1 = collisions_[c].first  -> getSpriteID();
      int id2 = collisions_[c].second -> getSpriteID();
      
      if( id1 == 1 && id2 > 1 ) { // target hitting enemy / scenary
        if( target -> isFiring() ) {
          if( spriteHit ) {
            if( spriteHit -> getBottomY() < sprites_[id2] -> getBottomY() ) {
              spriteHit = sprites_[id2];
            }
          } else {
            spriteHit = sprites_[id2];
          }
        }
      }
    }
  }
  
  if( spriteHit ) {
    //printf( "hit sprite\n" );
    spriteHit -> reduceHp( 15 );
  }
  
  // spawn enemies
  if( !enemies_.empty() ) {
    for( unsigned i = enemies_.size(); i-- > 0; ) {
      if( currentTime > ( levelStart + ( enemies_[i].spawnTime * 1000 ) ) ) {
        
        Enemy* newEnemy = new Enemy( enemies_[i] );
        PlayState::add( newEnemy );
        enemies_.erase ( enemies_.begin() + i );
      }
    }
  }
  
  // spawn projectiles
  if( spritesSize > 1 ) {
    for( int i = 2; i < spritesSize; i++ ) {
      if( sprites_[i] -> spawnProjectile() && !sprites_[i] -> isDying() ) {
        printf( "spawn projectile\n" );
        
        ObjectData projectileData;
        projectileData.width  = 23;
        projectileData.height = 23;
        projectileData.x      = sprites_[i] -> getPosition().getX();
        projectileData.y      = sprites_[i] -> getPosition().getY();
        projectileData.objectType = "projectile";
        projectileData.textureID = "grenade";
        projectileData.filename = "assets/projectile.png";
        projectileData.name = "proj";
        
        StateData newStateData;
        newStateData.id = "DEFAULT";
        newStateData.spriteState = 0;
        
        AnimationData newAnimationData;
        newAnimationData.maxFrame = 1;
        /*newAnimationData.currentRow = 1;
        newAnimationData.minFrame = 0;
        
        newAnimationData.swapFrameAfter = 100000;*/
        
        newStateData.animData.push_back( newAnimationData );
        
        projectileData.stateData.push_back( newStateData );
        
        Projectile* newProjectile = new Projectile( projectileData, sprites_[0] -> getPosition(). getSpriteCenter().getX(), "grenade" );
        PlayState::add( newProjectile );
        
        sprites_[i] -> setSpawnProjectile( false );
      }
    }
  }
  
  return;
  /*
  // spawn enemies
  for( int i = 0; i < enemies.size(); i++ ) {
    if( !enemies[i].hasSpawned ) {
      if( currentTime > ( levelStart + ( enemies[i].spawnTime * 1000 ) ) ) {
        Sprite* enemy = new Enemy ( enemies[i] );
        //sprites.push_back( enemy );
        PlayState::add( enemy );
        enemies[i].hasSpawned = true;
      }
    }
  }
  
  // check to see if any projectiles have hit the scenary
    if( sprites[i] -> getSpriteType() == PROJECTILE && !sprites[i] -> isDying() ) {
      for( int p = 2; p < spritesSize; p++ ) {
        if( sprites[p] -> getSpriteType() == SCENARY && !sprites[p] -> isDying() ) {
          if( spritesCollided( sprites[p], sprites[i] ) ) {
            sprites[p] -> reduceHp( 250 );
            sprites[i] -> reduceHp( 250 );
            
          }
        }
      }
    }
    
    if( sprites[i] -> spawnProjectile() && !sprites[i] -> isDying() ) {
      //spawn projectile from enemy
      
      int x = sprites[i] -> getSpriteCenter().getX();
      int y = sprites[i] -> getSpriteCenter().getY();
      int destinationX = player -> getSpriteCenter().getX();
      int destinationY = player -> getSpriteCenter().getY();
      
      Projectile* newProjectile = new Projectile( x, y, destinationX, destinationY, 300, false, true, false );
      PlayState::add( newProjectile );
      
      sprites[i] -> setSpawnProjectile( false );
    }
    
    if( i > 1 && sprites[i] -> isHostile() && ! sprites[i] -> isDying() ) { // check to see if hit player
      if( spritesCollided( sprites[0], sprites[i] ) ) {
        //printf( "Enemy hit player\n" );
        sprites[0] -> reduceHp( 1 );
        sprites[i] -> reduceHp( 1 );
        //sprites[0] -> setIsDying();
      }
    }
  }
  
  if( spriteHit ) {
    spriteHit -> reduceHp( 15 );
  }
  
  
  
  //if( target -> isFiring() && int( ( ( SDL_GetTicks() / 100 ) % 8 ) ) == 0 ) {
  if( target -> isFiring() && framesSinceLastFire > 10 ) {
  
    Projectile* newProjectile = new Projectile( player -> getSpriteCenter().getX(), player -> getSpriteCenter().getY(), target -> getSpriteCenter().getX(), target -> getSpriteCenter().getY(), 3000, true, false, true );
    
    PlayState::add( newProjectile );
    
    framesSinceLastFire = 0;
    
  }
  framesSinceLastFire++;
  
  previousTime = currentTime;
  currentTime = SDL_GetTicks();
  TheGame::Instance() -> setDeltaTime( previousTime, currentTime );
  
  for( int i = 0; i < spritesSize; i++ ) {
    sprites[i] -> update();
  }
  */
}

template<typename A, typename B> std::pair<B,A> flip_pair( const std::pair<A,B> &p) {
  return std::pair<B,A>( p.second, p.first );
}

template<typename A, typename B> std::multimap<B,A> flip_map(const std::map<A,B> &src) {
  std::multimap<B,A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                 flip_pair<A,B>);
  return dst;
}

void PlayState::render() {
  if( spritesSize == 0 ) { return; }
  
  TheTextureManager::Instance() -> draw( "background", 0, 0, 1280, 720, TheGame::Instance() -> getRenderer() );
  
  //  cpp.sh/7pky
  std::map<int, int> src; // map of draw indexes so we know which order to draw
  
  
  
  for( int i = 0; i < spritesSize; i++ ) { // populate map
    src[i] = sprites_[i] -> getDrawIndex();
    //sprites[i] -> render();
  }
  //return;
  
  src[0] = 1001;
  src[1] = 1000;
  
  dst = flip_map( src ); // order by value
  
  for ( std::multimap<int, int>::iterator it=dst.begin(); it!=dst.end(); ++it ) {
    //std::cout << (*it).first << " => " << (*it).second << '\n';
    //int nextPosition = (*it).second;
    //std::cout << "print next = " << nextPosition << std::endl;
    sprites_[ (*it).second ] -> render();
  }
  
  src.clear();
  dst.clear();
  
  
  
  for( unsigned i = spritesSize; i-- > 0; ) {
    sprites_[i] -> render();
  }
}



bool PlayState::onExit() {
  
  
  std::cout << "exiting PlayState" << std::endl;
  return true;
}



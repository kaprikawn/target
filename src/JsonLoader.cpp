#include <iostream>
#include <fstream>
#include "JsonLoader.hpp"
#include "json.hpp"

std::vector<ObjectData> JsonLoader::getObjectData( std::string filename ) {
  std::ifstream fin( filename, std::ifstream::binary );
  nlohmann::json j;
  fin >> j;
  
  for( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
    nlohmann::json o = *it;
    
    ObjectData newObjectData;
    
    newObjectData.objectType        = o[ "properties" ][ "objectType" ];
    newObjectData.height            = o[ "properties" ][ "height" ];
    newObjectData.width             = o[ "properties" ][ "width" ];
    newObjectData.x                 = o[ "properties" ][ "x" ];
    newObjectData.y                 = o[ "properties" ][ "y" ];
    newObjectData.hb_left_adjust    = o[ "properties" ][ "hb_left_adjust" ];
    newObjectData.hb_right_adjust   = o[ "properties" ][ "hb_right_adjust" ];
    newObjectData.hb_top_adjust     = o[ "properties" ][ "hb_top_adjust" ];
    newObjectData.hb_bottom_adjust  = o[ "properties" ][ "hb_bottom_adjust" ];
    newObjectData.textureID         = o[ "properties" ][ "textureID" ];
    newObjectData.filename          = o[ "properties" ][ "filename" ];
    newObjectData.hp                = o[ "properties" ][ "hp" ];
    newObjectData.spawnTime         = o[ "properties" ][ "spawnTime" ];
    
    nlohmann::json sdRoot           = o[ "stateData" ];
    
    for( nlohmann::json::iterator sd1 = sdRoot.begin(); sd1 != sdRoot.end(); ++sd1 ) {
      nlohmann::json sd = *sd1;
      
      StateData newStateData;
      
      newStateData.spriteState   = sd[ "spriteState" ];
      
      if( !sd[ "skip" ] ) {
        newStateData.id         = sd[ "id" ];
        newStateData.fixedAnim  = sd[ "fixedAnim" ];
        nlohmann::json aRoot    = sd[ "animation" ];
        
        for( nlohmann::json::iterator a1 = aRoot.begin(); a1 != aRoot.end(); ++a1 ) {
          nlohmann::json a = *a1;
          AnimationData newAnimationData;
          
          newAnimationData.minFrame       = a[ "minFrame" ];
          newAnimationData.maxFrame       = a[ "maxFrame" ];
          newAnimationData.currentRow     = a[ "currentRow" ];
          newAnimationData.frameDelay     = a[ "frameDelay" ];
          newAnimationData.swapFrameAfter = a[ "swapFrameAfter" ];
          newAnimationData.swapAnimAfter  = a[ "swapAnimAfter" ];
          newAnimationData.oscillate      = a[ "oscillate" ];
          
          
          newStateData.animData.push_back( newAnimationData );
          //printf( "pushing back anim data\n" );
        }
      }
      newObjectData.stateData.push_back( newStateData );
      
    }
    
    if( newObjectData.objectType == "Enemy" ) {
      nlohmann::json pathRoot = o[ "pathData" ];
      for( nlohmann::json::iterator pd1 = pathRoot.begin(); pd1 != pathRoot.end(); ++pd1 ) {
        nlohmann::json pd = *pd1;
        Path newPathData( pd[ "x" ], pd[ "y" ] );
        newObjectData.pathData.push_back( newPathData );
      }
    }
    
    returnData.push_back( newObjectData );
  }
  
  return returnData;
}

/*

void JsonLoader::loadJson( std::string filename ) {
  
  std::ifstream fin( filename, std::ifstream::binary );
  nlohmann::json j;
  fin >> j;
  
  //nlohmann::json objectsJ = j;
  for( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
  
    nlohmann::json o = *it;
    
    //std::cout << "objectType is " << o[ "properties" ]["objectType"] << '\n';
    jsonValues newJsonValues;
    
    std::vector<DestinationPoint> coordinates;
    
    newJsonValues.objectType        = o[ "properties" ][ "objectType" ];
    newJsonValues.height            = o[ "properties" ][ "height" ];
    newJsonValues.width             = o[ "properties" ][ "width" ];
    newJsonValues.x                 = o[ "properties" ][ "x" ];
    newJsonValues.y                 = o[ "properties" ][ "y" ];
    newJsonValues.hb_left_adjust    = o[ "properties" ][ "hb_left_adjust" ];
    newJsonValues.hb_right_adjust   = o[ "properties" ][ "hb_right_adjust" ];
    newJsonValues.hb_top_adjust     = o[ "properties" ][ "hb_top_adjust" ];
    newJsonValues.hb_bottom_adjust  = o[ "properties" ][ "hb_bottom_adjust" ];
    newJsonValues.textureID         = o[ "properties" ][ "textureID" ];
    newJsonValues.filename          = o[ "properties" ][ "filename" ];
    
    nlohmann::json sdRoot = o[ "stateData" ];
    
    //std::cout << "here...objectType is " << newJsonValues.objectType << '\n';
    
    for( nlohmann::json::iterator sdp = sdRoot.begin(); sdp != sdRoot.end(); ++sdp ) {
      //std::cout << "id is " << o["stateData"]["id"] << std::endl;
      nlohmann::json sd = *sdp;
      //std::cout << "id is " << sd["id"] << std::endl;
      //std::cout << "printing pointer..." << *it2 << '\n';
      
      stateDataValues newStateDataValues;
      newStateDataValues.spriteState  = sd[ "spriteState" ];
      
      if( !sd[ "skip" ] ) {
        newStateDataValues.id           = sd[ "id" ];
        newStateDataValues.minFrame     = sd[ "minFrame" ];
        newStateDataValues.maxFrame     = sd[ "maxFrame" ];
        newStateDataValues.currentRow   = sd[ "currentRow" ];
        newStateDataValues.frameDelay   = sd[ "frameDelay" ];
        newStateDataValues.oscillate    = sd[ "oscillate" ];
        
        
      }
      
      if( newJsonValues.objectType == "Scenary1" ) {
        std::cout << "id is " << sd["id"] << std::endl;
        std::cout << "spriteState is " << sd["spriteState"] << std::endl;
        std::cout << "minFrame is " << sd["minFrame"] << std::endl;
        std::cout << "maxFrame is " << sd["maxFrame"] << std::endl;
        std::cout << "currentRow is " << sd["currentRow"] << std::endl;
        std::cout << "frameDelay is " << sd["frameDelay"] << std::endl;
        std::cout << "oscillate is " << sd["oscillate"] << std::endl;
        
      }
      
      newJsonValues.valuesStateData.push_back( newStateDataValues );
    }
    
    if( newJsonValues.objectType == "Enemy" ) {
      newJsonValues.spawnTime = o[ "properties" ][ "spawnTime" ];
      newJsonValues.speed     = o[ "properties" ][ "speed" ];
      newJsonValues.hp        = o[ "properties" ][ "hp" ];
      
      nlohmann::json coordsRoot = o[ "coordinates" ];
      for( nlohmann::json::iterator cp = coordsRoot.begin(); cp != coordsRoot.end(); ++cp ) {
        nlohmann::json coordData = *cp;
        
        newJsonValues.coordValues.push_back( DestinationPoint( coordData[ "x" ], coordData[ "y" ] ) );
        
      }
      
    }
    
    jsonObjects.push_back( newJsonValues );
  }
  
  
}*/

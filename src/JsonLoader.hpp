#ifndef JSONLOADER_HPP
#define JSONLOADER_HPP

#include <vector>
#include <string>
#include "Structs.hpp"

class JsonLoader {
  
  private:
    std::vector<ObjectData> returnData;
  
  public:
    void loadJson( std::string filename );
    std::vector<ObjectData> getObjectData( std::string filename );
    
};

#endif //JSONLOADER_HPP

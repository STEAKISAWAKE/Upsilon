
#ifndef __UPSILON_GAME_WORLD_H__
#define __UPSILON_GAME_WORLD_H__

#include <string>

#include "json.h"

class Game;

class World
{

// Constructors
public:
    World();
    World(std::string worldName);


// Variables
public:
    Game* game;

// Methods
public:
    void LoadWorld(nlohmann::json worldJson);


// Variables
private:
    


// Methods
private:


};

#endif // __UPSILON_GAME_WORLD_H__

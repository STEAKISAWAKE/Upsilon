#ifndef __UPSILON_GAME_GAME_H__
#define __UPSILON_GAME_GAME_H__

#include <string>
#include <vector>

class World;

class Game
{

// Constructors
public:


// Variables
public:


// Methods
public:
    World* LoadWorld(std::string worldName); // Loads a world from the maps folder
    void ChangeWorld(World* loadedWorld); // Changes the rendered and updated map


// Variables
private:
    std::vector<World*> worlds;


// Methods
private:


};

#endif // __UPSILON_GAME_GAME_H__
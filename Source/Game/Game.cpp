#include "Game.h"

#include "World.h"

World* Game::LoadWorld(std::string worldName)
{
    World* world = new World();

    nlohmann::json worldJson;

    world->LoadWorld(worldJson);

    worlds.push_back(world);
    return world;
}
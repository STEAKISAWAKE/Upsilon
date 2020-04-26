#include "World.h"

// Constructors

// Methods

void World::LoadWorld(nlohmann::json worldJson)
{
    // Get all required variables from json to cpp
    nlohmann::json actorsJson = worldJson["Actors"];

    
    // Loop over actors and spawn them
    for(nlohmann::json actorJson : actorsJson)
    {
        std::string actorType = actorJson["ActorType"];
        std::string actorName = actorJson["ActorName"];
    }


}
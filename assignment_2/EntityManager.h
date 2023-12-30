#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <map> // Include for std::map
#include "Entity.h"

// Alias definition for EntityVec
using EntityVec = std::vector<std::shared_ptr<Entity>>;

// Assuming EntityMap is an alias for std::map with string keys and EntityVec values
using EntityMap = std::map<std::string, EntityVec>;

class EntityManager {
public:
    EntityManager();
    void init();
    void update();

    std::shared_ptr<Entity> addEntity(const std::string & tag);

    const EntityVec & getEntities();
    const EntityVec & getEntities(const std::string & tag);
    
private:
    EntityVec   m_entities;
    EntityVec   m_entitiesToAdd;
    EntityMap   m_entityMap;
    size_t      m_totalEntities = 0;

    void removeDeadEntities(EntityVec & vec);
};

#endif

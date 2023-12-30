#include "EntityManager.h"
#include "Entity.h" // Include the header file where Entity is defined


EntityManager::EntityManager()
{

}



void EntityManager::update() {
    //TO do add entities from m_entitiesToAdd the proper locations
    //add to vector of all entities
    //add them to the vector insid ethe map, with the tag as a key

    //remove dead
    removeDeadEntities(m_entities);

    //remove dead for each vector in the entity map

    for (auto& [tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
    auto entity = std::make_shared<Entity>(m_totalEntities++, tag); // Creating shared_ptr directly

    //m_entitiesToAdd.push_back(entity);

    return entity;
}


const EntityVec & EntityManager::getEntities()
{
    return m_entities;
}


const EntityVec & EntityManager::getEntities(const std::string & tag)
{
    //TODO
    return m_entities;
}

void EntityManager::init() {
    // Implementation of init function
}

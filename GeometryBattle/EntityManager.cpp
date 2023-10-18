#include "EntityManager.h"

void EntityManager::update()
{
	for (const auto& el : m_toAdd)
	{
		m_entities.push_back(el);
	}

	for (const auto& el : m_toAdd)
	{
		m_entityMap[el->tag()].push_back(el);
	}
	m_toAdd.clear(); 
    
	removeDeadEntities(m_entities);

	for (auto &e : m_entityMap)
	{
		removeDeadEntities(e.second);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities));
	m_toAdd.push_back(entity); 
	m_totalEntities++;
	return entity; 
}


EntityVec& EntityManager::getEntities()
{
	return m_entities; 
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag]; 
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	auto it = std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity> e) {return !e->isAlive(); });
	vec.erase(it, vec.end()); 
}

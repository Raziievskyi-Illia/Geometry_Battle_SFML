#pragma once
#include "Entity.h"


typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map < std::string, EntityVec> EntityMap; 



class EntityManager
{
	EntityVec m_entities; 
	EntityVec m_toAdd; 
	EntityMap m_entityMap; 
	size_t m_totalEntities = 0; 
	
public:
	EntityManager() = default; 
	void update(); 
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	EntityVec& getEntities(); 
	EntityVec& getEntities(const std::string& tag); 
	void removeDeadEntities(EntityVec& vec); 
};

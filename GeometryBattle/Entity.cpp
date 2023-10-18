#include "Entity.h"

const size_t Entity::id() const
{
	return this->m_id; 
}

const std::string Entity::tag() const
{
	return this->m_tag; 
}

bool Entity::isAlive()
{
	return this->m_alive; 
}

void Entity::destroy()
{
	this->m_alive = false; 
}

Entity::Entity(const std::string tag, const size_t id)
{
	m_id = id; 
	m_tag = tag; 
}
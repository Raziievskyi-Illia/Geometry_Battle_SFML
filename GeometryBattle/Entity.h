#pragma once
#include "Components.h"
#include <memory>


class Entity
{
private:
	size_t m_id = 0; 
	bool m_alive = true; 
	std::string m_tag; 
	Entity(const std::string tag, const size_t id);
	friend class EntityManager;
public:
	std::shared_ptr<CTransform> CTransform = nullptr; 
	std::shared_ptr<CCollision> CCollision = nullptr; 
	std::shared_ptr<CShape> CShape = nullptr; 
	std::shared_ptr<CScore> CScore = nullptr; 
	std::shared_ptr<CLifespan> CLifespan = nullptr; 
	std::shared_ptr<CInput> CInput = nullptr; 

	bool isAlive(); 
	const size_t id() const;
	const std::string tag() const;
	void destroy(); 
};
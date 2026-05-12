#include "Entity.h"
#include <iostream>


Entity::Entity(std::string name, std::string description ,Entity* owner = nullptr)
{
	m_name = name;
	m_description = description;
	m_owner = owner;

	if (m_owner != nullptr) 
	{
		m_owner->m_contains.emplace_back(this);
	}
}

Entity::~Entity()
{
}

void Entity::Look()
{
	std::cout << m_name << ": ";
	std::cout << m_description << " \n";
}

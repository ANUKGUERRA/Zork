#pragma once
#include <string>
#include <vector>

enum class Types 
{
	Room,
	Npc,
	Item,
	Exit,
	Player
};
class Entity
{
public:
	Entity(std::string name, std::string description, Entity* owner);
	~Entity();
	virtual void Look();

	inline bool CompareName(std::string& name) 
	{
		return name == m_name;
	}


	Types type;
	std::string m_name;
	std::string m_description;
	Entity* m_owner;
	std::vector<Entity*> m_contains;
};


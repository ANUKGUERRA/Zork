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
		if (name.length() != m_name.length())
			return false;

		for (int i = 0; i < name.length(); ++i) {
			if (tolower(m_name[i]) != tolower(name[i]))
				return false;
		}

		return true;
	}


	Types type;
	std::string m_name;
	std::string m_description;
	Entity* m_owner;
	std::vector<Entity*> m_contains;
};


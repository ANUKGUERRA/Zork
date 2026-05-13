#include "NPC.h"
#include <iostream>

NPC::NPC(std::string name, std::string description, Entity* owner, Entity* key, int storageCapacity, bool isLocked)
	: Container(name, description, owner, storageCapacity, isLocked, key)
{
    type = Types::Npc;
}

NPC::~NPC()
{
}


void NPC::Look()
{
	Entity::Look();

	if (IsContainer())
	{
		if (!m_contains.empty())
		{
			std::cout << "- Has:\n";
			for (Entity* item : m_contains)
			{
				if (item == nullptr)
					continue;

				std::cout << "  - " << item->m_name << "\n";
			}
		}
	}
}
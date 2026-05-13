#include "Item.h"
#include <iostream>

Item::Item(std::string name, std::string description, Entity* owner, Entity* key, int storageCapacity, bool isLocked)
	: Container(name, description, owner, storageCapacity, isLocked, key)
{
	type = Types::Item;
}

Item::~Item()
{
}

void Item::Look()
{
	Entity::Look();

	if (IsContainer()) 
	{
		if (IsLocked())
			std::cout << "- Status: Locked\n";
		else
			std::cout << "- Status: Unlocked\n";

		if (!IsLocked())
		{
			std::cout << "- Capacity: " << m_contains.size() << "/" << m_storageCapacity << "\n";

			if (m_contains.empty())
			{
				std::cout << "  (empty)\n";
			}
			else
			{
				std::cout << "- Items inside:\n";
				for (Entity* item : m_contains)
				{
					if (item == nullptr)
						continue;

					std::cout << "  - " << item->m_name << "\n";
				}
			}
		}
	}
}

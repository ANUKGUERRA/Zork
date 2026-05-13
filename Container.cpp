#include "Container.h"

#include "Container.h"

Container::Container(std::string name, std::string description, Entity* owner, int storageCapacity, bool isLocked, Entity* key)
    : Entity(name, description, owner), m_key(key), m_storageCapacity(storageCapacity), m_isLocked(isLocked)
{
}

Container::~Container()
{
}
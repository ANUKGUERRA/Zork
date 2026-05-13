#pragma once
#include "Entity.h"

class Container : public Entity
{
public:
    Container(std::string name, std::string description, Entity* owner, int storageCapacity = 0, bool isLocked = false, Entity* key = nullptr);
    virtual ~Container();

    inline bool IsContainer() const { return m_storageCapacity > 0; }
    inline bool IsLocked()    const { return m_isLocked; }
    inline bool IsFull()      const { return (int)m_contains.size() >= m_storageCapacity; }
    inline void Unlock() { m_isLocked = false; }
    inline void Lock() { m_isLocked = true; }

    Entity* m_key;
    int     m_storageCapacity;
    bool    m_isLocked;
};


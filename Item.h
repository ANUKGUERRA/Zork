#pragma once
#include "Container.h"

class Item : public Container
{
public:
    Item(std::string name, std::string description, Entity* owner, 
        Entity* key = nullptr, int storageCapacity = 0, bool isLocked = false);

    ~Item();

    void Look() override;
};


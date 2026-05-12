#pragma once
#include "Entity.h"


class Room : public Entity
{
public:
    Room(std::string name, std::string description);
    ~Room();

    void Look() override;
};



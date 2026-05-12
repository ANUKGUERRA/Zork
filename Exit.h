#pragma once
#include "Entity.h"
class Exit : public Entity
{
public:
    Exit(std::string originDirectionName, std::string destinationDirectionName, std::string description, Entity* o, Entity* d);
    ~Exit();

    Entity* m_origin;
    Entity* m_destination;


    std::string GetDirectionFrom(Entity* room) const;

    Entity* GetDestinationFrom(Entity* room) const;

    std::string m_originDirectionName;
    std::string m_destinationDirectionName;

};


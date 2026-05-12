#include "Exit.h"

Exit::Exit(std::string originDirectionName, std::string destinationDirectionName, std::string description, Entity* o, Entity* d)
    : Entity("", description, nullptr), m_origin(o), m_destination(d)
{
    type = Types::Exit;

    m_originDirectionName = originDirectionName;
    m_destinationDirectionName = destinationDirectionName;
    m_origin->m_contains.emplace_back(this);
    m_destination->m_contains.emplace_back(this);
}

Exit::~Exit()
{
}

std::string Exit::GetDirectionFrom(Entity* room) const
{
    if (room == m_origin)      return m_originDirectionName;
    if (room == m_destination) return m_destinationDirectionName;
    return "";
}

Entity* Exit::GetDestinationFrom(Entity* room) const
{
    if (room == m_origin)      return m_destination;
    if (room == m_destination) return m_origin;
    return nullptr;
}

#include "Room.h"
#include "Exit.h"
#include <iostream>

Room::Room(std::string name, std::string description)
    : Entity(name, description, nullptr)
{
    type = Types::Room;
}

Room::~Room()
{
}

void Room::Look()
{
    std::cout << "\n[ " << m_name << " ]\n";
    std::cout << m_description << "\n";

    // Exits
    std::cout << "\nExits: \n";
    bool anyExit = false;
    for (Entity* e : m_contains)
    {
        if (e->type == Types::Exit)
        {
            Exit* exit = static_cast<Exit*>(e);
            std::string dir = exit->GetDirectionFrom(this);
            std::string place = exit->GetDestinationFrom(this)->m_name;
            if (!dir.empty())
            {
                std::cout << dir << " leads to " << place << std::endl;
                anyExit = true;
            }
        }
    }
    if (!anyExit) std::cout << "none";
    std::cout << "\n";

    // Items / NPCs
    bool anyItem = false;
    for (Entity* e : m_contains)
    {
        if (e->type == Types::Item || e->type == Types::Npc)
        {
            if (!anyItem) 
            { 
                std::cout << "\nYou see: \n"; 
                anyItem = true; 
            }
            e->Look();
        }
    }
    if (anyItem) std::cout << "\n";

    std::cout << "\n";
}
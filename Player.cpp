#include "Player.h"
#include "Exit.h"
#include "Item.h"
#include <iostream>
#include <algorithm>

Player::Player(std::string name, std::string description, Entity* owner)
    : Entity(name, description, owner)
{
    type = Types::Player;
}

Player::~Player()
{
}


//Helpers
bool Player::HandsUsed() const
{
    int count = 0;
    for (Entity* e : m_contains)
        if (e->type == Types::Item) ++count;
    return count > 1;
}

static Item* FindItemIn(Entity* container, const std::string& name)
{
    for (Entity* e : container->m_contains)
        if (e->type == Types::Item && e->CompareName(const_cast<std::string&>(name)))
            return static_cast<Item*>(e);
    return nullptr;
}

static void TransferItem(Entity* entity, Entity* from, Entity* to)
{
    from->m_contains.erase(
        std::remove(from->m_contains.begin(), from->m_contains.end(), entity),
        from->m_contains.end());
    to->m_contains.emplace_back(entity);
    entity->m_owner = to;
}



bool Player::Look(const std::string& parameter)
{
    if (parameter.empty())
    {
        m_owner->Look();
        return true;
    }

    for (Entity* e : m_owner->m_contains)
    {
        if (e->type == Types::Exit) 
        {
            Exit* exit = static_cast<Exit*>(e);

            if (exit->GetDirectionFrom(m_owner) == const_cast<std::string&>(parameter)) 
            {
                std::cout << "\n" << exit->GetDestinationFrom(m_owner)->m_name << ": " << exit->GetDestinationFrom(m_owner)->m_description << "\n\n";
                return true;
            }
        }
    }

    for (Entity* e : m_contains)
    {
        if (e->type != Types::Room && e->CompareName(const_cast<std::string&>(parameter)))
        {
            std::cout << "\n" << e->m_name << ": " << e->m_description << "\n\n";
            return true;
        }
    }

    std::cout << "You don't see any \"" << parameter << "\" here.\n";
    return false;
}

bool Player::Go(const std::string& direction)
{
    if (direction.empty())
    {
        std::cout << "Go where?\n";
        return false;
    }

    for (Entity* e : m_owner->m_contains)
    {
        if (e->type != Types::Exit) continue;

        Exit* exit = static_cast<Exit*>(e);
        std::string dir = exit->GetDirectionFrom(m_owner);

        if (dir != direction) continue;

        Entity* newRoom = exit->GetDestinationFrom(m_owner);
        if (!newRoom)
        {
            std::cout << "That exit leads nowhere.\n";
            return false;
        }

        Entity* oldRoom = m_owner;
        oldRoom->m_contains.erase(
            std::remove(oldRoom->m_contains.begin(), oldRoom->m_contains.end(), this),
            oldRoom->m_contains.end()
        );

        m_contains.erase(
            std::remove(m_contains.begin(), m_contains.end(), oldRoom),
            m_contains.end()
        );

        m_owner = newRoom;
        newRoom->m_contains.emplace_back(this);
        m_contains.emplace_back(newRoom);

        m_owner->Look();
        return true;
    }

    std::cout << "There's no exit to the \"" << direction << "\" here.\n";
    return false;
}

bool Player::Take(const std::string& parameter)
{
    if (parameter.empty())
    {
        std::cout << "Take what?\n";
        return false;
    }

    if (HandsUsed() >= MAX_HANDS)
    {
        std::cout << "Your hands are full. Drop something first.\n";
        return false;
    }

    return false;
}

bool Player::Talk(const std::string& parameter)
{
    return false;
}

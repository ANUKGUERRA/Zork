#include "World.h"
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
int Player::HandsUsed() const
{
    int count = 0;
    for (Entity* e : m_contains)
        if (e->type == Types::Item) ++count;
    return count;
}

static Item* FindItemIn(Entity* container, const std::string& name)
{
    for (Entity* e : container->m_contains)
        if (e->type == Types::Item && e->CompareName(const_cast<std::string&>(name))) 
        {

            return static_cast<Item*>(e);
        }
    return nullptr;
}

static void TransferItem(Entity* entity, Entity* from, Entity* to)
{
    from->m_contains.erase(std::remove(from->m_contains.begin(), from->m_contains.end(), entity), from->m_contains.end());
    to->m_contains.emplace_back(entity);
    entity->m_owner = to;
}


void Player::CloseContainer()
{
    if (m_openContainer)
    {
        std::cout << "You close the " << m_openContainer->m_name << ".\n";
        m_openContainer->Lock();
        m_openContainer = nullptr;
    }
}


bool Player::Look(const std::string& parameter)
{
    
    if (parameter.empty())
    {
        if (m_openContainer)
        {
            m_openContainer->Look();
            return true;
        }
        m_owner->Look();
        return true;
    }

    if (parameter == "inventory")
    {
        std::cout << "\nInventory:\n";

        for (Entity* e : m_contains) 
            if (e->type == Types::Item) e->Look();

        std::cout << "\n";
        return true;
    }
    if (parameter == "self" || parameter == "me")
    {
        Entity::Look();
        std::cout << "\n";
        return true;
    }

    if (m_openContainer)
    {
        for (Entity* e : m_openContainer->m_contains)
        {
            if (e->CompareName(const_cast<std::string&>(parameter)))
            {
                std::cout << "\n";
                e->Look();
                std::cout << "\n";
                return true;
            }
        }
    }


    for (Entity* e : m_owner->m_contains)
    {
        if (e->type == Types::Exit) 
        {
            Exit* exit = static_cast<Exit*>(e);

            if (exit->GetDirectionFrom(m_owner) == parameter) 
            {
                std::cout << "\n" << exit->GetDestinationFrom(m_owner)->m_name << ": " << exit->GetDestinationFrom(m_owner)->m_description << "\n\n";
                return true;
            }
        }
        
        if (e->CompareName(const_cast<std::string&>(parameter))) 
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
            std::cout << "That exit leads nowhere\n";
            return false;
        }

        CloseContainer();
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

    std::cout << "There's no exit to the \"" << direction << "\" here\n";
    return false;
}

bool Player::Take(const std::string& parameter)
{
    if (parameter.empty())
    {
        std::cout << "Take what?\n";
        return false;
    }


    if (m_openContainer)
    {
        std::cout << m_openContainer->m_name;
        Item* item = FindItemIn(m_openContainer, parameter);
        if (item)
        {
            if (HandsUsed() >= MAX_HANDS)
            {
                std::cout << "Your hands are full. Drop something first\n";
                return false;
            }
            TransferItem(item, m_openContainer, this);
            std::cout << " Gives you the " << item->m_name << "\n";
            return true;
        }
        std::cout << "There's no \"" << parameter << "\" in the "
            << m_openContainer->m_name << "\n";
        return false;
    }


    Item* item = FindItemIn(m_owner, parameter);
    if (item)
    {
        if (HandsUsed() >= MAX_HANDS)
        {
            std::cout << "Your hands are full. Drop something first\n";
            return false;
        }

        TransferItem(item, m_owner, this);
        std::cout << "You pick up the " << item->m_name << "\n";
        return true;
    }
    else
    {
        std::cout << "invalid item to pick: " << parameter << "\n";
    }


    return false;
}

bool Player::Drop(const std::string& parameter)
{
    if (parameter.empty())
    {
        std::cout << "Drop what?\n";
        return false;
    }

    Item* item = FindItemIn(this, parameter);
    if (!item)
    {
        std::cout << "You aren't carrying any \"" << parameter << "\"\n";
        return false;
    }

    if (m_openContainer)
    {
        if (m_openContainer->IsFull())
        {
            std::cout << "The " << m_openContainer->m_name << " is full\n";
            return false;
        }
        TransferItem(item, this, m_openContainer);
        std::cout << "You put the " << item->m_name
            << " in the " << m_openContainer->m_name << "\n";
        return true;
    }


    TransferItem(item, this, m_owner);
    std::cout << "You drop the " << item->m_name << "\n";
    return true;
}


bool Player::Talk(const std::string& parameter)
{


    for (Entity* e : m_owner->m_contains) 
    {
        if (e->type == Types::Npc && e->CompareName(const_cast<std::string&>(parameter)))
        {

            NPC* npc = static_cast<NPC*>(e);

            if (npc->IsContainer())
            {
                Item* matchingKey = nullptr;
                for (Entity* e : m_contains)
                    if (e == npc->m_key) { matchingKey = static_cast<Item*>(e); break; }

                if (matchingKey)
                {
                    std::cout << "Unlocked npc" << std::endl;
                    npc->Unlock();
                    m_openContainer = npc;
                }
            }
            for (auto& pair : npc->conditionalDialogue)
            {
                if (World::GetInstance().HasFlag(pair.first))
                {
                    for (const auto& line : pair.second)
                    {
                        std::cout << npc->m_name << ": " << line << "\n";
                    }
                    return true;
                }
            }


            for (const auto& line : npc->defaultDialogue)
            {
                std::cout << npc->m_name << ": " << line << "\n";
            }
            return true;
        }
    }
    std::cout << "You can't talk to: "<< parameter << "\n";
    return false;
}

bool Player::Open(const std::string& parameter)
{
    if (parameter.empty())
    {
        std::cout << "Open what?\n";
        return false;
    }

    if (m_openContainer)
        CloseContainer();


    Item* container = FindItemIn(m_owner, parameter);

    if (!container) container = FindItemIn(this, parameter);

    if (!container)
    {
        std::cout << "You don't see any \"" << parameter << "\" here.\n";
        return false;
    }


    if (!container->IsContainer())
    {
        std::cout << container->m_name << " it's not something that can be opened"  << "\n";
        return false;
    }

    if (container->IsLocked())
    {
        Item* matchingKey = nullptr;
        for (Entity* e : m_contains)
            if (e == container->m_key) { matchingKey = static_cast<Item*>(e); break; }

        if (!matchingKey)
        {
            std::cout << "The " << container->m_name << " is locked and you don't have the key.\n";
            return false;
        }

        container->Unlock();
        TransferItem(matchingKey, this, m_owner);
        std::cout << "You use the " << matchingKey->m_name
            << " to unlock the " << container->m_name << ".\n";
    }

    m_openContainer = container;

    container->Look();
    return true;
}

bool Player::Close(const std::string& parameter)
{
    CloseContainer();
    Look("");
    return true;
}




#pragma once

#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>

#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "NPC.h"
#include "Item.h"

class World
{
public:
    static World& GetInstance()
    {
        static World instance;
        return instance;
    }

    World(const World&) = delete;
    World& operator=(const World&) = delete;
    World(World&&) = delete;
    World& operator=(World&&) = delete;

    bool HandleInput(const std::vector<std::string>& tokens);

    void AddFlag(const std::string& flag);
    bool HasFlag(const std::string& flag) const;

    bool CheckWinCondition();

    std::unordered_set<std::string> flags;
    bool mysterySolved = false;

private:
    World();
    ~World();

    Player* player;
    std::vector<Entity*> entities;
};
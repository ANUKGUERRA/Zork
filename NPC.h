#pragma once
#include "Container.h"
#include <unordered_map>

class NPC : public Container
{
public:
    NPC(std::string name, std::string description, Entity* owner,
        Entity* key = nullptr, int storageCapacity = 0, bool isLocked = false);
    ~NPC();
    
    void Look() override;

    std::vector<std::string> defaultDialogue;
    std::unordered_map<std::string, std::vector<std::string>> conditionalDialogue;
};
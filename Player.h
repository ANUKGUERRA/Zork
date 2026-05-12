#pragma once
#include "Entity.h"
class Player : public Entity 
{
public:
    Player(std::string name, std::string description, Entity* owner);
	~Player();


    static constexpr int MAX_HANDS = 2;
    bool HandsUsed() const;

    bool Look(const std::string& parameter);
    bool Go(const std::string& parameter);
    bool Take(const std::string& parameter);
    bool Talk(const std::string& parameter);
};


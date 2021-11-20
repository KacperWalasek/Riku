#include "TestMove.h"
#include <iostream>

std::shared_ptr<Patch> TestMove::createPatch(const GameState& state) const
{
    std::cout << "\t test move" << std::endl;
    return std::make_shared<Patch>(PlayerPatch(0));
}

bool TestMove::isDoable(const GameState& state) const
{
    return true;
}

std::shared_ptr<IMove> TestMove::asPointner() const
{
    return std::make_shared<TestMove>();
}
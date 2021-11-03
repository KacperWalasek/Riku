//Kacper Walasek
#pragma once
#include "../Patch/Patch.h"
#include <memory>

class GameState;
class IMove
{
public:	
	virtual std::shared_ptr<Patch> createPatch(const GameState& state) const = 0;
	virtual bool isDoable(const GameState& state) const = 0;
};

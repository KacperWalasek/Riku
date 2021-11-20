// Kacper Walasek

#include "SimpleTileObject.h"

SimpleTileObject::SimpleTileObject(std::string name, const std::map<std::string, sol::function>& hooks) : loadedHookable(hooks), name(name) {}

std::string SimpleTileObject::getName() const
{
	return name;
}

double SimpleTileObject::getModifiedCost(double cost) const
{
	return cost;
}

std::shared_ptr<IMove> SimpleTileObject::onDestroy(bool byOwner)
{
	return loadedHookable.onDestroy(*this,byOwner);
}

std::shared_ptr<IMove> SimpleTileObject::onTurnEnd()
{
	return loadedHookable.onTurnEnd(*this);
}

std::shared_ptr<IMove> SimpleTileObject::onTurnBegin()
{
	return loadedHookable.onTurnBegin(*this);
}

std::shared_ptr<IMove> SimpleTileObject::onBeingPlaced(int mapX, int mapY)
{
	return loadedHookable.onBeingPlaced(*this, mapX, mapY);
}

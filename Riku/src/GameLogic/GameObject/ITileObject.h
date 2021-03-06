// Kacper Walasek

#pragma once
#include "../IAsset.h"
#include "../Tile/TileCost/ICostModifier.h"
#include "../StateUpdate/Move/IMove.h"
#include "../Hooks/IHookable.h"
#include <map>

class GUIDescription;
class ITileObject : public IAsset, public ICostModifier, public IHookable
{
public:
	virtual const GUIDescription& getGuiDescription() = 0;
	virtual std::shared_ptr<IMove> onOptionChosen(int index, int mapX, int mapY) = 0;
};

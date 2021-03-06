#pragma once
#include <memory>
#include <string>
#include "../StateUpdate/Move/IMiniMove.h"
namespace minigame
{
	class IMiniHookable
	{
	public:
		virtual std::string getId() const = 0;
		virtual std::shared_ptr<IMiniMove> onDestroy(bool byOwner) = 0;
		virtual std::shared_ptr<IMiniMove> onTurnEnd() = 0;
		virtual std::shared_ptr<IMiniMove> onTurnBegin() = 0;
		virtual std::shared_ptr<IMiniMove> onBeingPlaced(int mapX, int mapY) = 0;

		virtual int getOwner() const = 0;
	};
}

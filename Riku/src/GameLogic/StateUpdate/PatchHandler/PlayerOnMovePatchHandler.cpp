#include "PlayerOnMovePatchHandler.h"
#include "../../Actions/CombinedAction.h"
#include "../../Actions/SendPatchToAll.h"
#include "../../Actions/ResetCummulatedPatch.h"

std::shared_ptr<IAction> PlayerOnMovePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
	if (patch.playerOnMove >= 0 && patch.playerOnMove < state.players.size())
	{
		state.playerOnMove = patch.playerOnMove;
		return std::make_shared<CombinedAction>(
			std::make_shared<SendPatchToAll>(), 
			std::make_shared<ResetCummulatedPatch>());
	}
	return nullptr;
}

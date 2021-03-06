#include "TranslateMiniUnitMoveHandler.h"
#include "../StateUpdate/Move/TranslateMiniUnit.h"
#include "../../GameLogic/StateUpdate/MoveDescriptions/TranslateUnitMoveDescription.h"

std::shared_ptr<minigame::IMiniMove> minigame::TranslateMiniUnitMoveHandler::handleDescription(const IMoveDescription& description)
{
    const auto& desc = (const TranslateUnitMoveDescription&)description;
    return std::make_shared<TranslateMiniUnit>(desc.getFromX(), desc.getFromY(), desc.getToX(), desc.getToY());
}

bool minigame::TranslateMiniUnitMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "translate_unit";
}

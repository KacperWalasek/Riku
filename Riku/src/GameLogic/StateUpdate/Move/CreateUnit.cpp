#include "CreateUnit.h"
#include "../../Unit/Unit.h"

CreateUnit::CreateUnit(int player, std::string unit, int mapX, int mapY)
    : player(player), name(unit), mapX(mapX), mapY(mapY)
{}
CreateUnit::CreateUnit(std::string unit, int mapX, int mapY)
    : player(-1), name(unit), mapX(mapX), mapY(mapY)
{}

std::shared_ptr<Patch> CreateUnit::createPatch(const GameState& state, const LogicAssets& assets) const
{
    int player = this->player < 0 ? state.playerOnMove : this->player;
    auto it = assets.units.find(name);
    if (it == assets.units.end())
        return nullptr;
    const logic::Asset& asset = it->second;
    int mp = asset.getByKey("movement_points").asNumber();
    auto& funcs = asset.getFunctions();
    auto unitPtr = std::make_shared<Unit>(asset.getType(), name, player, mp, funcs);
    auto hookMove = unitPtr->onBeingPlaced(mapX, mapY);
    auto hookPatch = hookMove ? *(hookMove->createPatch(state, assets)) : Patch();
    return std::make_shared<Patch>(PlayerPatch(player, unitPtr) + (Patch)TilePatch({mapX,mapY}, unitPtr) + (Patch)RegisterHookablePatch(unitPtr) + hookPatch);
}

bool CreateUnit::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return mapX>=0 && mapY>=0 && mapX<state.map.size() && mapY<state.map[0].size() && !state.map[mapX][mapY].unit;
}

std::shared_ptr<IMove> CreateUnit::asPointner() const
{
    return std::make_shared<CreateUnit>(player, name, mapX, mapY);
}

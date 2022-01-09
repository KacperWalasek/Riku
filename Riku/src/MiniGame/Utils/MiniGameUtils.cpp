#include "MiniGameUtils.h"

int minigame::MiniCostEvaluator::h(vertex from, vertex to)
{
    return sqrt(pow((to.x - from.x), 2) + pow((to.y - from.y), 2));
}

int minigame::MiniCostEvaluator::d(vertex vert)
{
    return 1;
}

std::map<std::string, std::shared_ptr<minigame::IMiniHookable>> minigame::MiniGameUtils::hookables;
Path minigame::MiniGameUtils::getShortestPath(const MiniGameState& state, int fromX, int fromY, int toX, int toY)
{
    MiniCostEvaluator evaluator;
    return ShortestPathEvaluator::getShortestPath(evaluator, state.map.size(), state.map[0].size(), fromX, fromY, toX, toY);
}

void minigame::MiniGameUtils::addHookable(std::shared_ptr<IMiniHookable> hookable)
{
    hookables.emplace(hookable->getId(), hookable);
}

void minigame::MiniGameUtils::removeHookable(std::string id)
{
    hookables.erase(id);
}

std::shared_ptr<minigame::IMiniHookable> minigame::MiniGameUtils::getHookable(std::string id)
{
    return hookables[id];
}

void minigame::MiniGameUtils::clearHookables()
{
    hookables.clear();
}
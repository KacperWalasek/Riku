#include "MiniMapRequestHandler.h"
#include "../Responses/MiniMapResponse.h"
MiniMapRequestHandler::MiniMapRequestHandler(const MiniGameState& state)
    : state(state) {}

std::shared_ptr<Response> MiniMapRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<MiniMapResponse>(request, state.map);
}

bool MiniMapRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "mini_map";
}

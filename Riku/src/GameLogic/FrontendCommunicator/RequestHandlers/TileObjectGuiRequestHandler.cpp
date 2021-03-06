#include "TileObjectGuiRequestHandler.h"
#include "../Requests/TileRequest.h"
#include "../../Hooks/GUIDescription.h"
#include "../Responses/GUIResponse.h"

TileObjectGuiRequestHandler::TileObjectGuiRequestHandler(const GameState& state)
    : state(state)
{}

std::shared_ptr<Response> TileObjectGuiRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::shared_ptr<TileRequest> tileRequest = std::static_pointer_cast<TileRequest>(request);
    std::shared_ptr<ITileObject> object = state.map[tileRequest->getMapX()][tileRequest->getMapY()].object;
    if (!object)
        return std::make_shared<Response>(request, false);
    return std::make_shared<GUIResponse>(request, object->getGuiDescription().getOptions(), object->getGuiDescription().getHeaders());
}

bool TileObjectGuiRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "tile_object_gui";
}

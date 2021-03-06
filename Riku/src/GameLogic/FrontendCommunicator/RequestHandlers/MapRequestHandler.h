//Kacper Walasek
#pragma once
#include "IRequestHandler.h"
#include <vector>
#include "../../Tile/Tile.h"

class MapRequestHandler : public IRequestHandler
{
	const std::vector<std::vector<Tile>>& map;
public:
	MapRequestHandler(const std::vector<std::vector<Tile>>& map) :map(map) {}
	virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
	virtual bool canHandle(const Request& request) const override;
};


#pragma once
#include "IMove.h"
#include <string>
class Load :
    public IMove
{
    std::string path;
public:
    Load(std::string path);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};


#pragma once
#include "IMove.h"
#include <string>
#include "../Patch/Patch.h"
class Load :
    public IMove
{
    Patch patch;
public:
    Load(Patch patch);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};


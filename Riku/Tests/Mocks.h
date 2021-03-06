#pragma once
#include "../src/GameLogic/Unit/Unit.h"
#include "gmock/gmock.h"

std::map<std::string, sol::function> hooks;

class MockUnit : public Unit
{
public:
	MockUnit() : Unit("t", "n", 0, 100, std::vector<std::string>(), hooks) {}
};

class MockTileObject : public ITileObject 
{
public:
	MOCK_METHOD(std::string, getName, (), (const, override));
	MOCK_METHOD(double, getModifiedCost, (double), (const, override));
	MOCK_METHOD((std::shared_ptr<IMove>), onDestroy, (bool), (override));
	MOCK_METHOD((std::shared_ptr<IMove>), onTurnEnd, (), (override));
	MOCK_METHOD((std::shared_ptr<IMove>), onTurnBegin, (), (override));
	MOCK_METHOD((std::shared_ptr<IMove>), onBeingPlaced, (int,int), (override));
	MOCK_METHOD(bool, canBeBuilt, ((const GameState&), int, int), (override));
	MOCK_METHOD((const GUIDescription&), getGuiDescription, (), (override));
	MOCK_METHOD((std::shared_ptr<IMove>), onOptionChosen, (int,int,int), (override));
	MOCK_METHOD(int, getOwner, (), (const, override));
	MOCK_METHOD(std::string, getId, (), (const, override));
	MOCK_METHOD(std::shared_ptr<IMove>, onBeingCreated, (), (override));

	void DelegateToFake() {
		ON_CALL(*this, getId).WillByDefault([this]() {
			return "id";
			});
	}
};

class MockHookable : public IHookable
{
public:
	MOCK_METHOD((std::shared_ptr<IMove>), onDestroy, (bool), (override));
	MOCK_METHOD((std::shared_ptr<IMove>), onTurnEnd, (), (override));
	MOCK_METHOD((std::shared_ptr<IMove>), onTurnBegin, (), (override));
	MOCK_METHOD((std::shared_ptr<IMove>), onBeingPlaced, (int, int), (override));
	MOCK_METHOD(bool, canBeBuilt, ((const GameState&), int, int), (override));
	MOCK_METHOD(int, getOwner, (), (const, override));
	MOCK_METHOD(std::string, getId, (), (const, override));
	MOCK_METHOD((std::shared_ptr<IMove>), onBeingCreated, (), (override));

	void DelegateToFake() {
		ON_CALL(*this, getId).WillByDefault([this]() {
			return "id";
			});
	}
};
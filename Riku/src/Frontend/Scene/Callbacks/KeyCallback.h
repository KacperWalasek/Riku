#pragma once
#define _USE_MATH_DEFINES 
#include <GLFW\glfw3.h>
#include "../../Object.h"
#include "../../Config.h"

namespace front {
	class KeyCallback
	{
		FrontendState& state;
		int& focusedUnitIndex;
		CEGUI::GUI*& activeGUI;
	public:
		KeyCallback(FrontendState& state, int& focusedUnitIndex, CEGUI::GUI*& activeGUI)
			: state(state), focusedUnitIndex(focusedUnitIndex), activeGUI(activeGUI)
		{}

		void operator()(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE)
				;
			if (action == GLFW_PRESS)
			{
				if (activeGUI->on_key_press(key)) return;
				auto& map = state.getMap();
				const auto& units = state.getUnits();
				const Unit* unit = nullptr;
				if (focusedUnitIndex >= 0 && focusedUnitIndex < units.size())
					unit = units[focusedUnitIndex].get();

				std::optional<std::pair<int, int> > unitPos;
				if (unit)
					unitPos = std::make_pair(unit->getMapX(), unit->getMapY());
				//position [front::focusedUnitPosition.first,front::focusedUnitPosition.second];
				switch (key)
				{
				case GLFW_KEY_ESCAPE:
					//glfwSetWindowShouldClose(window, true);
					break;
				case GLFW_KEY_W:
					if (!unit || unitPos->second <= 0)
						break;
					state.moveUnit(unitPos->first, unitPos->second, unitPos->first, unitPos->second - 1);
					break;
				case GLFW_KEY_S:
					if (!unit || unitPos->second >= map[0].size() - 1)
						break;
					state.moveUnit(unitPos->first, unitPos->second, unitPos->first, unitPos->second + 1);
					break;
				case GLFW_KEY_A:
					if (!unit || unitPos->first <= 0)
						break;
					state.moveUnit(unitPos->first, unitPos->second, unitPos->first - 1, unitPos->second);
					break;
				case GLFW_KEY_D:
					if (!unit || unitPos->first >= map.size() - 1)
						break;
					state.moveUnit(unitPos->first, unitPos->second, unitPos->first + 1, unitPos->second);
					break;
				case GLFW_KEY_1: focusedUnitIndex = 0; break;
				case GLFW_KEY_2: focusedUnitIndex = 1; break;
					/*case GLFW_KEY_G:
						front::isGridOn=!front::isGridOn;
						break;*/
				default:
					break;
				}
			}
		}
	};
}


#pragma once

#include "GameStateManager.h"

namespace VNVita
{
	class GameState
	{
	public:
		virtual ~GameState(void) = default;

		virtual void activate(GameStateManager & manager);

		virtual void deactivate(GameStateManager & manager);

		virtual void update(GameStateManager & manager) = 0;

		virtual void render(GameStateManager & manager) = 0;
	};
}
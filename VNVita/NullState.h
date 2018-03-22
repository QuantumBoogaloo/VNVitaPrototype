#pragma once

#include "GameState.h"

namespace VNVita
{
	class NullState : public GameState
	{
	public:
		void activate(GameStateManager & manager) final;

		void deactivate(GameStateManager & manager) final;

		void update(GameStateManager & manager) final;

		void render(GameStateManager & manager) final;
	};
}
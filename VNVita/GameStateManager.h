#pragma once

#include <memory>

namespace VNVita
{
	class GameState;
}

namespace VNVita
{
	class GameStateManager
	{
	private:
		std::shared_ptr<GameState> currentState;
		std::shared_ptr<GameState> nextState;
		bool hasChangePending;

	public:
		virtual ~GameStateManager(void) = default;

		void changeState(std::shared_ptr<GameState> && nextState);

		void changeState(std::shared_ptr<GameState> const & nextState);

		bool hasStateChangePending(void) const;

		void handleStateChange(void);

		void update(void);

		void render(void);
	};
}
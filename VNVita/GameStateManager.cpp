#include "GameStateManager.h"

#include <utility>

#include "GameState.h"

void VNVita::GameStateManager::changeState(std::shared_ptr<GameState> && nextState)
{
	this->nextState = std::move(nextState);
	this->hasChangePending = true;
}

void VNVita::GameStateManager::changeState(std::shared_ptr<GameState> const & nextState)
{
	this->nextState = nextState;
	this->hasChangePending = true;
}

bool VNVita::GameStateManager::hasStateChangePending(void) const
{
	return this->hasChangePending;
}

void VNVita::GameStateManager::handleStateChange(void)
{
	if (this->hasStateChangePending())
	{
		if (this->currentState != nullptr)
			this->currentState->deactivate(*this);

		this->currentState = std::move(this->nextState);

		if (this->currentState != nullptr)
			this->currentState->activate(*this);

		this->hasChangePending = false;
	}
}

void VNVita::GameStateManager::update(void)
{
	if (this->currentState != nullptr)
		this->currentState->update(*this);
}

void VNVita::GameStateManager::render(void)
{
	if (this->currentState != nullptr)
		this->currentState->render(*this);
}
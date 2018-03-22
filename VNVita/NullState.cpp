#include "NullState.h"

void VNVita::NullState::activate(GameStateManager & manager)
{
	(void)manager;
}

void VNVita::NullState::deactivate(GameStateManager & manager)
{
	(void)manager;
}

void VNVita::NullState::update(GameStateManager & manager)
{
	(void)manager;
}

void VNVita::NullState::render(GameStateManager & manager)
{
	(void)manager;
}
#include "Program.h"

/*
Copyright (C) 2018 Pharap (@Pharap)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stdexcept>

#include <SDL2/SDL_image.h>

VNVita::Program::Program(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	auto flags = IMG_Init(IMG_InitFlags::IMG_INIT_PNG);
	if (flags & IMG_InitFlags::IMG_INIT_PNG == 0)
	{
		throw std::exception("Fagets");
	}

	SDL_Window * windowPointer = SDL_CreateWindow("VN Vita", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 544, SDL_WindowFlags(0));

	if (windowPointer == nullptr)
	{
		throw std::runtime_error(SDL_GetError());
	}

	SDL_Renderer * rendererPointer = SDL_CreateRenderer(windowPointer, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);

	if (rendererPointer == nullptr)
	{
		throw std::runtime_error(SDL_GetError());
	}

	this->window = SharedWindow(windowPointer, SDL_DestroyWindow);
	this->renderer = SharedRenderer(rendererPointer, SDL_DestroyRenderer);
}

VNVita::Program::SharedWindow VNVita::Program::getWindow(void)
{
	return this->window;
}

VNVita::Program::SharedRenderer VNVita::Program::getRenderer(void)
{
	return this->renderer;
}

VNVita::Program::SharedConstWindow VNVita::Program::getWindow(void) const
{
	return std::static_pointer_cast<SDL_Window const>(this->window);
}

VNVita::Program::SharedConstRenderer VNVita::Program::getRenderer(void) const
{
	return std::static_pointer_cast<SDL_Renderer const>(this->renderer);
}

bool VNVita::Program::isRunning(void) const
{
	return this->running;
}

void VNVita::Program::run(void)
{
	this->running = true;

	if (SDL_NumJoysticks() > 0)
	{
		this->joystick = SDL_JoystickOpen(0);
	}

	this->surface = IMG_Load("Test.png");
	if (this->surface != nullptr)
	{
		this->texture = SDL_CreateTextureFromSurface(this->renderer.get(), this->surface);
		if (this->texture != nullptr)
		{
			SDL_FreeSurface(this->surface);
			this->surface = nullptr;
		}
	}

	Uint32 frameStart = 0;
	float deltaTime = 0;

	while (this->running)
	{
		deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
		frameStart = SDL_GetTicks();

		this->handleInput();
		this->update();
		this->render();
	}
}

void VNVita::Program::handleInput(void)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EventType::SDL_QUIT:
			this->running = false;
			break;

			// Joystick events
		case SDL_EventType::SDL_JOYAXISMOTION:
			break;
		case SDL_EventType::SDL_JOYBALLMOTION:
			break;
		case SDL_EventType::SDL_JOYHATMOTION:
			break;
		case SDL_EventType::SDL_JOYBUTTONDOWN:
			break;
		case SDL_EventType::SDL_JOYBUTTONUP:
			break;
		case SDL_EventType::SDL_JOYDEVICEADDED:
		{
			if (event.jdevice.which == 0)
				this->joystick = SDL_JoystickOpen(0);
			break;
		}
		case SDL_EventType::SDL_JOYDEVICEREMOVED:
		{
			SDL_JoystickID id = static_cast<SDL_JoystickID>(event.jdevice.which);
			SDL_Joystick * joystick = SDL_JoystickFromInstanceID(id);
			if (this->joystick == joystick)
				this->joystick = nullptr;
			break;
		}
		}
	}
}

void VNVita::Program::update(void)
{

}

void VNVita::Program::render(void)
{
	auto renderer = this->renderer.get();

	SDL_SetRenderDrawColor(renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	if (this->texture != nullptr)
	{
		SDL_RenderCopy(renderer, this->texture, nullptr, nullptr);
	}

	if (this->surface != nullptr)
	{
		SDL_Rect rect = { 100, 100, 16, 16 };

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rect);
	}

	if (this->joystick != nullptr)
	{
		for (int i = 0; i < SDL_JoystickNumButtons(this->joystick); ++i)
		{
			const SDL_Colour activeColour = { 255, 255, 255, SDL_ALPHA_OPAQUE };
			const SDL_Colour inactiveColour = { 127, 127, 127, SDL_ALPHA_OPAQUE };

			SDL_Colour colour = SDL_JoystickGetButton(this->joystick, i) ? activeColour : inactiveColour;

			SDL_SetRenderDrawColor(this->renderer.get(), colour.r, colour.g, colour.b, colour.a);

			SDL_Rect rect = { 8 + ((16 + 8) * i), 8, 16, 16 };

			SDL_RenderFillRect(renderer, &rect);
		}
	}

	SDL_RenderPresent(renderer);
}
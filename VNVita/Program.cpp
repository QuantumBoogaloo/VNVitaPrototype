#include "Program.h"

/*
Copyright (C) 2018 Quantum Boogaloo, Bakagamedev(@bakagamedev), Pharap (@Pharap)

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

VNVita::Program::Program(void)
{
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
		if (event.type == SDL_EventType::SDL_QUIT)
		{
			this->running = false;
		}
	}
}

void VNVita::Program::update(void)
{

}

void VNVita::Program::render(void)
{
	SDL_SetRenderDrawColor(this->renderer.get(), 100, 149, 237, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(this->renderer.get());

	SDL_RenderPresent(this->renderer.get());
}
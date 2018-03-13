#pragma once

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

#include <memory>

#include <SDL2/SDL.h>

namespace VNVita
{
	class Program
	{
	public:
		using SharedWindow = std::shared_ptr<SDL_Window>;
		using SharedRenderer = std::shared_ptr<SDL_Renderer>;
		using SharedConstWindow = std::shared_ptr<SDL_Window const>;
		using SharedConstRenderer = std::shared_ptr<SDL_Renderer const>;

	private:
		SharedWindow window;
		SharedRenderer renderer;
		bool running;

	public:
		Program(void);
		~Program(void) = default;
		Program(Program &&) = delete; // Non-movable
		Program(Program const &) = delete; // Non-copyable

		SharedWindow getWindow(void);
		SharedRenderer getRenderer(void);

		SharedConstWindow getWindow(void) const;
		SharedConstRenderer getRenderer(void) const;

		bool isRunning(void) const;

		void run(void);

		void handleInput(void);
		void update(void);
		void render(void);
	};
}
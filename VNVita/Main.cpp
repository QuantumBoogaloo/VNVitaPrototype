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

#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
	SDL_Window *window = nullptr;

	window = SDL_CreateWindow("VN Vita", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 544, SDL_WindowFlags(0));

	SDL_Renderer *renderer = nullptr;

	renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);

	return 0;
}
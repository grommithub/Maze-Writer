#pragma once

#include <stdexcept>
#include "Constants.h"
#include <iostream>
#include "Constants.h"
#include "Coords.h"

#pragma warning(push)
#include <CodeAnalysis/Warnings.h>
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct SDL_Initializer
{
	SDL_Initializer() noexcept(false)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			throw std::runtime_error(SDL_GetError());
		}
	}
	~SDL_Initializer() noexcept
	{
		try
		{
			std::cout << "Quitting SDL.." << '\n';
		}
		catch (...){}
		SDL_Quit();
	}
	SDL_Initializer(const SDL_Initializer&) = delete;
	SDL_Initializer& operator=(const SDL_Initializer&) = delete;
	SDL_Initializer(SDL_Initializer&&) = delete;
	SDL_Initializer& operator=(SDL_Initializer&&) = delete;
};

class Window
{
	SDL_Window* window = nullptr;
public:
	SDL_Window& get_window() const noexcept
	{
		return *window;
	}
	Window() noexcept(false)
	{
		window = SDL_CreateWindow(WINDOW_NAME.data(), 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WindowFlags::SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			throw(std::runtime_error(SDL_GetError()));
		}
	}
	~Window() noexcept
	{
		try
		{
			std::cout << "Destroying Window.." << '\n';
		}
		catch (...) {}
		SDL_DestroyWindow(window);
	}
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;
};


class Renderer
{
	SDL_Rect render_rect{0,0, SQUARE_SIZE, SQUARE_SIZE};
public:
	SDL_Renderer* renderer;
	void render([[maybe_unused]]const PixelCoords& start, [[maybe_unused]]const PixelCoords& end, const Color& color = PATH_COLOR) noexcept
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(renderer, start.x + PADDING, start.y + PADDING, end.x + PADDING, end.y + PADDING);
		SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
	}

	void render(GridCoords coord, Color color = PATH_COLOR) 
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		render_rect.x = coord.middle_x() + PADDING;
		render_rect.y = coord.middle_y() + PADDING;
		render_rect.w = SQUARE_SIZE / 4;
		render_rect.h = render_rect.w;

		if (FILLED_SQUARE)
		{
			SDL_RenderFillRect(renderer, &render_rect);
		}
		else
		{
			SDL_RenderDrawRect(renderer, &render_rect);
		}
		SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
	}
	void present() const noexcept
	{
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
	//	SDL_RenderClear(renderer);
	}

	Renderer(const Window& window)
	{
		renderer = SDL_CreateRenderer(&window.get_window(), 0, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH/SCALING, SCREEN_HEIGHT/SCALING);
		if (renderer == nullptr)
		{
			throw std::runtime_error(SDL_GetError());
		}
	}
	~Renderer() noexcept
	{
		try
		{
			std::cout << "Destroying Renderer.." << '\n';
		} catch (...){}
		SDL_DestroyRenderer(renderer);
	}
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;
};


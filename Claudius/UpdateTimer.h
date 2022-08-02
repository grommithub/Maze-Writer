#pragma once
#include <SDL.h>
#include "Constants.h"

struct UpdateTimer
{
	float        sec_delta_time = 0.0f;
	unsigned int ms_last_frame = 0;
	unsigned int ms_time_to_wait = 0;

	/*
	Place at the top of game loop
	Place on_frame_complete() at bottom for capped frame rate
	*/
	void wait_for_time_to_update() noexcept
	{
		SDL_Delay(calculate_wait_time());
	}

	unsigned int calculate_wait_time() noexcept
	{
		ms_time_to_wait = SDL_GetTicks() - ms_last_frame + (MS_BETWEEN_FRAMES);
		return ms_time_to_wait;
	}
	float get_seconds_delta_time() const noexcept
	{
		return static_cast<float>(ms_time_to_wait) / 1000.0f;
	}

	/*
	Place at the bottom of game loop
	Place wait_for_time_to_update() at top for capped frame rate
	*/
	void on_frame_complete() noexcept
	{
		ms_last_frame = SDL_GetTicks();
	}
};
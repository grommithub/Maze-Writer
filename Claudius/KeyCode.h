#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL_keycode.h"
#pragma warning (pop)
enum class KeyCode
{
	ESCAPE,SPACE,ENTER,
	A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	LEFT_ARROW,RIGHT_ARROW,UP_ARROW,DOWN_ARROW,
	INVALID
};

constexpr KeyCode TranslateKeyCode(SDL_Keycode code) noexcept
{
	switch (code)
	{
		case SDLK_ESCAPE: return KeyCode::ESCAPE; break;
		case SDLK_SPACE: return KeyCode::SPACE; break;
		case SDLK_RETURN: return KeyCode::ENTER; break;
		case SDLK_RETURN2: return KeyCode::ENTER; break;
		case SDLK_a: return KeyCode::A; break;
		case SDLK_b: return KeyCode::B; break;
		case SDLK_c: return KeyCode::C; break;
		case SDLK_d: return KeyCode::D; break;
		case SDLK_e: return KeyCode::E; break;
		case SDLK_f: return KeyCode::F; break;
		case SDLK_g: return KeyCode::G; break;
		case SDLK_h: return KeyCode::H; break;
		case SDLK_i: return KeyCode::I; break;
		case SDLK_j: return KeyCode::J; break;
		case SDLK_k: return KeyCode::K; break;
		case SDLK_l: return KeyCode::L; break;
		case SDLK_m: return KeyCode::M; break;
		case SDLK_n: return KeyCode::N; break;
		case SDLK_o: return KeyCode::O; break;
		case SDLK_p: return KeyCode::P; break;
		case SDLK_q: return KeyCode::Q; break;
		case SDLK_r: return KeyCode::R; break;
		case SDLK_s: return KeyCode::S; break;
		case SDLK_t: return KeyCode::T; break;
		case SDLK_u: return KeyCode::U; break;
		case SDLK_v: return KeyCode::V; break;
		case SDLK_w: return KeyCode::W; break;
		case SDLK_x: return KeyCode::X; break;
		case SDLK_y: return KeyCode::Y; break;
		case SDLK_z: return KeyCode::Z; break;
		case SDLK_LEFT: return KeyCode::LEFT_ARROW; break;
		case SDLK_RIGHT: return KeyCode::RIGHT_ARROW; break;
		case SDLK_UP: return KeyCode::UP_ARROW; break;
		case SDLK_DOWN: return KeyCode::DOWN_ARROW; break;
		default: return KeyCode::INVALID; break;
	}
}
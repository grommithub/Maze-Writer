#pragma once

#include "Color.h"
#include "string"
#include "Coords.h"
#include <vector>
#include <algorithm>

constexpr std::string_view WINDOW_NAME = "Burt's Maze";
constexpr std::string_view MAZE_TEXT = "Dan Burt:\nProgrammer\ncool guy\n\nYou should\nhire him"; //You should! ;)

constexpr float        TARGET_FPS = 750.0f;
constexpr unsigned int MS_BETWEEN_FRAMES = static_cast<unsigned int>(1000.0f / TARGET_FPS);

constexpr bool RANDOM_GENERATION = true;

constexpr int PADDING = 50;
constexpr int SQUARE_SIZE = 2;
constexpr bool FILLED_SQUARE = true;

constexpr int GRID_TEXT_MARGIN = 5;
constexpr int TEXT_SCALE = 2;

constexpr int FONT_HEIGHT = 7, FONT_WIDTH = 6, KERNING = 1;

constexpr char FONT[][FONT_HEIGHT][FONT_HEIGHT] =
{
	{ "01110", "10001", "10011", "10101", "11001", "10001", "01110", },//0
	{ "00100", "01100", "00100", "00100", "00100", "00100", "01110", },//1
	{ "01110", "10001", "00001", "00010", "00100", "01000", "11111", },//2
	{ "01110", "10001", "00001", "00110", "00001", "10001", "01110", },//3
	{ "00010", "00110", "01010", "10010", "11111", "00010", "00111", },//4
	{ "11111", "10000", "11110", "00001", "00001", "10001", "01110", },//5
	{ "01110", "10001", "10000", "11110", "10001", "10001", "01110", },//6
	{ "11111", "10001", "00010", "00010", "00100", "00100", "00100", },//7
	{ "01110", "10001", "10001", "01110", "10001", "10001", "01110", },//8
	{ "01110", "10001", "10001", "01111", "00001", "00001", "01110", },//9
	{ "00000", "01100", "01100", "00000", "01100", "01100", "00000", },//:
	{ "11111", "11111", "11111", "11111", "11111", "11111", "11111", },//
	{ "11111", "11111", "11111", "11111", "11111", "11111", "11111", },//
	{ "00000", "00000", "11111", "00000", "11111", "00000", "00000", },//=
	{ "11111", "11111", "11111", "11111", "11111", "11111", "11111", },//
	{ "01110", "10001", "10001", "00010", "00100", "00000", "00100", },//?
	{ "11111", "11111", "11111", "11111", "11111", "11111", "11111", },//
	{ "01110", "10001", "10001", "10111", "10001", "10001", "10001", },//A
	{ "11110", "00001", "10001", "11110", "10001", "00001", "11110", },//B
	{ "01110", "10001", "10000", "10000", "10000", "10001", "01110", },//C
	{ "11110", "10001", "10001", "10001", "10001", "00001", "11110", },//D
	{ "11111", "10000", "10000", "11110", "10000", "10000", "11111", },//E
	{ "11111", "10000", "10000", "11110", "10000", "10000", "10000", },//F
	{ "01110", "10001", "10000", "10111", "10001", "10001", "01110", },//G
	{ "10001", "10001", "10001", "11111", "10001", "10001", "10001", },//H
	{ "01110", "00100", "00100", "00100", "00100", "00100", "01110", },//I
	{ "00001", "00001", "00001", "00001", "10001", "10001", "01110", },//J
	{ "10001", "10010", "10100", "11000", "10100", "10010", "10001", },//K
	{ "10000", "10000", "10000", "10000", "10000", "10000", "11111", },//L
	{ "10001", "11011", "10101", "10101", "10001", "10001", "10001", },//M
	{ "10001", "10001", "11001", "10101", "10011", "10001", "10001", },//N
	{ "01110", "10001", "10001", "10001", "10001", "00001", "01110", },//O
	{ "11110", "10001", "10001", "10110", "10000", "10000", "10000", },//P
	{ "01110", "10001", "10001", "10001", "10100", "10010", "01101", },//Q
	{ "11110", "00001", "10001", "11110", "10100", "10010", "10001", },//R
	{ "01111", "10000", "10000", "01110", "00001", "00001", "11110", },//S
	{ "11111", "00100", "00100", "00100", "00100", "00100", "00100", },//T
	{ "10001", "10001", "10001", "10001", "10001", "10001", "01110", },//U
	{ "10001", "10001", "10001", "10001", "10001", "01010", "00100", },//V
	{ "10001", "10001", "10001", "10101", "10101", "10101", "01010", },//W
	{ "10001", "10001", "01010", "00100", "01010", "10001", "10001", },//X
	{ "10001", "10001", "10001", "01010", "00100", "00100", "00100", },//Y
	{ "11111", "00001", "00010", "00100", "01000", "10000", "11111", },//Z
};


constexpr int get_longest_line_length(std::string_view text, std::string_view delimiter = "\n")
{
	int longest = 0;
	std::string_view remainder = text;
	while (remainder.find(delimiter) != std::string::npos)
	{
		int line_length = (int)remainder.find(delimiter);
		longest = std::max(longest, line_length);
		remainder = std::string_view(remainder.begin() + line_length + delimiter.size(), remainder.end());
	}
	longest = std::max(longest, (int)remainder.size());
	return longest;
}

constexpr int GRID_WIDTH = get_longest_line_length(MAZE_TEXT) * FONT_WIDTH * TEXT_SCALE + GRID_TEXT_MARGIN * 2 -2;
constexpr int GRID_HEIGHT = (FONT_HEIGHT + 1) * TEXT_SCALE * (std::count(MAZE_TEXT.begin(), MAZE_TEXT.end(), '\n') + 1) + GRID_TEXT_MARGIN * 2 - 2;

constexpr int SCALING = 3;

constexpr int SCREEN_WIDTH = ((GRID_WIDTH)*SQUARE_SIZE + PADDING * 2) * SCALING;
constexpr int SCREEN_HEIGHT = ((GRID_HEIGHT)*SQUARE_SIZE + PADDING * 2) * SCALING;
constexpr GridCoords MIDDLE_COORDS = { .x = GRID_WIDTH / 2, .y = GRID_HEIGHT / 2 };

constexpr Color BLACK = Color(0, 0, 0, 0);
constexpr Color WHITE = Color(-1, -1, -1, 0);
constexpr Color RED = Color(255, 0, 0, 0);
constexpr Color GREEN = Color(0, 255, 0, 0);
constexpr Color BLUE = Color(0, 0, 255, 0);

constexpr Color HACKER_GREEN = Color(32 * 1.3, 194 * 1.3, 14 * 1.3, 0);
constexpr Color PINK = Color(255, 212, 219, 0);

constexpr Color PATH_COLOR = HACKER_GREEN;
constexpr Color BACKGROUND_COLOR = BLACK;
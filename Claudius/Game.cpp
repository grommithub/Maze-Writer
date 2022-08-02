//Daniel Burt 2022/06/11

#include "Game.h"
#include <algorithm>
#include <iostream>

void Game::run()
{
	while (true)
	{
		timer.wait_for_time_to_update(); //Capping to frame-rate defined in Constants.cpp

		if (!process_user_events()) break;
		update();
		render();

		timer.on_frame_complete();
	}
}

void Game::update()
{
	generate_maze_part();
}

void Game::render() const noexcept
{
	renderer.present();
}

void Game::on_key_down([[maybe_unused]] const KeyCode key) noexcept
{
	if (key == KeyCode::SPACE) setup_maze();
	if (key == KeyCode::ESCAPE)
	{
		setup_maze();
		clear_history();
		SDL_RenderClear(renderer.renderer);
	}
}


Game::MazeCell& Game::get_cell(GridCoords coords) noexcept
{
	return all_cells[coords.x][coords.y];
}

std::vector<std::vector<bool>> Game::GET_BITMAP_CHARACTER(char character)
{
	character = toupper(character) - '0';
	char h[FONT_HEIGHT][FONT_WIDTH] = { "10001", "10001", "10001", "11111", "10001", "10001", "10001", };//H
	std::vector<std::vector<bool>> bits;
	for (unsigned int y = 0; y < FONT_HEIGHT; y++)
	{
		std::vector<bool> line;
		for (unsigned int x = 0; x < FONT_WIDTH; x++)
		{
			line.push_back(FONT[character][y][x] == '1');
		}
		//std::copy(&thing[i], &thing[i] + FONT_WIDTH, line);
		bits.push_back(line);
	}
	return bits;
}

/*
Sets up and allows for the creating of a brand-new maze
*/
void Game::setup_maze()
{
	clear_history();

	SDL_RenderClear(renderer.renderer); // I only do this at the start so I don't need to store each line in RAM :)

	//add_start_and_finish();
	initialize_maze_cells();
	visit_cell(get_cell(GridCoords{ 0,0 }));
}

/*
Sets initial values to the cells in our maze
*/
void Game::initialize_maze_cells()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			all_cells[x][y].location = GridCoords{ x,y };
			all_cells[x][y].visited = false;
		}
	}
	generate_text_layout(MAZE_TEXT);
}

//decides in advance which points should be visited on the maze
//excludes those belonging to letters in the text
void Game::generate_text_layout(const std::string_view& text)
{
	GridCoords text_point{ GRID_TEXT_MARGIN, GRID_TEXT_MARGIN };
	for (auto c : text)
	{
		if (c == ' ')
		{
			text_point.x += FONT_WIDTH * TEXT_SCALE;
			continue;
		}
		if (c == '\n')
		{
			text_point.x = GRID_TEXT_MARGIN;
			text_point.y += (FONT_HEIGHT + 1) * TEXT_SCALE;
			continue;
		}
		else
		{
			auto letter = GET_BITMAP_CHARACTER(c);
			for (int y = 0; y < FONT_HEIGHT * TEXT_SCALE; y++)
			{
				for (int x = 0; x < FONT_WIDTH * TEXT_SCALE; x++)
				{
					all_cells[text_point.x + x][text_point.y + y].visited = letter[y / TEXT_SCALE][x / TEXT_SCALE];
				}
			}
		}
		text_point.x += FONT_WIDTH * TEXT_SCALE;
	}
}

/*
Clears the history of visited cells
Necessary if we start generating a new maze before the last one finished generating
*/
void Game::clear_history()
{
	while (!history.empty())
	{
		history.pop();
	}
}

/*
Adds one path piece the top left and bottom right corners
These pieces consitute the beginning and end of the maze
*/
void Game::add_start_and_finish()
{
	GridCoords start{ 0, -1 }, end{ GRID_WIDTH - 1, GRID_HEIGHT };

	Line l{ start.middle(), GridCoords{ 0,0 }.middle() };
	Line l2{ end.middle(), GridCoords{ GRID_WIDTH - 1,GRID_HEIGHT - 1 }.middle() };

	add_path_segment(l); add_path_segment(l2);
}

/*
Adds single piece to maze
*/
void Game::generate_maze_part()
{
	if (history.empty()) return;
	auto neighbors = get_unvisited_neighbors(current->location);
	if (neighbors.empty())
	{
		while (get_unvisited_neighbors(history.top()->location).empty())
		{
			history.pop();
			if (history.empty()) return;
		}
		visit_cell(*history.top());
	}
	else
	{
		auto next = neighbors[rand() % neighbors.size() * RANDOM_GENERATION]; //random direction
		Line l{ current->location.middle(), next->location.middle() };
		add_path_segment(l);
		visit_cell(*next);
	}

}

/*
Adds visual path to buffer
*/
void Game::add_path_segment(Game::Line& l)
{
	renderer.render(l.start, l.end);
}

//Returns pointers to all unvisited neighbors
std::vector<Game::MazeCell*> Game::get_unvisited_neighbors(GridCoords coords)
{
	std::vector<MazeCell*> neighbors;
	for (int axis = 0; axis < 2; axis++)
	{
		for (int i = -1; i <= 1; i += 2)
		{
			GridCoords c = coords;
			if (axis == 0)
			{
				c.x += i;
			}
			else
			{
				c.y += i;
			}

			if (in_bounds(c) && !get_cell(c).visited)
			{
				neighbors.push_back(&get_cell(c));
			}
		}
	}
	return neighbors;
}

//Verifies that coordinate is within the bounds of the maze
bool Game::in_bounds(GridCoords coords) const noexcept
{
	auto x = coords.x;
	auto y = coords.y;
	return x >= 0 && x < GRID_WIDTH&& y >= 0 && y < GRID_HEIGHT;
}

//Puts our little tracker at a particular cell in the maze
void Game::visit_cell(MazeCell& cell) noexcept
{
	cell.visited = true;
	history.push(&cell);
	current = &cell;
}


/*
	Returns false if user requests quit
	else returns true
*/
inline bool Game::process_user_events() noexcept
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:    return false;
		case SDL_KEYDOWN: on_key_down(TranslateKeyCode(e.key.keysym.sym)); continue;
		default:break;
		}
	}
	return true;
}




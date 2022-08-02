#pragma once
#include <vector>
#include "SDL_Resources.h"
#include "UpdateTimer.h"
#include "KeyCode.h"
#include <chrono>
#include <stack>
#include <vector>
#include <string_view>

class Game
{
	SDL_Initializer init;
	Window window;
	Renderer renderer;
public:

	struct Line
	{
		PixelCoords start, end;
	};

	Game(const std::string_view& word) noexcept : renderer(window)
	{
		srand((unsigned int)time(NULL));

	}

	struct MazeCell
	{
		GridCoords location;
		bool visited{};
	};

	MazeCell* current{};
	MazeCell all_cells[GRID_WIDTH][GRID_HEIGHT];
	std::stack<MazeCell*> history;
	
	void setup_maze();
	void initialize_maze_cells();
	void generate_text_layout(const std::string_view& text);
	void generate_maze_part();
	std::vector<MazeCell*> get_unvisited_neighbors(GridCoords coords);
	void visit_cell(MazeCell& cell) noexcept;
	void add_path_segment(Game::Line& l);

	bool in_bounds(GridCoords coords) const noexcept;
	void clear_history();
	void add_start_and_finish();
	MazeCell& get_cell(GridCoords coords) noexcept;

	std::vector<std::vector<bool>> GET_BITMAP_CHARACTER(char c);

	
	void run();
	void update();
	void render() const noexcept;
	void on_key_down(KeyCode key) noexcept;
	bool process_user_events() noexcept;
	UpdateTimer timer;
	


};



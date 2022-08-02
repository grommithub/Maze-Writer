#include "Game.h"
#include <memory>
#include "Constants.h"
#undef main



int main()
{
	try
	{
		std::unique_ptr<Game> game(new Game(MAZE_TEXT));
		game->run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Fatal Error!\n" << e.what() << std::endl;
		return -1;
	}
	catch (...)
	{
		std::cout << "Unknown Fatal Error!" << std::endl;
		return -1;
	}
	return 0;
}


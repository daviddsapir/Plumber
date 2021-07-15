#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Board.h"

int main()
{
	srand(time(NULL));

	try
	{
		Controller().showScreen();
	}
	catch (std::exception&) {}

	return EXIT_SUCCESS;
}

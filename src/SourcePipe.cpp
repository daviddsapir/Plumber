//--------------------------- Include section  ---------------------------
#include "SourcePipe.h"
#include <array>


//------------------------------ C-tor -----------------------------------
// Uses the constructor of the base class to set the size, texture,
// position, and the index of the pipe.
//------------------------------------------------------------------------
SourcePipe::SourcePipe(sf::Vector2f& size, sf::Vector2f& pos,
	sf::Texture* texture, std::pair<int, int> index)
	: Pipe(std::array<int, NUM_OF_PIPE_ENTRANCES>{0, 0, 0, 1},
		size, pos, texture, index)
{}
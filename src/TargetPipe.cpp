//--------------------------- Include section  ---------------------------
#include "TargetPipe.h"


//------------------------------ C-tor -----------------------------------
// Uses the constructor of the base class to set the size, texture,
// position, and the index of the pipe.
//------------------------------------------------------------------------
TargetPipe::TargetPipe(sf::Vector2f& size, sf::Vector2f& pos,
	sf::Texture* texture, std::pair<int, int> m_index)
	: Pipe(std::array<int, NUM_OF_PIPE_ENTRANCES>{0, 0, 0, 1},
		size, pos, texture, m_index)
{}


//--------------------------- Include section  ---------------------------
#include "I_Pipe.h"
#include "Macros.h"
#include <array>


//------------------------------ C-tor -----------------------------------
// Uses the constructor of the base class to set the size, texture,
// position, and the index of the pipe.
//------------------------------------------------------------------------
I_Pipe::I_Pipe(sf::Vector2f& size, sf::Vector2f& pos,
	sf::Texture* texture, std::pair<int, int> m_index)
	: Pipe(std::array<int, NUM_OF_PIPE_ENTRANCES>{1, 0, 1, 0},
		size, pos, texture, m_index)
{}


// D-tor
I_Pipe::~I_Pipe()
{}


//----------------------------- SetTexture  ------------------------------
// Sets the texture according to the pipes connection status.
// If the pipe is connected it will set the pipe texture with the flow,
// otherwise it will set the texture of the pipe without flow. 
//------------------------------------------------------------------------
void I_Pipe::SetTexture()
{
	if (Pipe::getconStatus())
	{
		Pipe::SetPipeTexture(Resources::instance().
			getPipesObjectTextures(PIPE_I_CON));
	}
	else
	{
		Pipe::SetPipeTexture(Resources::instance().
			getPipesObjectTextures(PIPE_I_NOT_CON));
	}
}

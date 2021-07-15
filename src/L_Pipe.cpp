//--------------------------- Include section  ---------------------------
#include "L_Pipe.h"
#include "Resources.h"
#include <array>


//------------------------------ C-tor -----------------------------------
// Uses the constructor of the base class to set the size, texture,
// position, and the index of the pipe.
//------------------------------------------------------------------------
L_Pipe::L_Pipe(sf::Vector2f& size, sf::Vector2f& pos,
	sf::Texture* texture, std::pair<int, int> index)
	: Pipe(std::array<int, NUM_OF_PIPE_ENTRANCES> {0, 0, 1, 1},
		size, pos, texture, index)
{}


//----------------------------- SetTexture  ------------------------------
// Sets the texture according to the pipes connection status.
// If the pipe is connected it will set the pipe texture with the flow,
// otherwise it will set the texture of the pipe without flow. 
//------------------------------------------------------------------------
void L_Pipe::SetTexture()
{
	if (Pipe::getconStatus())
	{
		Pipe::SetPipeTexture(Resources::instance().
			getPipesObjectTextures(PIPE_L_CON));
	}
	else
	{
		Pipe::SetPipeTexture(Resources::instance().
			getPipesObjectTextures(PIPE_L_NOT_CON));
	}
}

#pragma once
#include "Pipe.h"


//-------------------------- class SourcePipe ----------------------------
class SourcePipe : public Pipe
{
public:

	// C-tor
	SourcePipe(sf::Vector2f&, sf::Vector2f&, sf::Texture*,
		std::pair<int, int>);
};
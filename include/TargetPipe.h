#pragma once

#include "Pipe.h"

//-------------------------- class SourcePipe ----------------------------
class TargetPipe : public Pipe
{
public:

	// C-tor
	TargetPipe(sf::Vector2f&, sf::Vector2f&, sf::Texture*,
		std::pair<int, int>);
};
#pragma once

//--------------------------- Include section  ---------------------------
#include "Pipe.h"

//---------------------------- class L_Pipe ------------------------------
class L_Pipe : public Pipe
{
public:

	// C-tor
	L_Pipe(sf::Vector2f&, sf::Vector2f&, sf::Texture*, std::pair<int, int>);

	// Sets texture according to the pipes connection status.
	virtual void SetTexture();
};
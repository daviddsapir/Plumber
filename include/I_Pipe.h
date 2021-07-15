#pragma once

//--------------------------- Include section  ---------------------------
#include "Pipe.h"
#include <array>
#include "Resources.h"


//---------------------------- class I_Pipe ------------------------------
class I_Pipe : public Pipe
{
public:

	// C-tor
	I_Pipe(sf::Vector2f&, sf::Vector2f&, sf::Texture*, std::pair<int, int>);

	// D-tor
	~I_Pipe();
 
	// Sets texture according to the pipes connection status.
	virtual void SetTexture();
};

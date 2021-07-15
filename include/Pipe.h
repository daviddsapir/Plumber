#pragma once

//--------------------------- Include section  ---------------------------
#include <array>
#include "Macros.h"


//----------------------------- class Pipe -------------------------------
class Pipe
{
public:
	
	// C-tor
	Pipe() = default;

	// C-tor
	Pipe(const std::array<int, 4>&,
		sf::Vector2f& size, sf::Vector2f& pos,
		const sf::Texture* texture, std::pair<int, int>&);
	
	// Virtual D-tor
	virtual ~Pipe();

	// Return the pipe entrances.
	const std::array<int, 4>& getEntrances() const;
	
	// Rotate pipe according to the mouse button click.
	void handleRotation(const std::string&);


	// Rotates the pipe entrances left.
	virtual void rotateLeft();

	// Rotates the pipe entrances right.
	virtual void rotateRight();

	// Draw the pipe upon the window.
	void draw(sf::RenderWindow& window);

	// Handle mouse click button.
	bool handleClickButton(const sf::Vector2f&, const std::string&);

	// Rotate the pipe texture.
	void rotateTexture(const int);

	// Sets the texture of the pipe accodring to the flow.
	void SetPipeTexture(const sf::Texture*);

	// Rotate the pipe randomly.
	void randromRotate();

	// Sets the connection status.
	void setConStatus(bool);

	// Returns the index of the pipe.
	const std::pair<int,int> getIndex() const;

	// Virtual function - Sets texture according
	// to the pipes connection status.
	virtual void SetTexture();

	// Returns the connections status.
	bool getconStatus() const;

	// Returns the obejct textrue.
	const sf::Texture* getTextrue() const;

private:

	// Hold the pipe's shape.
	sf::RectangleShape m_shape;

	// Holds the pipe entrances.
	std::array<int, 4> m_entrances;

	// To know if there is a flow.
	bool m_connected = false;

	// Holds the index of the pipe.
	std::pair<int, int> m_index;
};


enum ENTRANCES {
	LEFT,
	UP,
	RIGHT,
	DOWN
};
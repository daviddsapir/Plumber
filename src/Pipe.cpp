//--------------------------- Include section  ---------------------------
#include "Pipe.h"
#include "Resources.h"
#include "Macros.h"
#include <array>
#include <iostream>


//----------------------------- C-tor -------------------------------
// Intilize the pipe size,position,origin and texture by the data given.
// Also rotated randomly the pipe.
//-------------------------------------------------------------------
Pipe::Pipe(const std::array<int, 4>& entrances, sf::Vector2f& size, 
	sf::Vector2f& pos, const sf::Texture* texture, 
	std::pair<int, int>& index)
	: m_entrances(entrances), m_shape(size), m_index(index)
{
	m_shape.setPosition(pos.x + m_shape.getSize().x / 2,
		pos.y + m_shape.getSize().y / 2);

	m_shape.setOrigin(m_shape.getSize().x / 2,
		m_shape.getSize().y / 2);

	m_shape.setTexture(texture);

	if (texture != Resources::instance().
		getPipesObjectTextures(PIPE_TAR))
	{
		randromRotate();
	}
}

// D-tor
Pipe::~Pipe()
{}


//---------------------------- rotateLeft ---------------------------
// Rotate pipe to the left side.
//-------------------------------------------------------------------
void Pipe::rotateLeft()
{
	int temp = m_entrances[0];

	for (auto i = 0; i < m_entrances.size() - 1; i++)
		m_entrances[i] = m_entrances[double(i) + 1];

	m_entrances[m_entrances.size() - 1] = temp;

	rotateTexture(-ROTATION_ANGLE);
}


//---------------------------- rotateRight --------------------------
// Rotate pipe to the right side.
//-------------------------------------------------------------------
void Pipe::rotateRight()
{
	int temp = m_entrances[m_entrances.size() - 1];

	for (auto i = m_entrances.size() - 1; i > 0; i--)
		m_entrances[i] = m_entrances[double(i) - 1];

	m_entrances[0] = temp;

	rotateTexture(ROTATION_ANGLE);
}


//----------------------------- draw --------------------------------
// Draw the pipe objec upon the window of the game.
//-------------------------------------------------------------------
void Pipe::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}


//------------------------ handleClickButton ------------------------
// Handles the event that the user clicked the pipe.
//-------------------------------------------------------------------
bool Pipe::handleClickButton(const sf::Vector2f& mouseLocation,
	const std::string& mouseButton)
{
	if (m_shape.getGlobalBounds().contains(mouseLocation))
	{
		Resources::instance().ClickedSound(PIPE_CLICK);

		if (m_shape.getTexture() != Resources::instance().
			getPipesObjectTextures(PIPE_TAR))
		{
			handleRotation(mouseButton);
			return true;
		}
	}

	return false;
}


//-------------------------- handleRotation -------------------------
// Rotate pipe according to the mouse button click.
// 
// Right click - rotates pipe to the left.
// Left click - rotates pipe to the right.
//-------------------------------------------------------------------
void Pipe::handleRotation(const std::string& mouseButton)
{
	if (mouseButton == LEFT_BUTTON)
	{
		rotateRight();		// rotates pipe to the left.
	}
	else if (mouseButton == RIGHT_BUTTON)
	{
		rotateLeft();		// rotates pipe to the right.
	}
}


//--------------------------- getIndex ------------------------------
// Returns the index of the pipe.
//-------------------------------------------------------------------
const std::pair<int, int> Pipe::getIndex() const
{
	return m_index;
}


//-------------------------- rotateTexture --------------------------
// Rotate the pipe texture with given angle.
//-------------------------------------------------------------------
void Pipe::rotateTexture(const int angle)
{
	m_shape.rotate(angle);
}


//-------------------------- getEntrances ---------------------------
//                  Return the pipe entrances.
//-------------------------------------------------------------------
const std::array<int, 4>& Pipe::getEntrances() const
{
	return m_entrances;
}


//------------------------- randromRotate ---------------------------
//                   Rotate the pipe randomly.
//-------------------------------------------------------------------
void Pipe::randromRotate()
{	
	auto numOfRotation = rand() % 4;

	for (auto i = 0; i < numOfRotation; i++)
	{
		rotateRight();
	}
}


//-------------------------- setConStatus ---------------------------
// Sets the connection status.
//-------------------------------------------------------------------
void Pipe::setConStatus(bool status)
{
	m_connected = status;
}


//------------------------ SetPipeTexture ---------------------------
// Sets the texture of the pipe accodring to the flow.
//-------------------------------------------------------------------
void Pipe::SetPipeTexture(const sf::Texture* texture)
{
	m_shape.setTexture(texture);
}


//----------------------- SetPipeTexture ----------------------------
// Returns the connections status.
// i.e. returns if a flow passes through it.
//-------------------------------------------------------------------
bool Pipe::getconStatus() const
{
	return m_connected;
}


//------------------------- getTextrue ------------------------------
//				     Return the obejct textrue.
//-------------------------------------------------------------------
const sf::Texture* Pipe::getTextrue() const
{
	return m_shape.getTexture();
}


void Pipe::SetTexture() {}
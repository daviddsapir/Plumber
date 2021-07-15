#pragma once

//--------------------------- Include section  ---------------------------
#include "SFML/Graphics.hpp"


//-------------------- class InstructionScreen -----------------
class InstructionScreen
{
public:

	// c-tor
	InstructionScreen();

	// d-tor
	virtual ~InstructionScreen();

	// Handles the event that the button is released
	void handleMouseButtonReleased(const sf::Vector2f& location,
		bool& showInstruction);

	// Handle the event that the mouse howers the back button
	void handleHoverButton(const sf::Vector2f& location);
	
	// Draw the instruction screen on the window
	void draw(sf::RenderWindow& window);

	// Set the needed data that should be displayed
	void setInstructionScreen();


private:

	// To hold the gameObjectTextures of the player,
	// enemy, coin ...
	sf::RectangleShape
		m_background,
		backBtn;

	sf::Text backBtnTxt;

	// Sets the texts titles
	void setTextTitles(sf::Text& titleTxt, std::string str,
		const int pos_x, const int pos_y);
};

//--------------------------- Include section  ---------------------------
#include "InstructionScreen.h"
#include "Macros.h"
#include "Resources.h"


//----------------------------- constractor ------------------------------
// Sets the The desired size of the objects that should be 
// displayed if the user enters the instructions from the menu.
// The c-tor uses the help of the auxillary function 
// setInstructionScreen that sets the instructs texts.
//------------------------------------------------------------------------
InstructionScreen::InstructionScreen():
	m_background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)),
	backBtn(sf::Vector2f(WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.1))
{
	// Set the needed data that should be
	// displayed upon the instruction screen
	setInstructionScreen();
}


// d-tor
InstructionScreen::~InstructionScreen() {}


//---------------------- handleMouseButtonReleased -----------------------
//        Handles the event that the button is released
//------------------------------------------------------------------------
void InstructionScreen::handleMouseButtonReleased
(const sf::Vector2f& location, bool& showInstruction)
{
	if (backBtn.getGlobalBounds().contains(location))
	{
		Resources::instance().ClickedSound(MENU_BUTTON_CLICK);
		showInstruction = false;
	}
}

//-------------------------- handleHoverButton ---------------------------
//         Handle the event that the mouse howers the back button
//------------------------------------------------------------------------
void InstructionScreen::handleHoverButton(const sf::Vector2f& location)
{
	if (backBtn.getGlobalBounds().contains(location))
	{
		backBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON_HOVER));
	}
	else
	{
		backBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON));
	}
}


//------------------------------ draw ------------------------------------
//    Draw the instruction screen on the window
//------------------------------------------------------------------------
void InstructionScreen::draw(sf::RenderWindow& window)
{
	// Draw the background
	window.draw(m_background);

	// Draw the button of the instruction scree 
	// (the back to menu button)
	window.draw(backBtn);
	window.draw(backBtnTxt);
}


//------------------------- setInstructionScreen -------------------------
// Set the needed data that should be displayed upon the instruction
// screen.
//------------------------------------------------------------------------
void InstructionScreen::setInstructionScreen() 
{
	Resources& r = Resources::instance();

	// Set the background texture
	m_background.setTexture(r.getWindowObjectTexture(INSTRUCTION_MENU));

	//Set button.
	backBtn.setTexture(r.getWindowObjectTexture(BUTTON));
	backBtn.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.4,
		WINDOW_HEIGHT * 0.8));
	
	// Set the text "Back" and it's position the instruction screen
	setTextTitles(backBtnTxt, "Back",
		WINDOW_WIDTH * 0.465, WINDOW_HEIGHT * 0.81);
}


//---------------------------- setTextTitles -----------------------------
// Sets the texts titles.
// Auxillary function to set the desired text title.
// The auxillary function gets a titleTxt and the desired string and 
// it's position and sets the text with those parametrs.
//------------------------------------------------------------------------
void InstructionScreen::setTextTitles(sf::Text &titleTxt,
	std::string str, const int pos_x, const int pos_y) 
{	
	// Set the charcter size
	titleTxt.setCharacterSize(50);

	// Set the font - gets the font from the resources
	titleTxt.setFont((*Resources::instance().getArialfont()));

	// Set the desired string 
	titleTxt.setString(str);

	// Set the position of the text
	titleTxt.setPosition(sf::Vector2f(pos_x, pos_y));
}

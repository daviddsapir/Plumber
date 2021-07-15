#include "EndGameScreen.h"
#include "Macros.h"
#include "Resources.h"
#include <string>


//-------------------------- EndGameScreen --------------------------
// Display to the window the end game screen with all the needed
// data such as:time passed, taps counted, stage ended.
//-------------------------------------------------------------------
EndGameScreen::EndGameScreen() :
	m_background({ WINDOW_WIDTH,WINDOW_HEIGHT }), 
backToMenuBtn(sf::Vector2f(WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.1))
{
	Resources& r = Resources::instance();

	// Set the backgorund of the 
	m_background.setTexture(r.getWindowObjectTexture(DATA_MENU));

	//Back buttons.
	setBackButton();

	//Set title text.
	setTitleText();

	// Set fonts
	setFonts();
}


//------------------ setFonts -------------------
// Set the fonts of the end game screen 
//-----------------------------------------------
void EndGameScreen::setFonts()
{
	Resources& r = Resources::instance();

	backBtnTxt.setFont(*r.getArialfont());
	tapsTxt.setFont(*r.getArialfont());
	timeTxt.setFont(*r.getArialfont());
	stageTxt.setFont(*r.getArialfont());
}


//--------------- setTitleText ----------------
// Set the title text of the end game screen
//---------------------------------------------
void EndGameScreen::setTitleText()
{
	Resources& r = Resources::instance();

	titleTxt.setFont(*r.getArialfont());
	titleTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.40,
		WINDOW_HEIGHT * 0.2));
	titleTxt.setCharacterSize(50);
}



//---------------------- setBackButton ------------------------
//       Set the back button to the menu window
//--------------------------------------------------------------
void EndGameScreen::setBackButton()
{
	Resources& r = Resources::instance();

	//Set button.
	backToMenuBtn.setTexture(r.getWindowObjectTexture(BUTTON));
	backToMenuBtn.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.4,
		WINDOW_HEIGHT * 0.8));

	// Set back button
	std::string str = "Back";
	backBtnTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.47, WINDOW_HEIGHT * 0.81));
	backBtnTxt.setCharacterSize(50);
	backBtnTxt.setString(str);
}



//-------------------- draw ------------------------
// Draws the end game screen with the needed data.
// If the player wins the  
//--------------------------------------------------
void EndGameScreen::draw(sf::RenderWindow& window) 
{
	window.draw(m_background);
	window.draw(backToMenuBtn);
	window.draw(backBtnTxt);

	setWinScreen(window);

}




//----------------- handleMouseButtonReleased ------------------
// Handle the event that the mouse button is clicked upon the 
// BACK button of the end gamescreen.
// ==> Go back to menu on button click.
//--------------------------------------------------------------
void EndGameScreen::handleMouseButtonReleased
(const sf::Vector2f& location, bool& showEndScreen)
{
	if (backToMenuBtn.getGlobalBounds().contains(location))
	{
		Resources::instance().ClickedSound(MENU_BUTTON_CLICK);
		showEndScreen = false;
	}
}



//----------------------- handleHoverButton -----------------------
// Change button color on hover.
// handles the mouse that hovers the back button in the end game 
// screen. If the mouse hovers the back button, swich the color.
//-----------------------------------------------------------------
void EndGameScreen::handleHoverButton(const sf::Vector2f& location)
{
	if (backToMenuBtn.getGlobalBounds().contains(location))
	{
		// mouse hovers ==> change the color of the button
		backToMenuBtn.setTexture
		(Resources::instance().getWindowObjectTexture(BUTTON_HOVER));
	}
	else
	{
		// stay with the defualt color of the button
		backToMenuBtn.setTexture
		(Resources::instance().getWindowObjectTexture(BUTTON));
	}
}


//--------------------- setWinScreen ---------------------------
// Set the player win game, when the player complated all stages.
//--------------------------------------------------------------
void EndGameScreen::setWinScreen(sf::RenderWindow& window)
{
	std::string str = "Congratulations\nYou Have Won!";
	titleTxt.setString(str);
	titleTxt.setStyle(sf::Text::Underlined);
	titleTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.40, WINDOW_HEIGHT * 0.15));
	titleTxt.setCharacterSize(50);

	// Set the time passed text with the needed width and height
	setDataText(timeTxt, "Final Time: ",
		finalTime, WINDOW_HEIGHT * 0.3);

	// Set the taps counted text with the needed width and height
	setDataText(tapsTxt, "Final taps counted: ",
		finalTaps, WINDOW_HEIGHT * 0.4);

	// Set the stage text with the needed width and height
	setDataText(stageTxt, "Finish Stage: ",
		finalStage, WINDOW_HEIGHT * 0.5);

	window.draw(titleTxt);        // draw the title text on the window
	window.draw(timeTxt);		  // draw the time on the window
	window.draw(stageTxt);		  // draw the stage text on the window
	window.draw(tapsTxt);		  // draw the taps text on the window
}


//----------------- setWinGameData -----------------
//             Set the end game data.
// Sets the data that needs to be displayed if the
// player finished all stages in the game.
//--------------------------------------------------
void EndGameScreen::setWinGameData(const int time,
	const int taps, const int stage)
{
	finalTime = time;
	finalTaps = taps;
	finalStage = stage;
}


//------------------- setDataText --------------------
// Set the string, style, position and the charcter
// size of the text.
//----------------------------------------------------
void  EndGameScreen::setDataText(sf::Text &dataTxt,
	std::string str, const int info, const int pos_y) 
{		
	str += std::to_string(info);
	dataTxt.setString(str);
	dataTxt.setStyle(sf::Text::Bold);
	dataTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.30, pos_y));
	dataTxt.setCharacterSize(50);
}


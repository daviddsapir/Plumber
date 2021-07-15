#pragma once

//--------------------------- Include section  ---------------------------
#include "Menu.h"
#include "Board.h"
#include "InstructionScreen.h"
#include "EndGameScreen.h"
#include "SFML/Graphics.hpp"
#include "NextStagePopUp.h"


//----------------------------- Controller -------------------------------
class Controller
{
public:

	// C-tor
	Controller();

	// Shows the screen
	void showScreen();

	// runs the game.
	void runGame(sf::Event&);

private:

	// Show menu screen
	void openMenu(sf::Event&);

	// Runs the end game screen.
	void openEndGameScreen(sf::Event&);

	// Show instruction screen.
	void openInstruction(sf::Event&);

	// Show information of running game.
	void setInfoWindow();

	// Set text information.
	void setGameTxtUI();

	// Draws the game.
	void draw();

	// Handle the event that the mouse button got pressed.
	void handleClickButton(const sf::Vector2f&, const sf::Event&);

	// Return a string that represents the current mouse buttons status.
	std::string getMouseButtonStatus(const sf::Event&);

	// Handle time event.
	void timeHandler();

	// Checks the pipes connection.
	bool checkConnection(Pipe*&, Pipe*&);

	// Update the amount of clicks and pipe connection.
	void updateTapsAndPipes();

	// Checks the current pipes connection.
	void checkPipeConection();

	// Turns off the game.
	void endTheGame();

	// Loads the next stage.
	void nextStage();

	// Set the current status of the pipes.
	void setPipeStatus(Pipe*&, const bool);

	// Returns if the pipes are connected.
	bool isConnected(const int, const int) const;

	// Sets the menu text.
	void setMenuTxt();

	// Draws the menu text.
	void drawMenuTxt();

	// Returns if flow has reached the target pipe
	bool isTargetReached(Pipe*&) const;

	// Reprasants screen states of the game.
	bool exitGame = false,
		startGame = false,
		showInstruction = false,
		showEndGameScreen = false,
		wonTheGame = false,
		continueStage = true;

	unsigned int
		m_tapsNum = 0,		// taps counter.
		m_time = 0,			// time counter.
		m_stageNum = 1;		// stage counter.

	// Holds the board of the game.
	Board m_board;

	//Time passed
	sf::Clock m_timer;

	// the window
	sf::RenderWindow m_window;

	//Screen menu of the game
	Menu m_menu;

	// Instruction of the game.
	InstructionScreen m_instructScreen;

	//Screen at the end of how the game
	EndGameScreen m_endGameScreen;

	//Pop up to continue to the next stage.
	NextStagePopUp m_nextStagePopup;

	// To hold the menu informain.
	sf::RectangleShape m_infoWindow,
		m_boardWindowBackground, m_timeInfo,
		m_tapCount, m_windowInfoTitle;

	sf::Text m_timeTxt, m_tapCountTxt;
};

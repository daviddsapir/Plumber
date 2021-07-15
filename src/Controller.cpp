//--------------------------- Include section  ---------------------------
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Macros.h"
#include "Controller.h"
#include "Pipe.h"
#include "SourcePipe.h"
#include "TargetPipe.h"
#include "I_pipe.h"
#include "T_pipe.h"
#include "L_Pipe.h"
#include "Resources.h"


//------------------------------- C-tor ---------------------------------- 
// Defines the objectsand their sizes accordingly
//------------------------------------------------------------------------
Controller::Controller()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Plumber"),
    m_infoWindow({ 0.2 * WINDOW_WIDTH,WINDOW_HEIGHT }),
    m_tapCount({ 0.15 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT }),
    m_timeInfo({ 0.15 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT }),
    m_boardWindowBackground({ 0.8 * WINDOW_WIDTH,WINDOW_HEIGHT }),
    m_windowInfoTitle({ 0.15 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT })
{
    m_boardWindowBackground.setPosition(sf::Vector2f(0.2 * WINDOW_WIDTH,0));
    m_boardWindowBackground.setTexture(
    Resources::instance().getWindowObjectTexture(BOARD_WINDOW_BACKGROUND));

    setInfoWindow();
}


//----------------------------  showScreen -------------------------------
// Showing the different screen existed in the game.
//------------------------------------------------------------------------
void Controller::showScreen()
{
    sf::Event event;

    // Perform an initial inspection of the pipe connection.
    checkPipeConection();
 
    while (m_window.isOpen())
    {
        sf::Event event;

        // Clear the window
        m_window.clear();

        // Start running the game
        if (startGame) {
            if (!Resources::instance().isMusicPlayed()) {
                Resources::instance().playSoundTrack();
            }
            runGame(event);
        }

        // Open istruction in game menu
        else if (showInstruction)
            openInstruction(event);

        // Display the end game window + end game status
        else if (showEndGameScreen)
        {
            // Play game soundtrack
            if (Resources::instance().isMusicPlayed()) {
                Resources::instance().turnOffSoundTrack();
            }
            openEndGameScreen(event);
        }
        // Exit the game
        else if (!exitGame)
            openMenu(event);

        else
            break;

        // Display the window
        m_window.display();
    }
}


//------------------------------- runGame --------------------------------
// The main function of controller which runs the game and handles
// the possible events that can appear during the game. 
//------------------------------------------------------------------------
void Controller::runGame(sf::Event& event)
{
    if (auto event = sf::Event{}; m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed: m_window.close();   break;

        case sf::Event::MouseButtonReleased:
            if (continueStage) {
                // Handles the event the user pressed the mouse.
                handleClickButton(m_window.mapPixelToCoords
                (sf::Mouse::getPosition(m_window)), event);
            }
            else {
                m_nextStagePopup.handleMouseButtonReleased(m_window.mapPixelToCoords
                (sf::Mouse::getPosition(m_window)), continueStage);

            }
            break;
        case sf::Event::MouseMoved:
            if(!continueStage)
            {
                m_nextStagePopup.handleHoverButton(m_window.mapPixelToCoords
                (sf::Mouse::getPosition(m_window)));
            }
        }
    }

    // Wait until user confirm to continue next stage
    // by pressing 'next'button
    if (wonTheGame && continueStage) 
    {
        if (m_stageNum < MAX_STAGES)
        {
            nextStage();
        }
        else
        {
            endTheGame();
        }
    }

    // Handle events of the game. 
    timeHandler();

    // Draw the game objects upon the window.
    draw();    

    // Small pop up window.
    if (!continueStage) {
        m_nextStagePopup.draw(m_window);
    }
}


//------------------------------ openMenu --------------------------------
// Open the menu screen, the screen showing the following buttons:
// Start - allowing the player start the game.
// Instruction - show how to play the game.
// Exit - exit from the game.
//------------------------------------------------------------------------
void Controller::openMenu(sf::Event& event)
{
    while (m_window.pollEvent(event))
    {

        switch (event.type)
        {
        case sf::Event::Closed:
            
            // close the window
            m_window.close();
            break;

        case sf::Event::MouseButtonReleased:

            // Handle a click on a button when mouse button is released.
            m_menu.handleClickButton
            (m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)),
                m_window, exitGame, startGame, showInstruction);
            break;

        case sf::Event::MouseMoved:

            // Handle a the event of the mouse hovering the 
            // buttons of the menu.
            m_menu.handleHoverButton(m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)), m_window);
            break;
        }
    }

    // Draw the menu on the window
    m_menu.draw(m_window);
}


//-------------------------- openEndGameScreen ---------------------------
// Runs the end game screen.
//------------------------------------------------------------------------
void Controller::openEndGameScreen(sf::Event& event)
{
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:

            // Close the window
            m_window.close();
            break;

        case sf::Event::MouseButtonReleased:

            // Handle a click on a button when mouse button is released.
            m_endGameScreen.handleMouseButtonReleased
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)), showEndGameScreen);
            break;

        case sf::Event::MouseMoved:

            // Handle a the event of the mouse hovering the 
            // buttons of the instruction screen.
            m_endGameScreen.handleHoverButton
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)));
            break;
        }
    }

    // Draw the instructions upon the window.
    m_endGameScreen.draw(m_window);
}


//--------------------------- openInstruction ----------------------------
// Open the Instruction screen, the screen show how  to play the 
// game and what each item in the game role.
//------------------------------------------------------------------------
void Controller::openInstruction(sf::Event& event)
{
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:

            // Close the window
            m_window.close();
            break;

        case sf::Event::MouseButtonReleased:

            // Handle a click on a button when mouse button is released.
            m_instructScreen.handleMouseButtonReleased
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)), showInstruction);
            break;

        case sf::Event::MouseMoved:

            // Handle a the event of the mouse hovering the 
            // buttons of the instruction screen.
            m_instructScreen.handleHoverButton
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)));
            break;
        }
    }

    // Draw the instructions upon the window.
    m_instructScreen.draw(m_window);
}


//---------------------------- setInfoWindow -----------------------------
// Open the menu screen, the screen showing the following buttons:
// Start - allowing the player start the game.
// Instruction - show how to play the game.
// Exit - exit from the game.
//------------------------------------------------------------------------
void Controller::setInfoWindow()
{
    m_infoWindow.setPosition({ 0,0 });
    m_timeInfo.setPosition({ 0.025 * WINDOW_WIDTH,0.3 * WINDOW_HEIGHT });
    m_tapCount.setPosition({ 0.025 * WINDOW_WIDTH,0.6 * WINDOW_HEIGHT });

    m_windowInfoTitle.setPosition({ 0.025 * WINDOW_WIDTH,0.05
        * WINDOW_HEIGHT });

    Resources& resource = Resources::instance();

    m_windowInfoTitle.setTexture
    (resource.getWindowObjectTexture(PLUMBER_TITLE));

    m_infoWindow.setTexture
    (resource.getWindowObjectTexture(SIDE_MENU));

    m_timeInfo.setTexture
    (resource.getWindowObjectTexture(TEXT_BACKGROUND));

    m_tapCount.setTexture
    (resource.getWindowObjectTexture(TEXT_BACKGROUND));

    // Set the text information.
    setGameTxtUI();
}


//------------------------------ setTxtInfo ----------------------------
// Set the game Text objects characteristics.
//------------------------------------------------------------------------
void Controller::setGameTxtUI()
{
    m_timeTxt.setFont(*(Resources::instance().getArialfont()));
    m_tapCountTxt.setFont(*(Resources::instance().getArialfont()));
    m_timeTxt.setPosition({ 0.075 * WINDOW_WIDTH,0.3 * WINDOW_HEIGHT });
    m_tapCountTxt.setPosition({ 0.075 * WINDOW_WIDTH,0.6 * WINDOW_HEIGHT });

    m_timeTxt.setString(TIME_STR);
    m_tapCountTxt.setString(TAPS_STR);

    m_timeTxt.setCharacterSize(CHARCTER_SIZE);
    m_timeTxt.setScale({ 1,1 });
    m_timeTxt.setFillColor(sf::Color::White);
    m_timeTxt.setStyle(sf::Text::Bold);

    m_tapCountTxt.setCharacterSize(CHARCTER_SIZE);
    m_tapCountTxt.setScale({ 1,1 });
    m_tapCountTxt.setFillColor(sf::Color::White);
    m_tapCountTxt.setStyle(sf::Text::Bold);
}



//-------------------------------- draw ----------------------------------
// Draws all the objects of the game and displays it upon the window.
//------------------------------------------------------------------------
void Controller::draw()
{
    // Draw the window background.
    m_window.draw(m_boardWindowBackground);

    // Draw the board.
    m_board.draw(m_window);

    // Draw the informain window.
    m_window.draw(m_infoWindow);

    // Draw the information title.
    m_window.draw(m_windowInfoTitle);

    // draw the timer.
    m_window.draw(m_timeInfo);

    // Draw the tap counter value.
    m_window.draw(m_tapCount);

    // Sets and draws the menu. 
    setMenuTxt();
    drawMenuTxt();
}


//--------------------------- handleClickButton --------------------------
// Handle the event that the mouse button got pressed.
// Performs a check if there was a press of the right or left button and 
// accordingly sends the position of the click and a string indicating 
// which button was pressed.
// 
// ClickStatus - holds if the click was upon a pipe.
// button - Gets a string that indicates which button was pressed.
//          The optaions are Left, Right or no mouse button click was
//          pressed. 
// 
// If there was a click on the button, we will update the data structure 
// and the number of clicks will increase by 1.
//------------------------------------------------------------------------
void Controller::handleClickButton(const sf::Vector2f& location,
    const sf::Event& event)
{
    bool ClickStatus = false;

    if (auto button = getMouseButtonStatus(event); button != NOT_PRESSED) 
    {
        for (auto i = m_board.pipesBegin(); i != m_board.pipesEnd(); i++)
        {
            for (auto j = i->begin(); j < i->end(); j++) 
            {
                if (*j) 
                {
                    if (ClickStatus = j->get()->
                        handleClickButton(location, button); ClickStatus) 
                    {
                        updateTapsAndPipes();
                    }
                }
            }
        }
    }
}


//------------------------- getMouseButtonStatus -------------------------
// Return a string that represents the current mouse buttons status.
//------------------------------------------------------------------------
std::string Controller::getMouseButtonStatus(const sf::Event& event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        return std::string(LEFT_BUTTON);
    }

    if (event.mouseButton.button == sf::Mouse::Right)
    {
        return std::string(RIGHT_BUTTON);
    }
    
    return std::string(NOT_PRESSED);
}


//---------------------------- checkConnection ---------------------------
// Checks the pipes connection.
// Checks if the pipes are connected by using their locations and their 
// entrances. We say that 2 pipes are connected if The two rectangular
// sides facing each other contain the value 1 respectively.
//------------------------------------------------------------------------
bool Controller::checkConnection(Pipe*& p1, Pipe*& p2)
{
    auto p1_entrances = p1->getEntrances();
    auto p2_entrances = p2->getEntrances();
    auto p1_index = p1->getIndex();
    auto p2_index = p2->getIndex();
    bool status = false;


    // Check if the pipes are connected.
    if (p1_index.second > p2_index.second)
    {
        status = isConnected(p1_entrances[UP], p2_entrances[DOWN]);
    }
    else if (p1_index.second < p2_index.second)
    {
        status = isConnected(p1_entrances[DOWN], p2_entrances[UP]);
    }
    else if (p1_index.first > p2_index.first)
    {
        status = isConnected(p1_entrances[LEFT], p2_entrances[RIGHT]);
    }
    else if (p1_index.first < p2_index.first)
    {
        status = isConnected(p1_entrances[RIGHT], p2_entrances[LEFT]);
    }

    // Set the current status(connected or not) of the neighbor pipe.
    setPipeStatus(p2, status);

    if (isTargetReached(p2) && status)
    {
        wonTheGame = true;
        continueStage = false;
    }

    return status;
}


//-------------------------- updateTapsAndPipes --------------------------
// Update the amount of clicks and pipe connection.
//------------------------------------------------------------------------
void Controller::updateTapsAndPipes()
{
    // increase the number of taps by 1.
    ++m_tapsNum;

    // An operation has been performed on one of the pipes and 
    // therefore it is necessary to update the pipes status.
    m_board.SetPipeStatus();

    // Checks the connection of the pipes.
    checkPipeConection();
}


//-------------------------- checkPipeConection --------------------------
// Checks the current pipes connection.
// Check if source connected to 'Source' to 'Target':
// Find if the Source connected to Target :
// 1.Pick the existed source location.
// 2.Run BFS from the source pipe to adjacency pipes, that are connected.
// 3.If the target is found, stop.
//------------------------------------------------------------------------
void Controller::checkPipeConection()
{
    auto source_index = m_board.getSourceIndex();
    
    // Mark all the vertices as not visited
    auto visited = std::vector<std::vector<bool>>{};
    visited.resize(m_board.getMapSize());
    for (size_t i = 0; i < visited.size(); i++)
    {
        visited[i].resize(m_board.getMapSize());
    }
    
 
    // Create a queue for BFS
    std::list<std::pair<int, int>> queue{};

    // Mark the current node as visited and enqueue it
    visited[source_index.first][source_index.second] = true;
    queue.push_back(source_index);
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        auto v = queue.front();
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it.
        auto adjacencyList = m_board.getAdjacencyListAt(v.first, v.second);

        // Run over the adjacency list of vertex v.
        for (auto i = adjacencyList.begin();
            i != adjacencyList.end(); ++i)
        {
            auto index = i->get()->getIndex();

            if (!visited[index.first][index.second])
            {
                auto p1 = &m_board.getPipe(v.first, v.second);
                auto p2 = i->get();

                // check the connection between 
                // the vertexes (the pipes).
                if (checkConnection(p1, p2))
                {
                    // mark the vertex(pipe) as visited 
                    // and enter into the queue.
                    visited[index.first][index.second] = true;
                    queue.push_back(index);
                }
            }
        }
    }
}


//----------------------------- endTheGame ------------------------------- 
//                          Turns off the game.
//------------------------------------------------------------------------
void Controller::endTheGame()
{
    m_endGameScreen.setWinGameData(m_time, m_tapsNum, m_stageNum);
    m_time = 0;
    m_tapsNum = 0;
    m_stageNum = 1;
    m_board.intilizeBoardMap();
    m_board.nextStage();
    wonTheGame = false;
    showEndGameScreen = true;
    startGame = false;
    Resources::instance().winSound();
}


//------------------------------ nextStage ------------------------------- 
//                          Loads the next stage.
//------------------------------------------------------------------------
void Controller::nextStage()
{
    m_stageNum++;
    m_board.nextStage();
    wonTheGame = false;

    // Perform an initial inspection of the pipe connection.
    checkPipeConection();
}


//---------------------------- setPipeStatus -----------------------------
// Set the current status of the pipes.
//------------------------------------------------------------------------
void Controller::setPipeStatus(Pipe*& p, const bool status)
{
    p->setConStatus(status);
    p->SetTexture();
}


//----------------------------- isConnected ------------------------------
// Returns if the pipes are connected.
//------------------------------------------------------------------------
bool Controller::isConnected(const int p1_entrance,
    const int p2_entrance) const
{
    return (p1_entrance == p2_entrance && p1_entrance == 1);
}


//----------------------------- setMenuTxt -------------------------------
//                          Sets the menu text.
//------------------------------------------------------------------------
void Controller::setMenuTxt()
{
    m_timeTxt.setString(std::string(TIME_STR).
        append(std::to_string(m_time)));

    m_tapCountTxt.setString(std::string(TAPS_STR).
        append(std::to_string(m_tapsNum)));
}


//----------------------------- drawMenuTxt ------------------------------
//                          Draws the menu text.
//------------------------------------------------------------------------
void Controller::drawMenuTxt()
{
    m_window.draw(m_timeTxt);
    m_window.draw(m_tapCountTxt);
}


//-------------------------- isTargetReached -----------------------------
// Return if there is a flow from the source to the target.
//------------------------------------------------------------------------
bool Controller::isTargetReached(Pipe*& pipe) const
{
    return (pipe->getTextrue() == Resources::instance().
        getPipesObjectTextures(PIPE_TAR));
}


//----------------------------- timeHandler ------------------------------
// Handle time event.
// Increases time by 1, every second.
//------------------------------------------------------------------------
void Controller::timeHandler()
{
    // Increase time by 1, every second.
    if (m_timer.getElapsedTime().asSeconds() >= 1.f)
    {
        m_time += 1;
        m_timer.restart();
    }
}



//--------------------------- Include section  ---------------------------
#include "NextStagePopUp.h"
#include "Macros.h"


//------------------------------- C-tor ----------------------------------
// Sets the button and the text that should be printed according to the 
// Dimensions Received.
//------------------------------------------------------------------------
NextStagePopUp::NextStagePopUp() :
    nextStageScreen({ WINDOW_WIDTH * 0.2,WINDOW_HEIGHT * 0.2 }),
    nextStageButton({ WINDOW_WIDTH * 0.1,WINDOW_HEIGHT * 0.1 })
{
    nextButtonTxt.setFont(*Resources::instance().getArialfont());

    successTxt.setFont(*Resources::instance().getArialfont());

    setNextStageWindow();
}


// D-tor
NextStagePopUp::~NextStagePopUp()
{}


//------------------------------- draw -----------------------------------
// Draws the objects upon the window.
//------------------------------------------------------------------------
void NextStagePopUp::draw(sf::RenderWindow& window)
{
    window.draw(nextStageScreen);
    window.draw(successTxt);
    window.draw(nextStageButton);
    window.draw(nextButtonTxt);
}


//------------------------- handleHoverButton ----------------------------
// Handle the event that the mouse button got pressed.
//------------------------------------------------------------------------
void NextStagePopUp::handleHoverButton(const sf::Vector2f& location)
{
    if (nextStageButton.getGlobalBounds().contains(location))
    {
        // Mouse hovers ==> change the color of the button.
        nextStageButton.setTexture
        (Resources::instance().getWindowObjectTexture(BUTTON_HOVER));
    }
    else
    {
        // Stay with the defualt color of the button.
        nextStageButton.setTexture
        (Resources::instance().getWindowObjectTexture(BUTTON));
    }
}


//---------------------- handleMouseButtonReleased -----------------------
// Handle the event that the mouse button got released upon the button.
//------------------------------------------------------------------------
void NextStagePopUp::handleMouseButtonReleased
(const sf::Vector2f& location, bool& continueGame)
{
    if (nextStageButton.getGlobalBounds().contains(location))
    {
        Resources::instance().ClickedSound(MENU_BUTTON_CLICK);
        continueGame = true;
    }
}


//------------------------ setRandomSuccessString ------------------------
// Sets a random string that is displayed upon the next stage window.
//------------------------------------------------------------------------
void NextStagePopUp::setRandomSuccessString()
{
    switch (rand() % NUM_OF_RANDROM_SUCCESS_STR)
    {
    case FIRST_SUCCESS_STR: successTxt.setString(WELL_DONE_STR);    break;
    case SECOND_SUCCESS_STR: successTxt.setString(GREAT_JOB_STR);   break;
    }
}


//-------------------------- setNextStageWindow --------------------------
// Sets the next stage window.
//------------------------------------------------------------------------
void NextStagePopUp::setNextStageWindow()
{
    // Set the next stage window position, texture, position, color,
    // thickness and outline color.
    nextStageScreen.setPosition
    (0.4 * WINDOW_WIDTH, 0.4 * WINDOW_HEIGHT);
    nextStageScreen.setTexture(Resources::instance().
        getWindowObjectTexture(BOARD_BACKGROUND));
    nextStageButton.setPosition(WINDOW_WIDTH * 0.45,
        WINDOW_HEIGHT * 0.5);
    nextStageButton.setTexture(Resources::instance().
        getWindowObjectTexture(BUTTON_HOVER));
    nextStageScreen.setOutlineColor(sf::Color::Black);
    nextStageScreen.setOutlineThickness(3);


    // Set the success text fill color, style, position, size, and etc.
    successTxt.setFillColor(sf::Color::Black);
    setRandomSuccessString();
    successTxt.setStyle(sf::Text::Bold);
    successTxt.setPosition
    (sf::Vector2f(WINDOW_WIDTH * 0.45, WINDOW_HEIGHT * 0.44));
    successTxt.setCharacterSize(40);

    // Set the success next button text fill color, style, position, size, and etc.
    nextButtonTxt.setFillColor(sf::Color::Black);
    nextButtonTxt.setString("  Next");
    nextButtonTxt.setStyle(sf::Text::Bold);
    nextButtonTxt.setPosition
    (sf::Vector2f(WINDOW_WIDTH * 0.46, WINDOW_HEIGHT * 0.51));
    nextButtonTxt.setCharacterSize(40);
}


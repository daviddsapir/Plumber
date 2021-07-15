#pragma once

//--------------------------- Include section  ---------------------------
#include "SFML/Graphics.hpp"
#include "Macros.h"
#include "Resources.h"


//------------------------- Class NextStagePopUp  ------------------------
class NextStagePopUp
{
public:

    // D-tor
    NextStagePopUp();
    
    // C-tor
    ~NextStagePopUp();

    // Draw the next stage windows.
    void draw(sf::RenderWindow& window);

    // Handles the situation the the mouse hovers the back button
    void handleHoverButton(const sf::Vector2f& location);

    // Handles the button release in the end game screen
    void handleMouseButtonReleased(const sf::Vector2f& location,
        bool& showMenu);

    // Sets a random string that should be displayed.
    void setRandomSuccessString();

private:

    // Set the next stage windows.
    void setNextStageWindow();

    sf::RectangleShape nextStageScreen, nextStageButton;

    sf::Text successTxt, nextButtonTxt;
};
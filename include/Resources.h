#pragma once

//--------------------------- Include section  ---------------------------
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


//--------------------------- Class Resources ----------------------------
class Resources
{
public:

	// Return the address of the only object of this class.
	static Resources& instance();

	// d-tor
	~Resources();

	// Return windows texture in index i.
	sf::Texture* getWindowObjectTexture(const int&);

	// Return pipe texture in index i.
	sf::Texture* getPipesObjectTextures(const int&);

	// Return soundBuffers in index i.
	sf::SoundBuffer* getSoundBuffer(const int&);

	// Return arial font.
	const sf::Font* getArialfont() const;

	// Play the sound of pressing a button.
	void ClickedSound(const int&);

	// Plays the sound when win game.
	void winSound();

	// Return the music status (on or off).
	bool isMusicPlayed();

	// Turn on the soundTrack.
	void playSoundTrack();

	// Turn off the soundTrack.
	void turnOffSoundTrack();

private:

	// We don't want more than 1 object of this class.
	// This is a singletone.
	Resources();

	Resources(const Resources&) = default;

	Resources& operator=(const Resources&) = default;

	// Set general window  gameObjectTextures of the game.
	void setWindowObjectTextures();

	// Set pipes object textures of the game.
	void setPipesObjectTextures();

	// Set the sounds buffer of the game.
	void setSoundBuffer();

	// set the music soundtrack
	void setMusicSound();

	// vector to hold the window objects.
	std::vector <sf::Texture> m_windowObjectTextures;

	// vector to hold pipes textures
	std::vector <sf::Texture> m_pipeObjectsTextures;

	// Vector to hold all the sounds of the game
	std::vector <sf::SoundBuffer> m_soundsBuffer;
	
	// Holds the fonts of the window
	sf::Font dataWindowFont;

	// Holds the sounds.
	sf::Sound m_sound;

	// Hold the music background.
	sf::Music m_gameSoundTrack;
};


// enum to hold the positions in the 
// vector that hold the game buttons 
enum windowObjectTextures
{
	DATA_MENU,
	BUTTON,
	BUTTON_HOVER,
	INSTRUCTION_MENU,
	BOARD_BACKGROUND,
	BOARD_WINDOW_BACKGROUND,
	PLUMBER_TITLE,
	SIDE_MENU,
	TEXT_BACKGROUND,
	PLAY_MUSIC_BUTTON,
	MUTE_MUSIC_BUTTON,
	BACKGROUND
};


// enum to hold the positions in the 
// vector that hold the game buttons 
enum pipeObjectTextures
{
	PIPE_I_NOT_CON = 0,
	PIPE_L_NOT_CON = 1,
	PIPE_T_NOT_CON = 2,
	PIPE_SRC = 3,
	PIPE_TAR = 4,

	PIPE_I_CON,
	PIPE_L_CON,
	PIPE_T_CON,

	EMPTY_PIPE
};


// enum to hold the positions in the 
// vector that hold the game sounds 
enum sounds
{
	MENU_BUTTON_CLICK,
	PIPE_CLICK,
	WIN_GAME
};



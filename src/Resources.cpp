#pragma once 

//--------------------------- Include section  ---------------------------
#include "Resources.h"
#include "Macros.h"


// c-tor
Resources::Resources()
{
	// Set the general window objects
	setWindowObjectTextures();

	// Set pipes textures
	setPipesObjectTextures();

	// Set the sounds buffers
	setSoundBuffer();

	// Set the music sounds
	setMusicSound();

	// Set the font of the text.
	dataWindowFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}


// d-tor
Resources::~Resources()
{}


//--------------------------- instance ------------------------------
// Retrun pointer to the single object of class Resources.
//-------------------------------------------------------------------
Resources& Resources::instance()
{
	static Resources instance;

	return instance;
}


//--------------------- getWindowObjectTexture ---------------------
// Return the texture, hold in the vector m_gameObjectTextures,
// in index i.
//-------------------------------------------------------------------
sf::Texture* Resources::getWindowObjectTexture(const int& i)
{
	return &(m_windowObjectTextures[i]);
}


//--------------------- getPipesObjectTextures ----------------------
// Return the texture, hold in the vector m_pipeObjectsTextures, in
// index i.
//-------------------------------------------------------------------
sf::Texture* Resources::getPipesObjectTextures(const int& i)
{
	return &(m_pipeObjectsTextures[i]);
}


//-------------------------- getSoundBuffer -------------------------
// Return the sound buffer, hold in the vector m_soundsBuffer, in
// index i.
//-------------------------------------------------------------------
sf::SoundBuffer* Resources::getSoundBuffer(const int& i)
{
	return nullptr;//&(m_soundsBuffer[i]);
}


//-------------------- setWindowObjectTextures ----------------------
// Sets the windows objects textures.
//-------------------------------------------------------------------
void Resources::setWindowObjectTextures()
{
	sf::Texture texture;
	texture.setSmooth(true);
	texture.loadFromFile("data_menu.png");				// 0
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("button.png");					// 1
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("button_hover.png");			// 2
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("instructions.png");		    // 3
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("board_background.png");		// 4
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("board_window_background.png");// 5
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("plumber_title.png");			// 6
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("side_menu_background.png");   // 7
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("text_info_background.png");   // 7
	m_windowObjectTextures.push_back(texture);
}


//--------------------- setPipesObjectTextures ----------------------
// Sets the windows objects textures.
//-------------------------------------------------------------------
void Resources::setPipesObjectTextures()
{
	sf::Texture texture;
	texture.loadFromFile("pipe_i.png");					// 0
	m_pipeObjectsTextures.push_back(texture);
	texture.loadFromFile("pipe_l.png");					// 1
	m_pipeObjectsTextures.push_back(texture);
	texture.loadFromFile("pipe_t.png");					// 2
	m_pipeObjectsTextures.push_back(texture);
	texture.loadFromFile("pipe_src.png");				// 3
	m_pipeObjectsTextures.push_back(texture);
	texture.loadFromFile("pipe_tar.png");				// 4
	m_pipeObjectsTextures.push_back(texture);


	texture.loadFromFile("pipe_i_connect.png");		    // 5
	m_pipeObjectsTextures.push_back(texture);
	texture.loadFromFile("pipe_l_connect.png");			// 6
	m_pipeObjectsTextures.push_back(texture);
	texture.loadFromFile("pipe_t_connect.png");			// 7
	m_pipeObjectsTextures.push_back(texture);

	texture.loadFromFile("empty_pipe.png");				// 8
	m_pipeObjectsTextures.push_back(texture);
}


//------------------------- setSoundBuffer --------------------------
// Sets the sounds that appear in the game when an event happends.
//-------------------------------------------------------------------
void Resources::setSoundBuffer()
{
	sf::SoundBuffer soundBuf;

	soundBuf.loadFromFile("blop.wav");			        // 0	
	m_soundsBuffer.push_back(soundBuf);
	soundBuf.loadFromFile("pipeClick.wav");			    // 1	
	m_soundsBuffer.push_back(soundBuf);
	soundBuf.loadFromFile("win_sound.wav");
	m_soundsBuffer.push_back(soundBuf);					// 2
}


//-------------------------- setMusicSound --------------------------
// Sets the music sound of the game
//-------------------------------------------------------------------
void Resources::setMusicSound()
{
	m_gameSoundTrack.openFromFile("plumber_soundtrack.ogg");
	m_gameSoundTrack.setVolume(8);
	m_gameSoundTrack.setLoop(true);
}


//------------------------ ClickedSound -----------------------
// Plays the sound of pressing a button
//-------------------------------------------------------------------
void Resources::ClickedSound(const int& i)
{
	m_sound.setBuffer(m_soundsBuffer[i]);
	m_sound.setVolume(100);
	m_sound.play();
}


//--------------------------- winSound ------------------------------
// Plays the sound when win game.
//-------------------------------------------------------------------
void Resources::winSound()
{
	m_sound.setBuffer(m_soundsBuffer[WIN_GAME]);
	m_sound.setVolume(10);
	m_sound.play();
}


//------------------------- isMusicPlayed ---------------------------
//           Return the music status (on or off).
//-------------------------------------------------------------------
bool Resources::isMusicPlayed()
{
	return (m_gameSoundTrack.getStatus() ==
		sf::SoundSource::Status::Playing);
}


//------------------------- playSoundTrack --------------------------
// Turn on the soundTrack
//-------------------------------------------------------------------
void Resources::playSoundTrack()
{
	m_gameSoundTrack.play();
}


//------------------------ turnOffSoundTrack ------------------------
// Turn off the soundTrack
//-------------------------------------------------------------------
void Resources::turnOffSoundTrack()
{
	m_gameSoundTrack.pause();
}


//-------------------------- getArialfont ---------------------------
// Return arial font.
//-------------------------------------------------------------------
const sf::Font* Resources::getArialfont() const
{
	return &dataWindowFont;
}
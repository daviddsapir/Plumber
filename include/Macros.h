#pragma once 


#include <SFML/Graphics.hpp>
#include <string>

//--------------------------- window consts ------------------------------
const int
WINDOW_HEIGHT = 1080,
WINDOW_WIDTH = 1920,

TEXT_STYLE = 3,

MAX_STAGES = 5;
//--------------------------- board consts -------------------------------
const int 
BOARD_WINDOW_HEIGHT = 960,
BOARD_WINDOW_WIDTH = 960,
BOARD_WINDOW_POS_X = WINDOW_WIDTH * 0.35,
BOARD_WINDOW_POS_Y = BOARD_WINDOW_HEIGHT *0.05,
BLOCKED_PATHS = 5,
MAP_SIZE = 5;


//---------------------------- Pipe consts -------------------------------
const int
ROTATION_ANGLE = 90,
NUM_OF_PIPE_ENTRANCES = 4;

//PIPE_WIDTH = BOARD_WINDOW_WIDTH / BOARD_SIZE_WIDTH,
// = BOARD_WINDOW_WIDTH / BOARD_SIZE_WIDTH;


//----------------------------- Mouse consts -----------------------------
const std::string
LEFT_BUTTON = "leftMouseButton",
RIGHT_BUTTON = "rightMouseButton",
NOT_PRESSED = "NoMousebuttonPressed";

//------------------------------ Data menu -------------------------------
const std::string
TIME_STR = "\nTime: ",
TAPS_STR = "\nTaps: ";

const int CHARCTER_SIZE = 30;


//-------------------------- NextStagePopUp consts -----------------------
const int 
NUM_OF_RANDROM_SUCCESS_STR = 2,
FIRST_SUCCESS_STR = 0,
SECOND_SUCCESS_STR = 1;

const std::string
WELL_DONE_STR = "Well Done!",
GREAT_JOB_STR = "Great Job!";


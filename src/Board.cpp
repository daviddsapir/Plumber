//--------------------------- Include section  ---------------------------
#include "Board.h"
#include "Resources.h"
#include "Macros.h"
#include "SourcePipe.h"
#include "TargetPipe.h"
#include "I_Pipe.h"
#include "L_Pipe.h"
#include "T_Pipe.h"
#include <cmath>


//-------------------------------- C-tor ---------------------------------
// The contractor receives the dimensions of the board of the game and
// initializes the dimensions of the world and the data structures
// accordingly.
// 
// The function does as follows:
// setPipes - Sets the vector that hold the pipes.
// initializeAdjacencyList - Sets the adjacency list.
// setBoardUI - Sets the user interface of the game. i.e. how the board
// will be presented.
//------------------------------------------------------------------------
Board::Board():m_background({ BOARD_WINDOW_WIDTH ,BOARD_WINDOW_HEIGHT })
{
	setEmptyMatrixCells();

	// Sets the vector that hold the pipes.
	setPipes();

	// Sets the adjacency list.
	initializeAdjacencyList();

	// Sets the user interface.
	setBoardUI();
}


//------------------------------- nextStage ------------------------------
//                             Load next stage.
//------------------------------------------------------------------------
void Board::nextStage()
{
	// increase the map size by 1.
	mapSize += 1;

	// Increase the dimensions of the pipes accordingly 
	// to the map size.
	pipeSize = BOARD_WINDOW_HEIGHT / mapSize;

	// Clear the vector that holds the pipes.
	// New pipes need to be loaded.
	m_pipes.clear();
	
	// Clear the previous route.
	route.clear();

	setEmptyMatrixCells();

	// Clear the previous adjacency list.
	m_adjacencyList.clear();

	// Clear the previous empty blocks.
	m_emptyBlocks.clear();

	// Initialize the new pipes.
	setPipes();

	// Initialize the new adjacency list.
	initializeAdjacencyList();
}


//------------------------------ setBoardUI ------------------------------
// Sets the user interface. i.e. how the board will be presented.
//------------------------------------------------------------------------
void Board::setBoardUI()
{
	m_background.setOutlineColor(sf::Color::White);

	m_background.setOutlineThickness(2);

	m_background.setTexture(Resources::instance().
		getWindowObjectTexture(BOARD_BACKGROUND));

	m_background.setPosition({BOARD_WINDOW_POS_X,
		BOARD_WINDOW_POS_Y});
}


//------------------------------ getMapSize ------------------------------
// Return the map size.
//------------------------------------------------------------------------
const int Board::getMapSize() const
{
	return mapSize;
}


//---------------------------- getSourceIndex ----------------------------
// Return index of source pipe.
//------------------------------------------------------------------------
std::pair<int, int> Board::getSourceIndex() const
{
	return std::pair<int, int>(posSourceX,posSourceY);
}


//------------------------------ pipesBegin ------------------------------
// Return iterator to the begining of the vector that hold the pipes.
//------------------------------------------------------------------------
std::vector<std::vector<std::shared_ptr<Pipe>>>::iterator
	Board::pipesBegin()
{
	return m_pipes.begin();
}


//------------------------------ pipesEnd --------------------------------
// Return iterator to the end of the vector that hold the pipes.
//------------------------------------------------------------------------
std::vector<std::vector<std::shared_ptr<Pipe>>>::iterator 
	Board::pipesEnd()
{
	return m_pipes.end();
}


//---------------------------- getTargetIndex ----------------------------
// Return index of target pipe.
//------------------------------------------------------------------------
std::pair<int, int> Board::getTargetIndex() const
{
	return std::pair<int, int>(posTargetX, posTargetY);
}


//-------------------------------- draw ----------------------------------
// Draw the objects of the board.
//------------------------------------------------------------------------
void Board::draw(sf::RenderWindow& window)
{
	window.draw(m_background);

	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			if (m_pipes[i][j]) 
			{
				m_pipes[i][j]->draw(window);
			}
		}
	}

	for (auto i : m_emptyBlocks) {
		window.draw(i);
	}
}


//------------------------------ setPipes --------------------------------
// Set the pipes according to the following algorithm:
// 1.On matrix of chars ,which reprasant the pipes on the board, choose
//  'source' 'target'
// 2.Put the holes which pipes cant pass through
// 3.find route from 'source' to 'target'.
// 4.put the pipes according the route found.
// 5.put the unfilled pipes randomly.
//------------------------------------------------------------------------
void Board::setPipes()
{
	m_pipes.resize(mapSize);

	for (int i = 0; i < m_pipes.size(); i++)
	{
		m_pipes[i].resize(mapSize);
	}

	//Set the target and resource pipes.
	setTargetSource();

	//Set the route which solution route cant get through.
	setForbidenRoutes();

	//Find the route to get from source to target.
	findPathSourceTarget();

	//Set the solution pipe route.
	putPipesRoute();

	//Fill the rest of pipes with randoms.
	fillRandomsPipes();
}


//--------------------------- setTargetSource ----------------------------
// Set the target and source in the array which reprasent the current 
// map built up by random position.
//------------------------------------------------------------------------
void Board::setTargetSource()
{
	insertSource();

	insertTarget();
}


//--------------------------- setTargetSource ----------------------------
// Set the target and source in the array which reprasent the current 
// map built up by random position.
//------------------------------------------------------------------------
void Board::insertSource()
{
	int i = rand() % mapSize,
		j = rand() % mapSize;

	// Save the position of the source pipe.
	posSourceX = i;
	posSourceY = j;

	m_map[i][j] = 's';
}


//---------------------------- insertTarget ------------------------------
// Insert the target position and check the source is not positioned in
// the same position.
//------------------------------------------------------------------------
void Board::insertTarget()
{
	int i = rand() % mapSize,
		j = rand() % mapSize;

	while (true)
	{
		// Check the distance between source to targe is
		// above 1 in row and coulmn.
		if (m_map[i][j] != 's' && 
			(std::abs(float(posSourceX - i)) >= 1 && 
			(std::abs(float(posSourceY - j)) >= 1 )))
		{
			//Save the target pipe position.
			posTargetX = i;
			posTargetY = j;

			m_map[i][j] = 't';

			break;
		}
		else 
		{
			 i = rand() % mapSize,
			 j = rand() % mapSize;
		}
	}
}


//---------------------------- SetPipeStatus -----------------------------
// Sets the pipes current status.
// Runs over the pipes and sets them back to be as not connected to the 
// source pipe.
//------------------------------------------------------------------------
void Board::SetPipeStatus()
{
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			if (m_pipes[i][j])
			{
				m_pipes[i][j]->setConStatus(false);
				m_pipes[i][j]->SetTexture();
			}
		}
	}
}


//-------------------------- setForbidenRoutes ---------------------------
// Set blocked cells which the route solution is built witout them, this
// done to improve diversity.
//------------------------------------------------------------------------
void Board::setForbidenRoutes()
{

	int indexX,indexY,counter = 0;
	
	while (counter < BLOCKED_PATHS){

		indexX = rand() % mapSize;
		indexY = rand() % mapSize;

		if (m_map[indexX][indexY] != 't'&&
			m_map[indexX][indexY] != 's' &&
			m_map[indexX][indexY]  != 'x') {

			m_map[indexX][indexY] = 'x';
			counter++;
		}
	}
}


//------------------------- setEmptyMatrixCells --------------------------
// Clear the array which reprasant the pipes map used.
//------------------------------------------------------------------------
void Board::setEmptyMatrixCells() 
{
	m_map.clear();
	m_map.resize(mapSize);

	for (int i = 0; i < mapSize; i++)
	{
		m_map[i].resize(mapSize);
		for (int j = 0; j < mapSize; j++)
		{
			m_map[i][j] = '0';
		}
	}
}


//------------------------ findPathSourceTarget --------------------------
// Find the path between 'source' to 'target',if a route found, save the
// solution path in a deque,if not, try to find again a valid route.
//------------------------------------------------------------------------
void Board::findPathSourceTarget()
{

	while (!setRoute(posSourceX, posSourceY)) 
	{
		route.clear();

		setEmptyMatrixCells();

		setTargetSource();

		setForbidenRoutes();
	}

	std::cout << '\n';

	route.push_back(std::pair(posSourceX, posSourceY));
}


//-------------------------------- isSafe --------------------------------
// Checks boundaries.
//------------------------------------------------------------------------
bool Board::isSafe(const int i, const int j) const
{
	if (i >= 0 && i < mapSize && j >= 0 && j < mapSize)
	{
		return true;
	}

	return false;
}


//---------------------------- putPipesRoute ------------------------------
// Put the required pipes according to the route saved from source Pipe 
// to target Pipe.
// The function decide which pipe to put according to the current pipe
// position.
//------------------------------------------------------------------------
void Board::putPipesRoute() {

	putSourceTargetPipes();

	sf::Vector2f size = sf::Vector2f(pipeSize, pipeSize), position;

	auto previous = route.back();
	route.pop_back();
	auto current = route.back();
	
	while (route.size() >= 2)
	{
		route.pop_back();

		auto newPipe = route.back();

		position = sf::Vector2f
		(BOARD_WINDOW_POS_X + pipeSize * current.first,
			BOARD_WINDOW_POS_Y + pipeSize * current.second);

		if (m_pipes[current.first][current.second] == nullptr) 
		{
			if (newPipe.first == previous.first ||
				newPipe.second == previous.second)
			{
				// Put straight 'I' pipe.
				m_pipes[current.first][current.second] =
					std::make_shared<I_Pipe>(size, position,
						Resources::instance().
						getPipesObjectTextures(PIPE_I_NOT_CON),
						std::pair(current.first, current.second));

			}
			else 
			{
				// Put the 'L' Pipe
				m_pipes[current.first][current.second] =
					std::make_shared<L_Pipe>(size, position,
						Resources::instance().
						getPipesObjectTextures(PIPE_L_NOT_CON),
						std::pair(current.first, current.second));
			}
		}
		previous = current;
		current = newPipe;
	}

	// Set the target diraction according the last pipe connected.
	setTargetDirection(previous,current);
}


//------------------------- setTargetDirection ---------------------------
// Set the 'target' pipe direction according to the last
// pipe position.
//------------------------------------------------------------------------
void Board::setTargetDirection(std::pair<int, int>& pipe,
	std::pair<int, int>& target)
{
	auto entrances = m_pipes[posTargetX][posTargetY]->getEntrances();

	if (pipe.first < target.first && pipe.second == target.second)
	{
		m_pipes[posTargetX][posTargetY]->rotateRight();

	}
	else if (pipe.first > target.first && pipe.second == target.second)
	{
		m_pipes[posTargetX][posTargetY]->rotateLeft();
	}
	else if (pipe.first == target.first && pipe.second < target.second)
	{
		m_pipes[posTargetX][posTargetY]->rotateRight();
		m_pipes[posTargetX][posTargetY]->rotateRight();
	}
}


//------------------------ putSourceTargetPipes --------------------------
// Positions the source pipe.
//------------------------------------------------------------------------
void Board::putSourceTargetPipes()
{
	// Set the Source pipe object in the pipes matrix. 
	sf::Vector2f size = sf::Vector2f(pipeSize, pipeSize),
		position = sf::Vector2f
		(BOARD_WINDOW_POS_X + pipeSize * posSourceX,
			BOARD_WINDOW_POS_Y + pipeSize * posSourceY);
	
	m_pipes[posSourceX][posSourceY] = 
		(std::make_shared<SourcePipe>(size, position,
		Resources::instance().getPipesObjectTextures(PIPE_SRC),
		std::pair<int, int>(posSourceX, posSourceY)));

	//Set the Target pipe object in the pipes matrix. 
	position = sf::Vector2f(BOARD_WINDOW_POS_X + pipeSize * posTargetX,
		BOARD_WINDOW_POS_Y + pipeSize * posTargetY);

	m_pipes[posTargetX][posTargetY] = 
		(std::make_shared<TargetPipe>(size, position,
		Resources::instance().getPipesObjectTextures(PIPE_TAR),
		std::pair<int, int>(posTargetX, posTargetY)));
}


//-------------------------- fillRandomsPipes ----------------------------
// Fill the empty cells of pipes with rand pipes types.
//------------------------------------------------------------------------
void Board::fillRandomsPipes() 
{
	int randomPipe = rand() % 3;

	sf::Vector2f size,pos;
	
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++){

			size = sf::Vector2f(pipeSize, pipeSize);

			pos = sf::Vector2f( BOARD_WINDOW_POS_X + pipeSize * i,
							BOARD_WINDOW_POS_Y + pipeSize * j );

			if (m_pipes[i][j] == nullptr && m_map[i][j] != 'x' )
			{
				if ((unsigned int)i == posTargetX &&
					(unsigned int)j == posTargetY) {
					std::cout << " ";
				}
				switch (randomPipe)
				{
				case 0:
					// Insert Stright Pipe.
					m_pipes[i][j] = std::make_shared<I_Pipe>(size,pos,
						Resources::instance().
						getPipesObjectTextures(PIPE_I_NOT_CON),
						std::pair<int,int>(i,j));
					break;

				case 1:
					// Insert Right Angle Pipe.
					m_pipes[i][j] = std::make_shared<L_Pipe>(size, pos,
						Resources::instance().
						getPipesObjectTextures(PIPE_L_NOT_CON), 
						std::pair<int, int>(i, j));
					break;

				case 2:
					// Insert T Pipe.
					m_pipes[i][j] = std::make_shared<T_Pipe>(size, pos,
						Resources::instance().
						getPipesObjectTextures(PIPE_T_NOT_CON),
						std::pair<int, int>(i, j));
					break;

				}
			}
			else if(m_map[i][j] == 'x')
			{
				//Insert empty block.
				sf::RectangleShape emptyBlock{size};
				emptyBlock.setPosition(pos);
				emptyBlock.setTexture(Resources::instance().
					getPipesObjectTextures(EMPTY_PIPE));
				m_emptyBlocks.push_back(emptyBlock);
			}
			randomPipe = rand() % 3;
		}
	}
}


//------------------------ initializeAdjacencyList -----------------------
// Initializes the Adjacency List.
// Runs over the pipes and creates a linked list of neighbors for each
// existing vertex in the graph.
//------------------------------------------------------------------------
void Board::initializeAdjacencyList()
{
	for (auto i = 0; i < mapSize; i++)
	{
		for (auto j = 0; j < mapSize; j++)
		{
			if (m_pipes[i][j] != nullptr)
			{
				m_adjacencyList.insert(std::pair<std::pair<int, int>,
					std::list<std::shared_ptr<Pipe>>>
					(std::pair<int, int>(i, j),std::list 
						<std::shared_ptr<Pipe>>{}));

				// Insert the current vertex Adjacency List.
				insertNeighbors(i, j);
			}
		}
	}
}


//---------------------------- insertNeighbors ---------------------------
// Inserts the neighbors of a vertex into the linked list.
//------------------------------------------------------------------------
void Board::insertNeighbors(const int i, const int j)
{
	// Neighbor from above.
	if (i - 1 >= 0 && isNeighborExist(i - 1, j))
	{
		insertNeighbors({ i, j }, i - 1, j);
	}

	// Neighbor from below.
	if (size_t(i) + 1 < m_pipes.size() && isNeighborExist(i + 1, j)) 
	{
		insertNeighbors({ i, j }, i + 1, j); 
	}

	// Neighbor from left.
	if (j - 1 >= 0 && isNeighborExist(i, j - 1))
	{
		insertNeighbors({ i, j }, i, j - 1);
	}

	// Neighbor from right.
	if (j + 1 < mapSize && isNeighborExist(i, j + 1))
	{
		insertNeighbors({ i, j }, i, j + 1);
	}
}


//--------------------------- insertNeighbors ----------------------------
// Inserts the current neighbor into the linked list.
//------------------------------------------------------------------------
void Board::insertNeighbors(std::pair<int, int> mapIndex,
	const int i, const int j)
{
	m_adjacencyList[mapIndex].push_back(m_pipes[i][j]);
}


//--------------------------- isNeighborExist ----------------------------
// Returns if the current neighbors exists.
//------------------------------------------------------------------------
bool Board::isNeighborExist(const int i, const int j) const
{
	return m_pipes[i][j] != nullptr;
}


//------------------------------ setRoute --------------------------------
// Find the solution route from 's' to 't' for a valid route found, save
// the position in deque.
// The function use backtracking to pass on all valid diractions.
//------------------------------------------------------------------------
bool  Board::setRoute(const int IndexX,const int IndexY) 
{
	if (!isSafe(IndexX, IndexY)|| 
		m_map[IndexX][IndexY] == '1' || 
		m_map[IndexX][IndexY] == 'x'||
		m_map[IndexX][IndexY] == 'b') {
		return false;
	}

	if (m_map[IndexX][IndexY] == 't')
	{
		return true;
	}

	if (m_map[IndexX][IndexY] != 's' && m_map[IndexX][IndexY] != 't')
		m_map[IndexX][IndexY] = '1';

	if (setRoute(IndexX - 1, IndexY)) {
		route.push_back({ IndexX - 1, IndexY });
		return true;
	}

	if (setRoute(IndexX, IndexY + 1)) {
		route.push_back({ IndexX , IndexY + 1});
		return true;
	}

	if (setRoute(IndexX + 1, IndexY)) {
		route.push_back({ IndexX + 1, IndexY });
		return true;
	}

	if (setRoute(IndexX, IndexY - 1)) {
		route.push_back({ IndexX , IndexY -1});
		return true;
	}

	m_map[IndexX][IndexY] = 'b';
	return false;
}


//--------------------------- intilizeBoardMap ---------------------------
// Reset map and pipe sizes
//------------------------------------------------------------------------
void Board::intilizeBoardMap()
{
	mapSize = MAP_SIZE - 1;
	pipeSize = BOARD_WINDOW_HEIGHT / mapSize;
}


//------------------------------ getPipe ---------------------------------
// Return pipe in index (i,j).
//------------------------------------------------------------------------
Pipe& Board::getPipe(const int& i, const int& j)
{
	return *(m_pipes[i][j].get());
}


//-------------------------- getAdjacencyListAt --------------------------
// Return adjacency list of vertex (i,j).
//------------------------------------------------------------------------
std::list<std::shared_ptr<Pipe>>& Board::getAdjacencyListAt(const int& i,
	const int& j)
{
	return m_adjacencyList[{i, j}];
}
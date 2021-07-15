#pragma once

//--------------------------- Include section  ---------------------------
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include <deque>
#include <list>
#include <unordered_map>
#include "Pipe.h"
#include "Macros.h"


//---------------------------- Class Board -------------------------------
class Board
{
public:

	// C-tor
	Board();

	// Draw the objects of the board.
	void draw(sf::RenderWindow& window);

	// Return the map size.
	const int getMapSize() const;

	// Return index of source pipe.
	std::pair<int, int> getSourceIndex() const;

	// Return index of target pipe.
	std::pair<int, int> getTargetIndex() const;
	
	// Return adjacency list of vertex (i,j).
	std::list<std::shared_ptr<Pipe>>& 
		getAdjacencyListAt(const int&, const int&);

	// Load next stage.
	void nextStage();

	// Reset map and pipe sizes
	void intilizeBoardMap();

	// Return pipe in index (i,j).
	Pipe& getPipe(const int&, const int&);
	
	// Sets the pipes current status.
	void SetPipeStatus();

	// Return iterator to the begining of the vector that hold the pipes.
	std::vector<std::vector<std::shared_ptr<Pipe>>>::iterator pipesBegin();

	// Return iterator to the end of the vector that hold the pipes.
	std::vector<std::vector<std::shared_ptr<Pipe>>>::iterator pipesEnd();

private:

	// Set UI elemts on the board.
	void setBoardUI();

	// Set the pipes board.
	void setPipes();

	// Set the target and source pipes.
	void setTargetSource();

	// Insert source pipe.
	void insertSource();

	// Insert the Target pipe.
	void insertTarget();

	// Set the forbiden cells which solution route
	// wont pick.
	void setForbidenRoutes();

	// Fill the empty cells with '0'
	void setEmptyMatrixCells();

	// Find the route from source to target.
	void findPathSourceTarget();

	// Check if there are no issue with index i and j position.
	bool isSafe(const int, const int) const;

	// Set the route in deque.
	bool setRoute(const int, const int);

	// Put the right pipes on given route.
	void putPipesRoute();

	// Set the target diraction toward the last pipe.
	void setTargetDirection(std::pair<int, int>&, std::pair<int, int>&);

	// Positions the source pipe.
	void putSourceTargetPipes();

	// Fill the empty cells of pipes with rand pipes types.
	void fillRandomsPipes();

	// Initializes the Adjacency List.
	void initializeAdjacencyList();

	// Inserts the neighbors of a vertex into the linked list.
	void insertNeighbors(const int, const int);

	// Inserts the current neighbor into the linked list.
	void insertNeighbors(std::pair<int, int>, const int, const int);

	// Returns if the current neighbors exists.
	bool isNeighborExist(const int, const int) const;

	// Holds the sizes of data structures.
	int mapSize = MAP_SIZE,
		pipeSize = BOARD_WINDOW_HEIGHT / mapSize;

	// Background of the game.
	sf::RectangleShape m_background;

	// Solution route deque.
	std::deque<std::pair<int ,int>> route;

	unsigned int 
		posSourceX, posSourceY,			// index of source pipe.
		posTargetX, posTargetY;			// index of target pipe.

	// To hold the pipes of the game.
	std::vector<std::vector<std::shared_ptr<Pipe>>> m_pipes;

	// Adjacency List
	std::map<std::pair<int, int>, std::list<std::shared_ptr<Pipe>>>
		m_adjacencyList;

	std::vector<sf::RectangleShape> m_emptyBlocks;

	std::vector < std::vector<char >> m_map;
};
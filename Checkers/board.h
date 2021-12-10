#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum tiletype {
	black,
	white
};

class Board {
public:
	sf::RectangleShape tileShape; //board spaces 
	int boardH, boardW; //board width and height 
	int tileH, tileW; //tile width and height 
	//rows per tile and col
	int tilesPerRow;
	int tilesPerCol;
	//total number of tiles 
	int tileCount;
	std::vector<tiletype> tileTypes;
	int clickPos;
	bool newClick = false;
	bool pieceJumping = false;
	bool blockedTile = false;

	//overloaded constructor: dictates the  board height and width 
	Board(sf::RenderWindow &window, int height, int width, int tilesInRow, int tilesInCol);

	void drawBoard(sf::RenderWindow &window); //draws board
	//gets the position of the tile from index number (N)
	sf::Vector2f getTilePos(int N);
	//gets the index of the tile from the posiion
	int getTileN(float x, float y); 
};
#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include "game.h"

class Piece {
public:
	Board *boardref;
	Game *gameref;
	int position;
	int availableMoves;
	bool canMove;
	bool alive = true;
	bool selected = false;
	bool kinged = false;
	checkertype color;
	
	sf::CircleShape checkerShape;
	sf::CircleShape innerShape;
	sf::ConvexShape kingShape;
	sf::RectangleShape moveShape;

	//default constructor
	Piece();
	//overloaded constructor
	Piece(checkertype col, int pos, Board &bref, Game &gref);
	void drawPiece(sf::RenderWindow &window);
	void selectPiece(std::vector<Piece*> checkers);
	void placePiece(std::vector<Piece*> checkers);
	void update(std::vector<Piece*> checkers);
};
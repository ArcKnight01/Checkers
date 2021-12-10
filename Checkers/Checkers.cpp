// iD Tech Game Plan - SFML Template

// Include Needed for SFML
#include <SFML/Graphics.hpp>
// Include Needed for Animations
#include <SFML/Graphics/Rect.hpp>
// Include Needed for Text
#include <SFML/Graphics/Text.hpp>
#include "board.h"
#include "piece.h"
#include "game.h"
#include "stdafx.h"
using namespace sf;
/* DEFINE GAMESTATES HERE */

//constants here:
const int windowW = 800;
const int windowH = 800;
const int tilesPerRow = 8;
const int tilesPerCol = 8;

int main()
{

	// Create a Window to Display Graphics, Define Size and Window Name
	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Aidan's Checkers Game");

	/* CREATE OBJECTS AND ASSIGN OBJECT ATTRIBUTES HERE */
	Board GameBoard(window, windowW, windowH, tilesPerRow, tilesPerCol);

	/* DEFINE VARIABLES HERE */
	bool declareWinner = false;
	bool restart = false;

	int piecesPerTeam = (tilesPerRow / 2) * 3;
	Game  GameHandler(piecesPerTeam);

	//vector of pieces
	std::vector<Piece>checker;
	//vector of pointers to pieces
	std::vector<Piece*>checkerPtr;

	//add pieces to the vector
	int spawnPos;
	for (int i = 0; i < piecesPerTeam; i++) {
		spawnPos = (2 * i + 1) - (i / (tilesPerRow / 2)) % 2;
		checker.push_back(Piece(redteam, spawnPos, GameBoard, GameHandler));
		checker.push_back(Piece(whiteteam, (GameBoard.tileCount-1)-spawnPos, GameBoard, GameHandler));
	}

	for (Piece& p : checker) {
		checkerPtr.push_back(&p);
	}

	// Run the Program while the Window is Open
	while (window.isOpen())
	{	
		//reset game loop items
		window.clear();
		GameBoard.newClick = false;

		sf::Event event;
		while (window.pollEvent(event))
		{
			// When X Button Clicked, Close Window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::R) {
					restart = true;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::R) {
					restart = false;
				}
			}
			/* DEFINE EVENTS (i.e. KEY PRESS & RELEASE) HERE */
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					//Register a new mouse click for piece selection functions
					GameBoard.newClick = true;
					//Find the tile that was clicked in
					GameBoard.clickPos = GameBoard.getTileN(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					// the position of mouse
				}
			}
		}

		/* DEFINE ACTIONS (i.e. MOVEMENT) HERE */

		/* DRAW OBJECTS HERE */

		//first draw the checkers board:
		GameBoard.drawBoard(window);
		//draw turnindicator in top left corner
		GameHandler.drawTurn(window);

		if (restart) {
			//reset board & checkers
			restart = false;
			
		}

		//Iterate through all checker pieces (checker.size is the amount of checkers)
		for (int i = 0; i < checker.size(); i++) { 
			checker[i].update(checkerPtr); //update each piece
			checker[i].drawPiece(window); //draw each piece
			if (checker[i].alive == false) {
				declareWinner = GameHandler.losePiece(checker[i].color);
				checker.erase(checker.begin() + i);
			}
		}
		//Display message if losePiece returns true
		if (declareWinner) {
			GameHandler.drawVictory(window);
		}
			
		window.display();

	}
	return 0;
}
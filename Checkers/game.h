#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
//this class controls the game flow 

const int playerCount = 2;

//different teams
enum checkertype {
	redteam,
	whiteteam
};

class Game {
public:
	int playerTurn = 0;
	sf::RectangleShape turnIndicator; //red or white depending on whose turn it is
	checkertype turncolor;
	int pieceTotal[playerCount]; //array that keeps track of total pieces

	std::string victoryMsg[playerCount];
	sf::Text victoryText;
	sf::Font victoryFont;

	Game(int startingPieces);
	void changeTurn(); //exchange turns
	void drawTurn(sf::RenderWindow& window);
	void drawVictory(sf::RenderWindow& window); //draw victory window
	bool losePiece(checkertype color); //allow piece to go away

};
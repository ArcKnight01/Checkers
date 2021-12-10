#include "game.h" 
#include "stdafx.h"


Game::Game(int startingPieces) {
	for (int i = 0; i < playerCount; i++) {
		pieceTotal[i] = startingPieces;
	}

	//victory message
	victoryFont.loadFromFile("Assets/arial.ttf");
	victoryText.setFont(victoryFont);
	victoryText.setFillColor(sf::Color::Green);
	victoryText.setOutlineColor(sf::Color::Black);
	victoryText.setOutlineThickness(2.f);
	victoryText.setOrigin(0, 0);
	victoryText.setPosition(275, 350);
	victoryText.setCharacterSize(60);
	//victoryMsg[0] = "Red wins!";
	//victoryMsg[1] = "White wins!";
	victoryMsg[1] = "Red wins!";
	victoryMsg[0] = "White wins!"; // this 2 are correct bc message goes when red loses all pieces

	//red turn indicator, size ({50, 50}), 
	//position (25,25) , outline color black, thickness (3.f)
	
	//turn indicator
	turnIndicator.setFillColor(sf::Color::Red);
	turnIndicator.setSize({ 50,50 });
	turnIndicator.setPosition({ 25,25 });
	turnIndicator.setOutlineColor(sf::Color::Black);
	turnIndicator.setOutlineThickness(3.f);
	turncolor = redteam;
}
void Game::changeTurn() {
	//Increment the turn and loop around when it passes the player count
	playerTurn++;
	if (playerTurn >= playerCount) {
		playerTurn = 0;
	}
	switch (playerTurn) {
	case 0:
		turncolor = redteam;
		turnIndicator.setFillColor(sf::Color::Red);
		break;
	case 1:
		turncolor = whiteteam;
		turnIndicator.setFillColor(sf::Color::White);
		break;
	}
}

void Game::drawTurn(sf::RenderWindow& window) {
	window.draw(turnIndicator);
	
}
void Game::drawVictory(sf::RenderWindow& window){
	window.draw(victoryText);
}
bool Game::losePiece(checkertype color) {
	//remove a piece from the player's total and check if that total becomes zero:
	pieceTotal[color]--;
	if (pieceTotal[color] == 0) {
		victoryText.setString(victoryMsg[color]); //0 is red team. 1 is white team
		return true;
	}
	return false;
}

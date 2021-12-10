#include "stdafx.h"
#include "piece.h"

Piece::Piece() {}

Piece::Piece(checkertype col, int pos, Board &bref, Game &gref) {
	color = col;
	position = pos;
	boardref = &bref;
	gameref = &gref;
	
	
	
	
	
	if (color == whiteteam) {
		checkerShape.setFillColor(sf::Color::White);
		innerShape.setFillColor(sf::Color(225, 225, 255));
		kingShape.setFillColor(sf::Color(225, 225, 255));
	}
	else {
		checkerShape.setFillColor(sf::Color::Red);
		innerShape.setFillColor(sf::Color(200, 0, 0));
		kingShape.setFillColor(sf::Color(200, 0, 0));
	}
	checkerShape.setOutlineColor(sf::Color::Green);
	checkerShape.setOutlineThickness(0.f);
	checkerShape.setRadius(boardref->tileW *0.4);
	checkerShape.setOrigin(-boardref->tileW * 0.1, -boardref->tileH * 0.1);

	innerShape.setOutlineThickness(0.f);
	innerShape.setRadius(boardref->tileW * 0.3);
	innerShape.setOrigin(-boardref->tileW * 0.2, -boardref->tileH * 0.2);

	kingShape.setPointCount(7);
	kingShape.setPoint(0, sf::Vector2f(0, 0));
	kingShape.setPoint(1, sf::Vector2f(0, 75));
	kingShape.setPoint(2, sf::Vector2f(100, 75));
	kingShape.setPoint(3, sf::Vector2f(100, 0));
	kingShape.setPoint(4, sf::Vector2f(75, 50));
	kingShape.setPoint(5, sf::Vector2f(50, 0));
	kingShape.setPoint(6, sf::Vector2f(25, 50));
	//kingShape.setOrigin(-boardref->tileW * 0.4, -boardref->tileH * 0.4);
	kingShape.setOrigin(-boardref->tileW * 0.825, -boardref->tileH * 1);
	kingShape.setScale(0.375, 0.375);

	moveShape = sf::RectangleShape(sf::Vector2f(boardref->tileW, boardref->tileH));
	moveShape.setFillColor(sf::Color::Black);
	//moveShape.setOrigin(-boardref->tileW, -boardref->tileH);
	//moveShape.setSize(sf::Vector2f(boardref->tileW, boardref->tileH));

}
//other functions:
void Piece::drawPiece(sf::RenderWindow& window) {
	moveShape.setPosition(boardref->getTilePos(position));
	window.draw(moveShape);

	checkerShape.setPosition(boardref->getTilePos(position));
	window.draw(checkerShape);
	innerShape.setPosition(boardref->getTilePos(position));
	window.draw(innerShape);
	kingShape.setPosition(boardref->getTilePos(position));
	window.draw(kingShape);
	
}
void Piece::selectPiece(std::vector<Piece*> checkers) {
	bool moveAvailable = false;
	bool possibleJump;
	bool jumpAvailable;
	bool blocked = false;
	if (color == gameref-> turncolor && boardref->pieceJumping == false && selected == false && boardref->clickPos == position && boardref->newClick == true){
		selected = true;
		//if selected then change outline color to green:
		checkerShape.setOutlineColor(sf::Color::Green);
		checkerShape.setOutlineThickness(8.f);
		int upAndLeftPos = position - boardref->tilesPerRow - 1;
		int upAndRightPos = position - boardref->tilesPerRow + 1;
		int jumpUpLeft = position - (boardref->tilesPerRow - 1) * 2;
		int jumpUpRight = position - (boardref->tilesPerRow + 1) * 2;
		int downAndLeftPos = position + boardref->tilesPerRow - 1;
		int downAndRightPos = position + boardref->tilesPerRow + 1;
		int jumpDownLeft = position + (boardref->tilesPerRow - 1) * 2;
		int jumpDownRight = position + (boardref->tilesPerRow + 1) * 2;
	}
	else if (selected == true && boardref->clickPos == position && boardref->newClick == true) {
		//if already selected unselect, and remove green outline
		checkerShape.setOutlineThickness(0.f);
		selected = false;
		//if piece is clicked after piece has jumped: change turn
		if (boardref->pieceJumping == true) {
			//player can choose to end their turn after jumping a piece
			gameref->changeTurn();
		}
		boardref->pieceJumping = false;
	}
}
void Piece::placePiece(std::vector<Piece*> checkers) {
	int upAndLeftPos = position - boardref->tilesPerRow - 1;
	int upAndRightPos = position - boardref->tilesPerRow + 1;
	int jumpUpLeft = position - (boardref->tilesPerRow - 1) * 2;
	int jumpUpRight = position - (boardref->tilesPerRow + 1) * 2;
	int downAndLeftPos = position + boardref->tilesPerRow - 1;
	int downAndRightPos = position + boardref->tilesPerRow + 1;
	int jumpDownLeft = position + (boardref->tilesPerRow - 1) * 2;
	int jumpDownRight = position + (boardref->tilesPerRow + 1) * 2;
	//place a piece if the next click is in a valid location
	if (selected == true && boardref->clickPos != position) { //if the piece is selected and click position is not the same as the piece's current position then:
		//Check all pieces to see if one of them is blocking the new click position
		bool pieceBlocked = false;
		//loop through all pieces to see if any of them is blocking the next click
		for (Piece* checker : checkers) {
			if (boardref->clickPos == checker->position && checker->alive) { //if the click position equals the position of another checker (occupied) and that checker is alive
				checkerShape.setOutlineColor(sf::Color::Magenta);
				pieceBlocked = true;
				break;
			}
		}
		//piece is not blocked and the tile is black
		if (pieceBlocked == false && boardref->tileTypes[boardref->clickPos] == black) {
			//click position is not occupied and tile color is black
			
			if (color == redteam && kinged == false) {

				//red piece moves down board:
				if (boardref->pieceJumping == false && (boardref->clickPos == position + boardref->tilesPerRow - 1 || boardref->clickPos == position + boardref->tilesPerRow + 1)) { //position is left or right one tile away
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false;
					//End of turn
					gameref->changeTurn();
				}
				//Red jumps down and left
				if (boardref->clickPos == position + (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow - 1) == checker->position && checker->color == whiteteam) {
							//Enemy piece is being jumped over
							//checkerShape.setOutlineColor(sf::Color::Cyan);
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					//For jumping pieces, reusing the same pieceBlocked variable to check if there was actually an enemy piece to jump over
					if (pieceBlocked == true) {
						//Valid position, jumped
						checkerShape.setOutlineColor(sf::Color::Blue);
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//Red jumps down and right
				if (boardref->clickPos == position + (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow + 1) == checker->position && checker->color == whiteteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						checkerShape.setOutlineColor(sf::Color::Blue);
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//king a piece if it reaches the other side
				if (position >= boardref->tileCount - boardref->tilesPerRow) {
					kinged = true;
					//checkerShape.setFillColor(sf::Color(255, 0, 0));
					checkerShape.setFillColor(sf::Color(200, 0, 0));
					innerShape.setFillColor(sf::Color::Red);
					kingShape.setFillColor(sf::Color(200, 0, 0));
				}
			} 
			//white team:
			else if (color == whiteteam && kinged == false) {
				//white piece moves up board
				if (boardref->pieceJumping == false && (boardref->clickPos == position - boardref->tilesPerRow - 1 || boardref->clickPos == position - boardref->tilesPerRow + 1)) {
					//valid move position, no jumping
					position = boardref->clickPos;
					checkerShape.setOutlineThickness(0.f);
					selected = false;
					//end of turn:
					gameref->changeTurn();
				}

				//up and left
				if (boardref->clickPos == position - (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow + 1) == checker->position && checker->color == redteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						checkerShape.setOutlineColor(sf::Color::Blue);
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//White jumps up and right
				if (boardref->clickPos == position - (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow - 1) == checker->position && checker->color == redteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						checkerShape.setOutlineColor(sf::Color::Blue);
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//king a piece if it reaches the other side
				if (position < boardref->tilesPerRow) { //used to be <= (testing)
					kinged = true;
					checkerShape.setFillColor(sf::Color(200, 200, 255));
					innerShape.setFillColor(sf::Color::White);
					kingShape.setFillColor(sf::Color(225, 225, 255));
				}
			}
			else if (kinged == true) {
				if (boardref->pieceJumping == false && (boardref->clickPos == position - boardref->tilesPerRow - 1 || boardref->clickPos == position - boardref->tilesPerRow + 1
					|| boardref->clickPos == position + boardref->tilesPerRow - 1 || boardref->clickPos == position + boardref->tilesPerRow + 1)) {
					
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false; //used to be == (possible error)
					//turn ends
					gameref->changeTurn();
				}
				//up and left, up and right( pasted from white team)

				//up and left
				if (boardref->clickPos == position - (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow + 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King jumps up and right
				if (boardref->clickPos == position - (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow - 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}

				//down and left
				if (boardref->clickPos == position + (boardref->tilesPerRow - 1) * 2) {
					//check for valid jump
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow - 1) == checker->position && checker->color != color) {
							//enemy piece is being jumped
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//valid position jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}

				//down and right
				if (boardref->clickPos == position + (boardref->tilesPerRow + 1) * 2) {
					//check if jump is valid 
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow + 1) == checker->position && checker->color != color) {
							//enemy piece is being jumped
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
			}
		}
		//clicked location that is open but cannot be moved to 
		//jumping pieces must jump again or end turn (by clicking on piece)
		else if (boardref->pieceJumping == false) {
			//if clicked location isn't the checker piece's current location && is currently selected && hasn't just jumped 
			//unselect the current piece
			checkerShape.setOutlineThickness(0.f);
			selected = false;
			//temporarily (debugging purposes) set fill color of moveShape to yellow.
			if (pieceBlocked) {
				moveShape.setFillColor(sf::Color::Color(150, 0, 0, 200));
			}
			else if (boardref->tileTypes[boardref->clickPos] != black) {
				moveShape.setFillColor(sf::Color::White);
			}
			if (boardref->pieceJumping == true) {
				moveShape.setFillColor(sf::Color::Cyan);
			}
		}
	}
}
void Piece::update(std::vector<Piece*> checkers) {
	selectPiece(checkers);
	placePiece(checkers);
}
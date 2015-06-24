/****************************************************/
/*                                                  */
/* Date Created: 01/12/14                           */
/* Description: Implementation of ChessPiece        */
/*              abstract class.                     */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141201  HL   Created.                          */
/****************************************************/

#include <string>
#include "ChessPiece.hpp"

ChessPiece::~ChessPiece(){
  return;
}

std::string ChessPiece::getColour() const {
  if (colour == WHITE) {
    return "White";
  }
  return "Black";
}



bool ChessPiece::clearRoute(int source_index, int destination_index,
			    move_type direction,
			    ChessPiece *board[]) {
  if (destination_index > source_index) {
    for (int i = source_index + direction; i < destination_index; i+=direction) {
      if (board[i] != NULL) {
	return false;
      }
    }
  }
  else {
    for (int i = source_index + direction; i > destination_index; i+=direction) {
      if (board[i] != NULL) {
	return false;
      }
    }
  }
  return true;
}

bool ChessPiece::hasMoved() {
  return has_moved;
}

void ChessPiece::setMove() {
  has_moved = true;
  return;
}


bool ChessPiece::hasSpecialMoves() {
  return has_special_moves;
}


int ChessPiece::getMoveMultiple(move_type direction) {
  return MAX_MULTIPLE;
}


bool ChessPiece::hasCaptureMove(move_type moves[], int &number_of_moves) {
  return false;
}


bool ChessPiece::validMove(int source_index, int destination_index, 
			   ChessPiece *board[]) {
  
  move_type capture_moves[MAX_MOVES];
  int number_of_capture_moves;
  int steps;

  if(board[destination_index] != NULL && 
     board[destination_index]->getColour() == this->getColour())
    return false;


  for (int i = 0; i < number_of_moves; i++) {
    steps = getMoveMultiple(moves[i]);
    if ((destination_index - source_index) % moves[i] == 0 && 
	(destination_index - source_index) / moves[i] > 0 &&
	(destination_index - source_index) / moves[i] <= steps) {
      if(hasCaptureMove(capture_moves, number_of_capture_moves) &&
	 board[destination_index] != NULL) {
	break;
      }

      if(clearRoute(source_index, destination_index, moves[i], board))
	return true;
      return false;
    }
  }
  if(hasCaptureMove(capture_moves, number_of_capture_moves) &&
     board[destination_index] != NULL &&
     board[destination_index]->getColour() != this->getColour()) {
    for (int i = 0; i < number_of_capture_moves; i++) {
      if((destination_index - source_index) == capture_moves[i]) {
	return true;
      }
    }
  }
  return false;
}

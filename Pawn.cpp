/****************************************************/
/*                                                  */
/* Date Created: 01/12/14                           */
/* Description: Implementation of Pawn class.       */
/*              A pawn is a ChessPiece              */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141201  HL   Created.                          */
/****************************************************/

#include <string>
#include<cstdlib>

#include "Pawn.hpp"

using namespace std;

Pawn::Pawn(colours _colour) {
  colour = _colour;
  if(colour == WHITE) {
    moves[0] = NORTH;
  }
  else {
    moves[0] = SOUTH;
  }
  number_of_moves = 1;
  has_special_moves = true;
}

Pawn::~Pawn() {
  return;
}


int Pawn::getMoveMultiple(move_type direction) {
  if (has_moved) 
    return 1;

  if (direction == NORTH || direction == SOUTH)
    return 2;

  return 1;
}


bool Pawn::hasCaptureMove(move_type capture_moves[], 
			  int &number_of_capture_moves) {
  if(colour == WHITE) {
    capture_moves[0] = NORTH_WEST;
    capture_moves[1] = NORTH_EAST;
  }
  else {
    capture_moves[0] = SOUTH_WEST;
    capture_moves[1] = SOUTH_EAST;
  }
  number_of_capture_moves = 2;
  return true;
}


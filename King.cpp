/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Implementation of King class.       */
/*              A king is a ChessPiece              */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/

#include <string>
#include <cstdlib>

#include "King.hpp"

using namespace std;

King::King(colours _colour) {
  colour = _colour;
  moves[0] = NORTH;
  moves[1] = NORTH_EAST;
  moves[2] = EAST;
  moves[3] = SOUTH_EAST;
  moves[4] = SOUTH;
  moves[5] = SOUTH_WEST;
  moves[6] = WEST;
  moves[7] = NORTH_WEST;
  number_of_moves = 8;
}

King::~King() {
  return;
}

int King::getMoveMultiple(move_type direction) {
  if(has_moved)
    return 1;

  if (direction == EAST || direction == WEST)
    return 2;

  return 1;
}

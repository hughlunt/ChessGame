/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Implementation of Knight class.     */
/*              A knight is a ChessPiece            */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/

#include <string>
#include <cstdlib>
#include "Knight.hpp"

using namespace std;

Knight::Knight(colours _colour) {
  colour = _colour;
  moves[0] = SOUTH_SOUTH_WEST;
  moves[1] = SOUTH_SOUTH_EAST;
  moves[2] = WEST_SOUTH_WEST;
  moves[3] = EAST_SOUTH_EAST;
  moves[4] = WEST_NORTH_WEST;
  moves[5] = EAST_NORTH_EAST;
  moves[6] = NORTH_NORTH_WEST;
  moves[7] = NORTH_NORTH_EAST;
  number_of_moves = 8;
}

Knight::~Knight() {
  return;
}

int Knight::getMoveMultiple(move_type direction) {
  return 1;
}

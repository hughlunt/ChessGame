/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Implementation of Bishop class.     */
/*              A bishop is a ChessPiece            */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/

#include <string>
#include<cstdlib>

#include "Bishop.hpp"

using namespace std;

Bishop::Bishop(colours _colour) {
  colour = _colour;
  moves[0] = NORTH_WEST;
  moves[1] = NORTH_EAST;
  moves[2] = SOUTH_WEST;
  moves[3] = SOUTH_EAST;
  number_of_moves = 4;
}

Bishop::~Bishop() {
  return;
}

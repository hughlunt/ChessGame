/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Implementation of Rook class.       */
/*              A rook is a ChessPiece              */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/

#include <string>
#include <cstdlib>

#include "Rook.hpp"

using namespace std;

Rook::Rook(colours _colour) {
  colour = _colour;
  moves[0] = NORTH;
  moves[1] = SOUTH;
  moves[2] = EAST;
  moves[3] = WEST;
  number_of_moves = 4;

}

Rook::~Rook() {
  return;
}

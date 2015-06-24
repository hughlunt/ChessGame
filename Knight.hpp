/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Definition of Knight class.         */
/*              A knight is a ChessPiece            */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/
#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.hpp"

class Knight: public ChessPiece {

public:
  Knight (colours _colour);
  ~Knight();

  // Returns the number of steps each piece can make in a direction
  int getMoveMultiple(move_type direction);

  // Return the name of a piece.
  std::string getName() const {
    return "Knight";
  }

};

#endif

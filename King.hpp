/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Definition of King class.           */
/*              A king is a ChessPiece              */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/
#ifndef KING_H
#define KING_H

#include "ChessPiece.hpp"

class King: public ChessPiece {

public:
  King (colours _colour);
  ~King();

  // Returns the number of steps each piece can make in a direction
  int getMoveMultiple(move_type direction);

  // Return the name of a piece.
  std::string getName() const {
    return "King";
  }

};

#endif

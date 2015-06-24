/****************************************************/
/*                                                  */
/* Date Created: 01/12/14                           */
/* Description: Definition of Pawn class.           */
/*              A pawn is a ChessPiece              */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141201  HL   Created.                          */
/****************************************************/
#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.hpp"

class Pawn: public ChessPiece {

public:
  Pawn (colours _colour);
  ~Pawn();

  // Returns the number of steps each piece can make in a direction
  int getMoveMultiple(move_type direction);

  // Returns true if a piece has a capture move that allows it to move
  // in a direction it would not normally be allowed to move in.
  bool hasCaptureMove(move_type moves[], int &number_of_moves);

  // Return the name of a piece.
  std::string getName() const {
    return "Pawn";
  }

};

#endif

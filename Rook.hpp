/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Definition of Rook class.           */
/*              A rook is a ChessPiece              */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/
#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.hpp"

class Rook: public ChessPiece {

public:
  Rook (colours _colour);
  ~Rook();

  // Return the name of a piece.
  std::string getName() const {
    return "Rook";
  }

};

#endif

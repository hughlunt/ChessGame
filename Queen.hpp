/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Definition of Queen class.          */
/*              A queen is a ChessPiece             */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/
#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.hpp"

class Queen: public ChessPiece {

public:
  Queen (colours _colour);
  ~Queen();

  // Return the name of a piece.
  std::string getName() const {
    return "Queen";
  }

};

#endif

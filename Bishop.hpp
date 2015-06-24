/****************************************************/
/*                                                  */
/* Date Created: 02/12/14                           */
/* Description: Definition of Bishop class.         */
/*              A bishop is a ChessPiece            */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141202  HL   Created.                          */
/****************************************************/
#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.hpp"

class Bishop: public ChessPiece {

public:
  Bishop (colours _colour);
  ~Bishop();

  // Return the name of a piece.
  std::string getName() const {
    return "Bishop";
  }
};

#endif

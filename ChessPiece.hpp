/****************************************************/
/*                                                  */
/* Date Created: 01/12/14                           */
/* Description: Definition of ChessPiece abstract   */
/*              class.                              */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141201  HL   Created.                          */
/****************************************************/
#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include<string>

class ChessPiece {

public:
  ChessPiece(){
    has_moved = false;
    has_special_moves = false;
}

  virtual ~ChessPiece() =0;

  enum colours {WHITE, BLACK} colour;

  // Return the colour (Black or White) of a piece.
  std::string getColour() const;

  // Return True if the move from source_index to destination_index is valid
  // Return false if it is not.
  bool validMove(int source_index, int destination_index, 
			 ChessPiece *board[]);

  // Return the name of a piece.
  virtual std::string getName() const=0;

  // Return true if a piece has moved, false otherwise
  bool hasMoved();

  // Change the has_moved attribute to true.
  void setMove();

  // Return true if the piece has special moves i.e a capture or promotion move
  bool hasSpecialMoves();

  enum move_type{SOUTH_SOUTH_WEST = -33, SOUTH_SOUTH_EAST = -31,
		 WEST_SOUTH_WEST = -18, SOUTH_EAST, SOUTH, SOUTH_WEST, 
		 EAST_SOUTH_EAST, 
		 EAST = -1, WEST = 1,
		 WEST_NORTH_WEST = 14, NORTH_WEST, NORTH, NORTH_EAST,
		 EAST_NORTH_EAST, 
		 NORTH_NORTH_WEST = 31, NORTH_NORTH_EAST = 33}; 

protected:

  static const int BOARD_WIDTH = 8;
  static const int MAX_MOVES = 8;
  static const int MAX_MULTIPLE = 7;

  bool has_moved;
  bool has_special_moves;
  move_type moves[MAX_MOVES];
  int number_of_moves;

  // True if there are no pieces blocking a move from source_index to
  // destination_index in index increments of direction.
  // Returns false if there is a piece in the way  
  bool clearRoute(int source_index, int destination_index, 
		  move_type direction,
		  ChessPiece *board[]);

  // Returns the number of steps each piece can make in a direction
  virtual int getMoveMultiple(move_type direction);

  // Returns true if a piece has a capture move that allows it to move
  // in a direction it would not normally be allowed to move in.
  virtual bool hasCaptureMove(move_type moves[], int &number_of_moves);

};

#endif

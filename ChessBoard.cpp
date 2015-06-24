/****************************************************/
/*                                                  */
/* Date Created: 01/12/14                           */
/* Description: Implementation of ChessBoard class. */
/*              Sets up board and revieces moves    */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141201  HL   Created.                          */
/****************************************************/

#include<iostream>
#include<string>
#include<cstdlib>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Queen.hpp"

using namespace std;



ChessBoard::ChessBoard() {
  cout << "A new chess game is started!\n";
  setupBoard();
  return;
}



ChessBoard::~ChessBoard() {
  clearBoard();
  return;
}



static const std::string WHITE = "White";
static const std::string BLACK = "Black";



void ChessBoard::submitMove(string source_square, string destination_square){

  // Is the game alive?
  if (!game_alive) {
    cout << "This game has ended.\n";
    return;
  }

  // Are the inputs valid?
  if (!validSquare(source_square) || !validSquare(destination_square)) {
    return;
  }

  // Convert to array indicies
  int source_index = squareToIndex(source_square);
  int destination_index = squareToIndex(destination_square);

  // Return if there's not piece or the incorrect piece is moved.
  if (noPiece(source_index, source_square) || !myTurn(source_index)) {
    return;
  }


  // Return if this move is not valid
  if (!board[source_index]->validMove(source_index, 
				      destination_index, board) || 
      !safeToMove(source_index, destination_index)) {
  
    cout << board[source_index]->getColour() << "'s ";
    cout << board[source_index]->getName() << " cannot move to ";
    cout << destination_square << "!\n";
    return;
  }
  
  // Check for castle move
  if((source_index == white_king_index || 
      source_index == black_king_index) &&
     abs(source_index - destination_index) == 2) {

    if(!validCastle(source_index, destination_index)) { 
      cout << board[source_index]->getColour() << "'s ";
      cout << board[source_index]->getName() << " cannot move to ";
      cout << destination_square << "!\n";
      return;
    }

    // Need to move the Rook as well as the king...
    //Move the rook...
    moveCastlingRook(source_index, destination_index);
  }
    
  movePiece(source_index, destination_index);
  
  // Check if pawn should be promoted
  checkPawnPromotion(destination_index);

  // Is the opponent in check
  checkForCheck(destination_index);

  // Flag this piece as having moved
  board[destination_index]->setMove();
  
  // If 50 moves have taken place, without pawn move or
  // capture of piece, then draw game.
  // A move is one go each, so 100 calls here.
  if (fifty_move_draw_count == 100) {
    cout << "Fifty moves have occured without a capture or pawn move.\n";
    cout << "Game drawn\n";
    game_alive = false;
  }

  turn = (turn == WHITE ? BLACK : WHITE);
  return;
}



void ChessBoard::movePiece(int source_index, int destination_index) {
 
  cout << board[source_index]->getColour() << "'s ";
  cout << board[source_index]->getName();
  cout << " moves from " << indexToSquare(source_index) << " to ";
  cout << indexToSquare(destination_index);

  if(board[source_index]->hasSpecialMoves()) {
    fifty_move_draw_count = 0;
  }
  else {
    fifty_move_draw_count += 1;
  }

  if(board[destination_index] != NULL) {
    cout << " taking " << board[destination_index]->getColour() << "'s ";
    cout << board[destination_index]->getName();
    delete board[destination_index];
    fifty_move_draw_count = 0;
  }
  cout << endl;

  if (source_index == white_king_index) {
    white_king_index = destination_index;
  }
  if (source_index == black_king_index) {
    black_king_index = destination_index;
  }

  board[destination_index] = board[source_index];
  board[source_index] = NULL;

  if (!board[destination_index]->hasMoved()) {
    board[destination_index]->setMove();
  }

  move_counter += 1;
}



void ChessBoard::clearBoard() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i] != NULL) { 
      delete board[i];
      board[i] = NULL;
    }
  }
  game_alive = false;
}



void ChessBoard::resetBoard() {
  clearBoard();
  setupBoard();
  return;
}



void ChessBoard::setupBoard() {

  for (int i = 0; i < BOARD_SIZE; i ++) {

    switch (i/BOARD_WIDTH) {

    case 0:
	
      switch (i % BOARD_WIDTH) {
      
      case 0:
      case 7:
	board[i] = new Rook(ChessPiece::WHITE);
	break;
      case 1:
      case 6:
	board[i] = new Knight(ChessPiece::WHITE);
	break;
      case 2:
      case 5:
	board[i] = new Bishop(ChessPiece::WHITE);
	break;
      case 3:
	board[i] = new Queen(ChessPiece::WHITE);
	break;
      default:
	board[i] = new King(ChessPiece::WHITE);
	white_king_index = i;
	break;
      }
      
      break; 
      
    case 2:
      board[i] = new Pawn(ChessPiece::WHITE);
      break;
      
    case 12:
      board[i] = new Pawn(ChessPiece::BLACK);
      break;
      
    case 14:

      switch (i % BOARD_WIDTH) {
      case 0:
      case 7:
	board[i] = new Rook(ChessPiece::BLACK);
	break;
      case 1:
      case 6:
	board[i] = new Knight(ChessPiece::BLACK);
	break;
      case 2:
      case 5:
	board[i] = new Bishop(ChessPiece::BLACK);
	break;
      case 3:
	board[i] = new Queen(ChessPiece::BLACK);
	break;
      default:
	board[i] = new King(ChessPiece::BLACK);
	black_king_index = i;
	break;
      }     

      break;
      
    default:
      board[i] = NULL;   
    }
  }
  turn = WHITE;
  game_alive = true;
  return;
}



int ChessBoard::squareToIndex(string square) {
  //Get rank index (given 128 array, rank index is 16(n-1)
  rank = ChessPiece::NORTH * ((square.at(1) - INT_ASCII_OFFSET) - 1) ; 
  // File index is ASCII code of character - ASCII_offset of value
  file = toupper(square.at(0)) - ASCII_OFFSET;
  return (rank + file);
}



string ChessBoard::indexToSquare(int index) {
  string square;
  rank = (index/ChessPiece::NORTH) + 1;
  char char_file = (index % ChessPiece::NORTH) + ASCII_OFFSET; 
  char char_rank = rank + INT_ASCII_OFFSET;
  square.clear();
  square.push_back(char_file);
  square.push_back(char_rank);
  return square;
}


bool ChessBoard::validSquare(string square) {

  if (square.length() != SQUARE_LENGTH) {
    cout << "ERROR: Square length must be " << SQUARE_LENGTH << ".\n\n";
    return false;
  }

  if (toupper(square.at(0)) > ASCII_MAX || toupper(square.at(0)) < ASCII_OFFSET) {
    cout << "ERROR: " << square.at(0) << " is not a valid file.\n\n";
    return false;
  }

  if ((square.at(1) - INT_ASCII_OFFSET) > BOARD_WIDTH || 
      (square.at(1)-INT_ASCII_OFFSET) <= 0) {
    cout << "ERROR: " << square.at(1) << " is not a valid rank.\n\n";
    return false;
  }

  return true;
}



bool ChessBoard::isAttacked(int target, string colour, vector <int> &attacker) {
  attacker.clear();
  for (int i = 0; i < BOARD_SIZE; i++) {
    if ((i & 0x88) == 0 &&  // Square is on board
	board[i] != NULL &&  // Piece occupues square
	board[i]->getColour() == colour && // same colour
	board[i]->validMove(i, target, board)) { // Can capture square
      attacker.push_back(i);
    }
  }
  if(attacker.size() > 0) 
    return true;

  return false;
}



bool ChessBoard::noPiece(int source_index, string source_square) {
  if (board[source_index] == NULL) {
    cout << "There is no piece at position " << source_square << "!\n";
    return true;
  }
  return false;
}



bool ChessBoard::myTurn(int source_index) {
  if (board[source_index]->getColour() != turn) {
    cout << "It is not " << board[source_index]->getColour();
    cout << "'s turn to move!\n";
    return false;
  }
  return true;
}



bool ChessBoard::selfCheck(string colour) {
  vector <int> attacker;
  int target;
  string attacked_by;

  if (colour == BLACK) {
    target = black_king_index;
    attacked_by = WHITE;
  }
  else {
    target = white_king_index;
    attacked_by = BLACK;
  }
 
  // Does this move put mover into check? 
  if (isAttacked(target, attacked_by, attacker)) 
      return true;

  return false;
}



void ChessBoard::checkForCheck(int destination_index) {
  vector <int> attacker;
  int target;

  if (turn == BLACK) {
    target = white_king_index;
  }
  else {
    target = black_king_index;
  }
    
  // Is this checkmate
  if(checkmateOrCheck(target)) {
    return;
  }
  
  // Stalemate if no other valid moves
  for(int i = 0; i < BOARD_SIZE; i++) {
    if((i & 0x88) == 0) {
      if(isAttacked(i, board[target]->getColour(), attacker)) {
	for(unsigned int j=0; j < attacker.size(); j++) {
	  if(safeToMove(attacker.at(j), i))
	    return;
	}
      }
    }
  }

  cout << "Stalemate\n";
  game_alive = false;	      
  return;
}



void ChessBoard::getNeighbours(int index) {
  neighbours[0] = index + ChessPiece::EAST;
  neighbours[1] = index + ChessPiece::WEST;
  neighbours[2] = index + ChessPiece::NORTH_WEST;
  neighbours[3] = index + ChessPiece::SOUTH_EAST;
  neighbours[4] = index + ChessPiece::NORTH;
  neighbours[5] = index + ChessPiece::SOUTH;
  neighbours[6] = index + ChessPiece::NORTH_EAST;
  neighbours[7] = index + ChessPiece::SOUTH_WEST;
  return;
} 


bool ChessBoard::blockingMove(int attack_index, int target_index) {
  int index_difference = abs(target_index - attack_index);
  int increment;
  vector <int> defender; 

  // Can't block a knight
  if (index_difference == (ChessPiece::NORTH_NORTH_WEST) || 
      index_difference == (ChessPiece::NORTH_NORTH_EAST) || 
      index_difference == (ChessPiece::SOUTH_SOUTH_WEST) || 
      index_difference == (ChessPiece::SOUTH_SOUTH_EAST) ||
      index_difference == (ChessPiece::EAST_NORTH_EAST) ||
      index_difference == (ChessPiece::EAST_SOUTH_EAST) ||
      index_difference == (ChessPiece::WEST_SOUTH_WEST) ||
      index_difference == (ChessPiece::WEST_NORTH_WEST))
    return false;


  if (index_difference % ChessPiece::NORTH_WEST == 0) {
    if (attack_index > target_index)
      increment = ChessPiece::NORTH_WEST;
    else
      increment = ChessPiece::SOUTH_EAST;
  }


  if (index_difference % ChessPiece::NORTH == 0) {
    if (attack_index > target_index)
      increment = ChessPiece::NORTH;
    else
      increment = ChessPiece::SOUTH;
  }


  if (index_difference % ChessPiece::NORTH_EAST == 0) {
    if (attack_index > target_index)
      increment = ChessPiece::NORTH_EAST;
    else
      increment = ChessPiece::SOUTH_WEST;
  }


  if (index_difference < BOARD_WIDTH) {
    if (attack_index > target_index)
      increment = ChessPiece::EAST;
    else
      increment = ChessPiece::WEST;
  }


  for(int i = target_index; i < attack_index; i += increment) {
    if (isAttacked(i, turn, defender)) {
      for (unsigned int j=0; j < defender.size(); j++) {
	if(safeToMove(defender.at(j), i))
	  return true;
      }
    }
  }
  return false;
}



bool ChessBoard::safeToMove(int from_index, int to_index) {

  // Save the original positions, move the piece, then move it back if necessary
  ChessPiece * save_from_piece = board[from_index];
  ChessPiece * save_to_piece = board[to_index];
  board[to_index] = board[from_index];
  board[from_index] = NULL;

  //Update King positions if neccessary
  if (from_index == white_king_index) 
    white_king_index = to_index;
  
  if (from_index == black_king_index) 
    black_king_index = to_index;
  

  if (selfCheck(board[to_index]->getColour())) { // revert positions
    board[from_index] = save_from_piece;
    board[to_index] = save_to_piece;

    // Restore King positions
    if (to_index == white_king_index)
      white_king_index = from_index;

    if (to_index == black_king_index)
      black_king_index = from_index;

    return false;
  }

  
  board[from_index] = save_from_piece;
  board[to_index] = save_to_piece; 

  // Restore King positions
  if (to_index == white_king_index)
    white_king_index = from_index;
  
  if (to_index == black_king_index)
    black_king_index = from_index;

  return true;
}



bool ChessBoard::kingCanMoveToNeighbours(int king_square) {
  vector <int> king_threateners;
  getNeighbours(king_square);

  for(int i = 0; i < BOARD_WIDTH; i++) {
    if ((neighbours[i] & 0x88) == 0 &&
	!isAttacked(neighbours[i], turn, king_threateners) &&
	((board[neighbours[i]] == NULL) ||
	 board[neighbours[i]]->getColour() != board[king_square]->getColour())) {
      return true;
    }
  }
  return false;
}



bool ChessBoard::checkmateOrCheck(int king_square) {
  vector <int> attacker;

  if (kingCanMoveToNeighbours(king_square)) {
    // No stalemate or checkmate. 
    // Does this move put opponent into check?
    if(isAttacked(king_square, turn, attacker)) {
      cout << board[king_square]->getColour() << " is in check\n";
      return true;
    }
  }

  if(isAttacked(king_square, turn, attacker)) {
    // Checkmate if more than 1 attacker as should have already
    // determined above that king can't move to neighbours
    if (attacker.size() > 1) { 
      cout << board[king_square]->getColour() << " is in checkmate\n";
      game_alive = false;
      return true;
    }
    
    // Can the attacker be taken?
    int attacking_index = attacker.front();
    if(isAttacked(attacking_index, board[king_square]->getColour(), attacker)) {
      // Will taking the attacker leave the capturer in check?
      for (unsigned int i = 0; i < attacker.size(); i++ ) {
	if(safeToMove(attacker.at(i), attacking_index)) {
	  cout << board[king_square]->getColour() << " is in check\n";
	  return true ;
	}
      }
    }
    
    // Can anything come between attacker and king?
    if (blockingMove(attacking_index, king_square)) {
      cout << board[king_square]->getColour() << " is in check\n";
      return true;
    }
    
    cout << board[king_square]->getColour() << " is in checkmate\n";
    game_alive = false;
    return true;
  }
  
  return false;
}



bool ChessBoard::validCastle(int source_index, int destination_index) {
  int rook = getCastlingRook(source_index, destination_index);
  
  // Either king or rook has moved
  if ((board[source_index]->hasMoved()) || 
      (board[rook]->hasMoved())) {
    return false;
  }
    
  // Kingside castle
  if (destination_index - source_index > 0) {
    for (int i = (source_index + 1); i < destination_index; i++) {
      if (board[i] != NULL)
	return false;
    }

    if (!safeToMove(source_index, (source_index + 1))) {
      return false;	
    }
    return true;
  }

  // Queenside castle
  // Check king will not pass through check AND
  // the squares between the king and rook are unoccupied
 
  for (int i = (source_index - 1); i > destination_index; i--) {
    if (board[i] != NULL)
      return false;
  }
  if(!safeToMove(source_index, (source_index - 1)))  
    return false;
  
  return true;
}



int ChessBoard::getCastlingRook(int source_index, int destination_index) {
  if (destination_index > source_index) 
    return (destination_index + 1);

  return (destination_index - 2);

}



void ChessBoard::moveCastlingRook(int king_index, int king_destination) {

  int rook = getCastlingRook(king_index, king_destination);
  int rook_destination;
  // If queenside castle, then rook + 3 squares will be on the board
  // If rook + 3 is not on board, then it's a kingside castle
  if(((rook + 3) & 0x88) != 0) {
    rook_destination = rook - 2;
  }
  else {
    rook_destination = rook + 3; 
  }

  movePiece(rook, rook_destination);

  board[rook_destination]->setMove();

  return;
}


void ChessBoard::checkPawnPromotion(int destination_index) {
  rank = (destination_index/ChessPiece::NORTH + 1);
  if (board[destination_index]->hasSpecialMoves() &&
      (rank == 1 || rank == 8)) {
    cout << turn << "'s " << board[destination_index]->getName();
    cout << " has been promoted.\n";
    delete board[destination_index];
    if(turn == WHITE) 
      board[destination_index] = new Queen(ChessPiece::WHITE);
    else 
      board[destination_index] = new Queen(ChessPiece::BLACK);
  }
  return;
}

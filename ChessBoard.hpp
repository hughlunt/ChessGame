/****************************************************/
/*                                                  */
/* Date Created: 01/12/14                           */
/* Description: Definition of ChessBoard class.     */
/*              Sets up board and revieces moves    */
/*                                                  */
/* Date      Who  Description of Change             */
/* 20141201  HL   Created.                          */
/****************************************************/

#include <vector>
class ChessPiece;

class ChessBoard {

public: 
  
  ChessBoard();
  ~ChessBoard();

  // Move a piece from source_square to destination_square
  void submitMove(std::string source_square, std::string destination_square);
  // Reset the chessboard.
  void resetBoard();

private:
  static const int BOARD_SIZE = 128;
  static const int BOARD_WIDTH = 8;
  static const int ASCII_OFFSET = 65;
  static const int ASCII_MAX = 90;
  static const int SQUARE_LENGTH = 2;
  static const int INT_ASCII_OFFSET = 48;

  ChessPiece *board[BOARD_SIZE];
  
  int fifty_move_draw_count;
  int move_counter;

  int rank;
  int file;

  int black_king_index;
  int white_king_index;

  //int en_passant_index;
  int neighbours[BOARD_WIDTH];
  
  std::string turn;

  bool game_alive;

  // Function takes an input square reference e.g. "E2" and converts it to
  // the corresponding index number e.g. 20.
  int squareToIndex(std::string square);

  // Takes a board index, returns the square in string notation.
  // e.g. 20 would become "E2".
  std::string indexToSquare(int index);

  // Returns true if the square input is in the correct format e.g "E2".
  // Returns false otherwise.
  bool validSquare(std::string square);

  //Deletes all object on the board
  void clearBoard();

  // Places all pieces on the board
  void setupBoard();

  // Checks if a specific colour is attacking a target index
  bool isAttacked(int target, std::string colour, std::vector <int> &attacker);

  // Moves a piece on chessboard board from source index to destination index
  void movePiece(int source_index, int destination_index);

  // Returns true if there is not a piece at the source index a.k.a source square
  // Returns flase if there is a piece there.
  bool noPiece(int source_index, std::string source_square);

  // Returns true if trying to move the correct colour piece
  // Returns false if trying to move the incorrect colout piece
  bool myTurn(int source_index);

  // Returns true if a move results in the colour passed in
  // placing themselves in check. False if it does not.
  bool selfCheck(std::string colour);

  // Checks if a move places oponent in check or checkmate. 
  // Outputs to screen if so.
  void checkForCheck(int destination_index);

  // Returns the immediate neighbours of index in an array
  void getNeighbours(int index);

  // Returns true if there is a piece that can block the attacking index
  // from the target index. Returns false if not
  bool blockingMove(int attack_index, int target_index);

  // Returns true if piece can move from one index to another 
  // without putting itself in check
  bool safeToMove(int from_index, int to_index);

  // Returns true if a king is able to move to at least one of its's
  // immediate neighbours
  bool kingCanMoveToNeighbours(int king_square);

  // Returns true if a king is in checkmate or check
  // False otherwise. 
  bool checkmateOrCheck(int king_square);

  // Returns true if a castling move is valid
  // Returns false if it is not valid
  bool validCastle(int source_index, int destination_index);

  //Returns the index of the rook that the king is attempting to castle with
  int getCastlingRook(int source_index, int destination_index);

  // Moves a castling rook
  void moveCastlingRook(int king_index, int king_destination);

  // Checks to see if a pawn has reached the final rank
  // If so, it promotes it to a queen
  void checkPawnPromotion(int destination_index);

  // Checks to see if the move just made will allow en-passant on the following
  // move. If so it sets the en-passant index.
  //void checkEnPassant(int destination_index);
};

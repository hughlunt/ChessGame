GCC = g++
CFLAGS= -c -g -Wall -MMD
OBJ = ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Rook.o Knight.o Bishop.o King.o Queen.o
EXECUTABLE = chess

$(EXECUTABLE):$(OBJ)
	$(GCC) $(OBJ) -o $(EXECUTABLE)

%.o: %.cpp
	$(GCC) $(CFLAGS) $<

-include $(OBJ:.o=.d)

.PHONY: clean

clean: 
	rm -f $(OBJ) $(EXECUTABLE)

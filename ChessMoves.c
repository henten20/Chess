//------------------------------------------------------------------
// University of Central Florida
// COP 3502 - Fall 2016 - Szumlanski
// Program Author: Henry Ton
// PID: H2950390
// Program 1: ChessMoves.c
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ChessMoves.h"

#define COL 8
#define ROW 8


//------------------------------------------------------------------
// This function creates a bnak chess board and
// fills the initialized spaces with the proper pieces
//------------------------------------------------------------------
char **createChessBoard(void)
{
	int i, j;
	char **ChessBoard;

	// Creating a dynamic array for the board
	ChessBoard = malloc(sizeof(char*)*ROW);

	// For each index, a new array is created
	for (i = 0; i < ROW; i++)
		ChessBoard[i] = malloc(sizeof(char)*COL);

	strncpy(ChessBoard[0], "RNBQKBNR", 8);
	strncpy(ChessBoard[1], "PPPPPPPP", 8);
	strncpy(ChessBoard[2], "        ", 8);
	strncpy(ChessBoard[3], "        ", 8);
	strncpy(ChessBoard[4], "        ", 8);
	strncpy(ChessBoard[5], "        ", 8);
	strncpy(ChessBoard[6], "pppppppp", 8);
	strncpy(ChessBoard[7], "rnbqkbnr", 8);

	return ChessBoard;
}

//------------------------------------------------------------------
// This function takes in the dynamically created chessboard and
// wipes out the allocated memory for each index created.
// This is important for preventing memory leaks
//------------------------------------------------------------------
char **destroyChessBoard(char **board)
{
	int i;

	//creating blank 2D array
	for (i = 0; i < ROW; i++)
	{
		free(board[i]);
	}
	free(board);

	return NULL;
}
//------------------------------------------------------------------
// This function prints out the chessboard, starting with the bars
// at the top, then the 2D array, followed by another bar. 
//------------------------------------------------------------------
void printChessBoard(char **board)
{
	int i, j, border = 0;

	while (border < COL)
	{
		printf("=");
		border++;
	}
	border = 0;

	printf("\n");

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

	while (border < COL)
	{
		printf("=");
		border++;
	}
	printf("\n\n");
}

//------------------------------------------------------------------
// This function takes the parsed string inputs for the chess moves
// and checks for the piece, column, row, capture, etc etc. 
// It then saves the informtion into the Move struct for later use.
//------------------------------------------------------------------
void readMove(char *part, Move *move)
{
	int length = strlen(part);

	int i = length - 1;
	int temp_num;

	// The parsing begins from the right side of the string
	// and reads towards the left, black move ->> white move

	// This checks for to_location "row"
	if ((part[i] >= '0') && (part[i] <= '9'))
	{
		temp_num = atoi(&part[i]);
		move->to_loc.row = temp_num;
		i--;
	}


	// This checks for the to_location "col"
	if ((part[i] >= 'a') && (part[i] <= 'z'))
	{
		move->to_loc.col = part[i];
		i--;
	}

	// This checks to see if a capture takes place
	if (part[i] == 'x')
	{
		move->isCapture = 1;
		i--;
	}
	else
	{
		move->isCapture = 0;
	}
	

	// This checks for a from_location "row"
	if ((part[i] >= '0') && (part[i] <= '9'))
	{
		temp_num = atoi(&part[i]);
		move->from_loc.row = temp_num;
		i--;
	}
	else
	{
		move->from_loc.row = -1;
	}

	// This checks for a the_from location "col"
	if ((part[i] >= 'a') && (part[i] <= 'z'))
	{
		move->from_loc.col = part[i];
		i--;
	}
	else
	{
		move->from_loc.col = 'x';
	}


	// The very left-most part indicates the piece that is being moved

	if (part[i] == 'K')
	{
		move->piece = 'K';
	}
	else if (part[i] == 'Q')
	{
		move->piece = 'Q';
	}
	else if (part[i] == 'B')
	{
		move->piece = 'B';
	}
	else if (part[i] == 'R')
	{
		move->piece = 'R';
	}
	else if (part[i] == 'N')
	{
		move->piece = 'N';
	}
	else
	{
		move->piece = 'P';
	}

}

//------------------------------------------------------------------
// This function reads through a whole string which contains the 
// move number, white move, and black move. It then separates them
// according to the encounter of a space and calls the readMove 
// function to further parse through the string.
//------------------------------------------------------------------

void parseNotationString(char *str, Move *whiteMove, Move *blackMove)
{
	int moveNumber;
	int partNumber = 0;

	char *part;
	char moveset[100] = { 0 };


	// This saves the string into a newly created string
	strcpy(moveset, str);


	// strtok will read in each string until either a period or space
	// is encountered. It will then loop again and save the components
	// of that string to the corresponding move struct. Black or White.
	part = strtok(moveset, ". ");
	while (part != NULL)
	{
		if (partNumber == 0)
		{
			moveNumber = atoi(part);
		}
		if (partNumber == 1)
		{
			readMove(part, whiteMove);
			whiteMove->color = WHITE;
		}
		if (partNumber == 2)
		{
			//if(part == NULL)
			readMove(part, blackMove);
			blackMove->color = BLACK;
		}

		part = strtok(NULL, " .");
		partNumber++;
	}
}

//------------------------------------------------------------------
// These next two functions were created because the chess board 
// indices are opposite of how arrays are read in c.
// This function will take in the column and row index 
// and switch them to the corresponding array index. 
// These functions will be called repeatedly whenever a 
// piece is being moved.
//------------------------------------------------------------------
int convertCol(char column_after)
{
	int col;

	if (column_after == 'a')
		col = 0;
	if (column_after == 'b')
		col = 1;
	if (column_after == 'c')
		col = 2;
	if (column_after == 'd')
		col = 3;
	if (column_after == 'e')
		col = 4;
	if (column_after == 'f')
		col = 5;
	if (column_after == 'g')
		col = 6;
	if (column_after == 'h')
		col = 7;

	return col;
}

int convertRow(int row_after)
{
	int row;

	if (row_after == 1)
		row = 7;
	if (row_after == 2)
		row = 6;
	if (row_after == 3)
		row = 5;
	if (row_after == 4)
		row = 4;
	if (row_after == 5)
		row = 3;
	if (row_after == 6)
		row = 2;
	if (row_after == 7)
		row = 1;
	if (row_after == 8)
		row = 0;

	return row;
}

char reverse_convertCol(int column_before)
{
	char col;

	if (column_before == 0)
		col = 'a';
	if (column_before == 1)
		col = 'b';
	if (column_before == 2)
		col = 'c';
	if (column_before == 3)
		col = 'd';
	if (column_before == 4)
		col = 'e';
	if (column_before == 5)
		col = 'f';
	if (column_before == 6)
		col = 'g';
	if (column_before == 7)
		col = 'h';

	return col;
}

int reverse_convertRow(int row_before)
{
	int row;

	if (row_before == 0)
		row = 8;
	if (row_before == 1)
		row = 7;
	if (row_before == 2)
		row = 6;
	if (row_before == 3)
		row = 5;
	if (row_before == 4)
		row = 4;
	if (row_before == 5)
		row = 3;
	if (row_before == 6)
		row = 2;
	if (row_before == 7)
		row = 1;

	return row;
}

//------------------------------------------------------------------
// This function is a continuation of the findFromLoc function
// it takes in all the given information for the location of the
// pieces and scans the board at those location to see if the
// piece is present. If a piece is present, then the newly found
// location will be entered into the struct so that the movePiece
// function can alter the "from" location with a blank space.
//------------------------------------------------------------------
void checkPiece(int piece, char **board, int col_after, int row_after, int col_before, int row_before, Move *move)
{
	if (board[row_before][col_before] == piece)
	{
		move->from_loc.col = reverse_convertCol(col_before);
		move->from_loc.row = reverse_convertRow(row_before);
	}
}

void knight(char **board, Move *move, int col, int row)
{
	// check to see if the position is out of bounds
	if (col > 7 || col < 0 || row < 0 || row > 7)
		return;
}

void queen(char **board, Move *move, int col, int row, int n)
{
	// check to see if the position is out of bounds
	if (col > 7 || col < 0 || row < 0 || row > 7)
		return;

	if (board[row][col] == move->piece)
	{
		move->from_loc.col = col;
		move->from_loc.row = row;
		return;
	}

}

void bishop(char *board, Move *move, int col int row, int n)
{
	// check to see if the position is out of bounds
	if (col > 7 || col < 0 || row < 0 || row > 7)
		return;

	if (board[row][col] == move->piece)
	{
		move->from_loc.col = col;
		move->from_loc.row = row;
		return;
	}

	if (n == 0)
		bishop(board, move, col++, row++, n++);
	if (n == 1)
		bishop(board, move, col++, row--, n++);
	if (n == 2)
		bishop(board, move, col--, row++, n++);
	if (n == 3)
		bishop(board, move, col--, row--, n++);
	
}

void rook(char *board, Move *move, int col int row, int n)
{
	// check to see if the position is out of bounds
	if (col > 7 || col < 0 || row < 0 || row > 7)
		return;

	if (board[row][col] == move->piece)
	{
		move->from_loc.col = col;
		move->from_loc.row = row;
		return;
	}

	if (n == 0)
		rook(board, move, col++, row, n++);
	if (n == 1)
		rook(board, move, col, row++, n++);
	if (n == 2)
		rook(board, move, col--, row, n++);
	if (n == 3)
		rook(board, move, col, row--, n++);
}

void king(char **board, Move *move, int col, int row, int n)
{
	// check to see if the position is out of bounds
	if (col > 7 || col < 0 || row < 0 || row > 7)
		return;
}

//------------------------------------------------------------------
// This function will take in the chess board and move struct and
// begins checking all the possible "from" locations of each piece.
// Each piece has its own algorithm according to the kind of moves
// it can make. It'll backtrace and use the checkPiece function
// to confirm whether that piece is in the suspected location.
//------------------------------------------------------------------
void findFromLoc(char **board, Move *move)
{
	char piece;
	int capture;
	char col_after;
	int row_after;
	int col_before;
	int row_before;
	int i, j;

	piece = move->piece;
	capture = move->isCapture;

	// Assigning the "from" location
	col_before = move->from_loc.col;
	row_before = move->from_loc.row;

	if (move->piece == 'Q' || move->piece == 'q')
		queen(board, move, move->to_loc.col, move->to_loc.row, 0);


}

//------------------------------------------------------------------
// This function will take in the destinations for a specific piece
// and then search the board using the findFromLoc function to 
// see if that piece is moveable. It will then place that piece
// into the destination on the board.
//------------------------------------------------------------------
void movePiece(char **board, Move *move)
{
	int row_after = move->to_loc.row;
	int col_after = move->to_loc.col;
	int row_before;
	int col_before;
	char piece = move->piece;

	// convert the to_loc to array format
	move->to_loc.row = convertRow(row_after);
	move->to_loc.col = convertCol(col_after);

	// Checking for white or black color
	if (move->color == WHITE)
		move->piece = tolower(piece);

	// Tracing back to search for the piece
	findFromLoc(board, move);

	

	// Converting the locations to align with the array
	// Moving the piece 
	row_before = convertRow(move->from_loc.row);
	col_before = convertCol(move->from_loc.col);

	board[row_after][col_after] = piece;
	board[row_before][col_before] = ' ';
}

//------------------------------------------------------------------
// This function creates a white and black move struct, the board,
// and a 2D array to hold the strings for each move. It will then 
// start with the initial board and begin playing the game.
//------------------------------------------------------------------
char **playTheGame(Game *g)
{
	Move whiteMove;
	Move blackMove;

	char **board = NULL;
	char **yourMove = NULL;

	int i;

	board = createChessBoard();
	printChessBoard(board);

	yourMove = g->moves;

	for (i = 0; i < g->numMoves; i++)
	{
		// Splits the moves up
		parseNotationString(yourMove[i], &whiteMove, &blackMove);
		// White moves
		movePiece(board, &whiteMove);
		printChessBoard(board);
		// Black moves
		movePiece(board, &blackMove);
		printChessBoard(board);
	}
	return board;
}

double difficultyRating(void)
{
	return 4.5;
}

double hoursSpent(void)
{
	return 50.5;
}

//------------------------------------------------------------------------------------//
//																					  //
//				EVERYTHING PAST THIS POINT WILL CONSIST OF TEST CASES                 //
//																					  //
//------------------------------------------------------------------------------------//
#include <stdlib.h>
#include <string.h>
#include "ChessMoves.h"


// This is a hacky-horrible way of hard-coding a test case.
Game *testcase20(void)
{
	int i;
	char *moves[10];
	Game *g = NULL;

	i = 0;
	moves[i++] = "1. Nf3 a5";
	moves[i++] = "2. b3 h5";
	moves[i++] = "3. a4 Ra6";
	moves[i++] = "4. h3 Rhh6";
	moves[i++] = "5. Na3 Rad6";
	moves[i++] = "6. Rb1 Rhg6";
	moves[i++] = "7. Ra1 Rg3";
	moves[i++] = "8. Nd4 Rd3";

	g = malloc(sizeof(Game));
	g->numMoves = i;

	g->moves = malloc(sizeof(char *) * g->numMoves);

	for (i = 0; i < g->numMoves; i++)
	{
		g->moves[i] = malloc(sizeof(char) * (strlen(moves[i]) + 1));
		strcpy(g->moves[i], moves[i]);
	}

	return g;
}

Game *destroyGame(Game *g)
{
	int i;

	if (g == NULL)
		return NULL;

	for (i = 0; i < g->numMoves; i++)
		free(g->moves[i]);

	free(g->moves);
	free(g);

	return NULL;
}

int main(void)
{
	// Create a Game struct for this test case.
	Game *g = testcase20();

	// Play the game.
	char **finalBoardState = playTheGame(g);

	// Destroy the chess board returned by playTheGame().
	finalBoardState = destroyChessBoard(finalBoardState);

	// Destroy the Game struct with all the chess moves.
	g = destroyGame(g);

	return 0;
}


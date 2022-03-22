/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_CHESS_H
#define __MODULE_CHESS_H

#include "chess_structs.h"

#include <stdio.h>
#include <stdbool.h>


// constants
#define INF 1000000000
#define MAX_BORING_MOVES 100



//functions for colored terminal output
#define LIGHT(string) "\x1b[43m" string "\x1b[0m"
#define DARK(string) "\x1b[45m" string "\x1b[0m"
#define LIGHT_HINT(string) "\x1b[46m" string "\x1b[0m"
#define DARK_HINT(string) "\x1b[44m" string "\x1b[0m"
#define BLACK_FOREGROUND(string) "\x1b[30m" string

/**
 * generates all possible moves for given position
 * 
 * @param ml pointer to moveList - gets filled with all possible moves
 * @param b pointer to board - moves are generated based on this
 * 
 * @note b doesn't get modified
 */
void generateAllPossibleMoves(Tboard *b, TmoveList* ml);

/**
 * generates all moves starting at *input
 * 
 * @param b pointer to board - moves are generated based on this
 * @param input string of at least two chars (ex. A8C3, C2)
 * @param ml pointer to moveList - gets filled with hints
 * 
 * @note b doesn't get modified
 */
void generateHints(Tboard *b, const char *input, TmoveList* ml);

/**
 * prints board using ANSI color codes
 * 
 * @param b pointer to board to be printed
 */
void printBoard(const Tboard* b);

/**
 * prints board using ANSI color codes, also highlights moves in hint
 * 
 * @param b pointer to board to be printed
 * @param hints pointer to moveList containing hints
 */
void printBoardWithHints(const Tboard* b, TmoveList *hints);

/**
 * prints board using ANSI color codes
 * 
 * @param f output file
 * @param b pointer to board to be printed
 */
void fprintBoard(FILE* out, const Tboard* b);

/**
 * prints board using ANSI color codes, also highlights moves in hint
 * 
 * @param f output file
 * @param b pointer to board to be printed
 * @param hints pointer to moveList containing hints
 */
void fprintBoardWithHints(FILE* out, const Tboard* b, TmoveList *hints);

/**
 * returns unicode string representation of piece
 * 
 * @param piece (ex. p, p, Q, k, N)
 * @return unicode string (ex. ♚, ♝, "\x1b[30m♛")
 * 
 * @note black is made using ANSI codes
 */
char* getPieceGraphics(char piece);

/**
 * returns last piece that moved on board
 * 
 * @note only if something has been moved, else crashes..?
 */
char getLastMovedPiece(const Tboard* b);

/**
 * returns true if last move is check, else returns false
 * 
 * @param b pointer to board
 * @param myKingPos position of king (checks if this king got checked)
 * 
 * @return true if last move is check, else false
 */
bool gotChecked(const Tboard *b, const int myKingPos[2]);

/**
 * returns 2 for game is pending, 0 for draw,  
 * 1 for win of white and -1 for win of black
 * 
 * @param b pointer to board (isn't modified)
 * @return 2 for game is pending, 0 for draw,  
 * 1 for win of white and -1 for win of black
 */
int getResult(Tboard *b);

/**
 * same as getResult(), but faster
 * 
 * @param b pointer to board (isn't modified)
 * @param ml ponter to moveList containing all possible moves in this pos
 */
int getResultFaster(Tboard *b, TmoveList *ml);

/**
 * returns true if input is in all possible moves in this position
 * 
 * @param b pointer to board (is treated as const)
 * @param input string representing move (ex. E2E4, E7E8r)
 * 
 * @return true if valdid, else false
 */
bool isInputValid(const char* input, Tboard* b);

void moveBoard(const char* input, Tboard* b);
bool isEnPassant(const char* input, const Tboard* b);
bool isEnPassantLegal(const Tboard* b, const int pos[2],
                      const int moveVector[2], int moveRestriction,
                      char oppColor, const int mykingPos[2]);
bool isOnBoard(const int pos[2]);
void generatePieceMoves(const Tboard* b, const int pos[2], TmoveList* ml);
bool isKnightMovePossible(const Tboard* b, const char color,
                          const int pos[2], const int moveVector[2]);
bool isKingMovePossible(const Tboard* b, const char color,
                        const int origin[2], const int dest[2]);
bool isMoveTake(const Tboard* b, const char color, const int pos[2],
                const int moveVector[2], const int restriction);
bool isMoveClean(const Tboard* b, const int pos[2],
                 const int moveVector[2], const int restriction);
bool isItsMove(const int move, const char piece);
void getPieceLocation(const Tboard* b, const char piece, int[2]);
bool isBlockingCheck(const Tboard* b, const char, const int[2], const int[2]);
bool doesMoveBlockCheck(const Tboard* b, const char *move,
                        const int kingPos[2]);
void disableCastling(Tboard *b, char color, bool buffer[2]);
void regainCastling(Tboard *b, char color, bool buffer[2]);

char oppositeColor(const char color);
bool isColor(const char color, const char piece);
bool isUpper(const char);
bool isLower(const char);
void freeArrayOfStrings(char **arr, int len);
bool isArrayInArrayOfArrays(int *array, int **arrayOfArrays,
                            int ArrLen, int ArrOfArrsLen);
bool isStringTwiceInArrayOfStrings(char *array, char **arrayOfArrays,
                                   int ArrOfArrsLen);
void normalize(int moveVector[2]);
bool fitsRestriction(const int moveVector[2], int restriction);
bool isAttacked(const Tboard* b, const char color, const int pos[2]);
bool willBeAttacked(const Tboard *b, const char color, const int origin[2],
                    const int dest[2]);

#endif

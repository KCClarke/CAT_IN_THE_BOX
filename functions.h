// functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#define SPOTS 10
#define COORDINATES 2
#define DIRECTIONS 4



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
enum CardNumbers
{
    CARD_MAX = 5, // number on card
    CARD_MIN = 1, // number on card
};
enum AraySizes
{
    TOTAL_CARDS = 25, // for a 2 player game
    HAND_SIZE = 10,   // for a 2 player game
    COLORS = 4,       // four colors 1 for each row
    COLUMNS = 6,      // six columns including the one with the white cat
    REVEALED = 3      // 3 cards revealed for setup
};
enum Color
{
    RED,
    BLUE,
    YELLOW,
    GREEN,
    UNDEFINED,
    DISCARDED // okay so not a color but it works for my purposes
};

enum direction
{
    up,
    right,
    down,
    left
};
enum Token
{
    playerToken = 'x',
    aiToken = 'o',
    neutralToken = '-'
};

struct Card
{
    int number;
    enum Color color;
};

void greeting();
void initializeCards(struct Card deck[]);
void shuffle(struct Card deck[]);
void deal(struct Card deck[], struct Card playerHand[], struct Card aiHand[]);
void printBoard(char rBoard[COLORS][COLUMNS]);
void initializeBoard(char rBoard[COLORS][COLUMNS], char colors[]);
void revealCards(struct Card deck[], char rBoard[COLORS][COLUMNS]);
void playerDiscard(struct Card playerHand[]);
void aiDiscard(struct Card aiHand[]);
bool paradox(char colors[], char playerBoard[], struct Card playerHand[], char rBoard[COLORS][COLUMNS]);
int playerTurn(char colors[], char playerBoard[], struct Card playerHand[], char rBoard[COLORS][COLUMNS], struct Card *playerCard);
int aiTurn(char colors[], char aiBoard[], struct Card aiHand[], char rBoard[COLORS][COLUMNS], int ledColor, struct Card *playerCard, struct Card *aiCard);
void colorRemover(int ledColor, int nonLedColor, char colorBoard[]);
bool didPlayerWinTrick(int ledColor, struct Card *playerCard, struct Card *aiCard);
int bonusScore(char token, bool paradox, char rBoard[COLORS][COLUMNS]);
#endif // FUNCTIONS_H
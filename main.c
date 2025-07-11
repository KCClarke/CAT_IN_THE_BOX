// main.c

/******************************************************************************
CAT IN THE BOX
V2
28th of July 2023
dev Kasey Clarke
game by Muneyuki Yokouchi

update: First working prototype August 21 2023 =(^-^)=

*/

#include "functions.h"

int main()
{
    greeting();
    // setup
    srand(time(NULL));
    struct Card deck[TOTAL_CARDS];
    struct Card playerHand[HAND_SIZE];
    struct Card aiHand[HAND_SIZE];
    char colors[] = {'r', 'b', 'y', 'g'};
    char rBoard[COLORS][COLUMNS]; // the researh board
    initializeCards(deck);        // puts numbers on cards

    // main gameplay loop
    int maxRounds = 2;
    bool playerStarts = rand() % 2;
    bool initialStart = playerStarts;
    int playerFinalScore = 0, aiFinalScore = 0;
    for (int j = 1; j <= maxRounds; j++)
    { // plays game 2 rounds

        if (j == maxRounds) // different players start each round
            playerStarts = !initialStart;
        printf("round %d, %s starts\n", j, playerStarts ? "player" : "ai");
        shuffle(deck);
        deal(deck, playerHand, aiHand);
        initializeBoard(rBoard, colors);
        revealCards(deck, rBoard); // modifies research board
        printBoard(rBoard);
        playerDiscard(playerHand);
        aiDiscard(aiHand);

        int playerRoundScore = 0, aiRoundScore = 0;
        int handAfterDiscard = HAND_SIZE - 1; // 1 card was discarded
        char playerBoard[] = {'r', 'b', 'y', 'g'};
        char aiBoard[] = {'r', 'b', 'y', 'g'};
        struct Card playerCard, aiCard;
        playerCard.number = UNDEFINED;
        int minCardsInHand = 1; // scale up for de bugging back to 1 for play
        int ledColor = UNDEFINED, nonLedColor = UNDEFINED;
        bool playerParadox = false, aiParadox = false;
        // int playerFinalScore, aiFinalScore;
        for (int i = handAfterDiscard; i > minCardsInHand; i--)
        { // plays untill both players paradox or have minCardsInHand
            ledColor = UNDEFINED;
            bool playerWonTrick;
            if (i != handAfterDiscard)
                playerStarts = playerWonTrick;

            if (playerStarts)
            {
                if (paradox(colors, playerBoard, playerHand, rBoard))
                {
                    playerParadox = true;
                    break;
                }
                ledColor = playerTurn(colors, playerBoard, playerHand, rBoard, &playerCard);
                printBoard(rBoard);

                if (paradox(colors, aiBoard, aiHand, rBoard))
                {
                    aiParadox = true;
                    break;
                }
                nonLedColor = aiTurn(colors, aiBoard, aiHand, rBoard, ledColor, &playerCard, &aiCard);
                colorRemover(ledColor, nonLedColor, aiBoard);
                printBoard(rBoard);
            }
            else
            {
                if (paradox(colors, aiBoard, aiHand, rBoard))
                {
                    aiParadox = true;
                    break;
                }
                ledColor = aiTurn(colors, aiBoard, aiHand, rBoard, ledColor, &playerCard, &aiCard);
                printBoard(rBoard);

                if (paradox(colors, playerBoard, playerHand, rBoard))
                {
                    playerParadox = true;
                    break;
                }
                nonLedColor = playerTurn(colors, playerBoard, playerHand, rBoard, &playerCard);
                colorRemover(ledColor, nonLedColor, playerBoard);
                printBoard(rBoard);
            }
            // winning card determines startPlayer
            playerWonTrick = didPlayerWinTrick(ledColor, &playerCard, &aiCard); // true; // rand() % 2; // random for now
            printf("%s won the trick!", playerWonTrick ? "player" : "ai");
            if (playerWonTrick)
            {
                playerRoundScore++;
                printf(" %d tricks won\n", playerRoundScore);
            }
            else
            {
                aiRoundScore++;
                printf(" %d tricks won\n", aiRoundScore);
            }
        }
        if (playerParadox || aiParadox)
            printf("%s has paradoxed!\n", playerParadox ? "player" : "ai");

        if (playerParadox)
        {
            playerFinalScore -= playerRoundScore;
        }
        else
        {
            playerFinalScore += playerRoundScore;
        }

        if (aiParadox)
            aiFinalScore -= aiRoundScore;
        else
            aiFinalScore += aiRoundScore;

        playerFinalScore += bonusScore(playerToken, playerParadox, rBoard);
        aiFinalScore += bonusScore(aiToken, aiParadox, rBoard);

        printf("\n");
    }
    printf("Final scores!\nplayer: %d\n    ai: %d\n", playerFinalScore, aiFinalScore);
    // endGame();
    int lastBit;
    scanf(" %d", &lastBit);
}
///////////////////////////////////////////////////////////////////////////////
// cd "C:\Users\Kasey\OneDrive\Documents\c and c++ code\CAT IN THE BOX"
//  gcc -o main main.c functions.c
//.\main
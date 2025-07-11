// functions.c

#include "functions.h"

void greeting() { printf("\n\n\tWelcome to CAT IN THE BOX [=(^_^)=]\n"); }
void initializeCards(struct Card deck[])
{
    // printf("card initializer\n");
    for (int j = 0; j < CARD_MAX; j++)
    {
        for (int i = 0; i < CARD_MAX; i++)
        {
            int index = i + j * CARD_MAX;
            deck[index].color = UNDEFINED;
            deck[index].number = CARD_MIN + j;
        }
    }

    // for (int i = 0; i < TOTAL_CARDS; i++)
    // {
    //     printf(" %d", deck[i].color);
    // }
}
void shuffle(struct Card deck[])
{
    // printf("shuffle deck\n");
    for (int i = 0; i < TOTAL_CARDS; i++)
    {
        int temp_a = deck[i].number;
        int random = rand() % TOTAL_CARDS;
        int temp_b = deck[random].number;
        deck[i].number = temp_b;
        deck[random].number = temp_a;
    }
    /*
    for (int i = 0; i < TOTAL_CARDS; i++)
        printf(" %d", deck[i].number);
    printf("\n");
    */
}
void deal(struct Card deck[], struct Card playerHand[], struct Card aiHand[])
{
    // printf("deal\n");
    for (int i = 0; i < HAND_SIZE + HAND_SIZE; i++)
    {
        if (i < HAND_SIZE)
        {
            playerHand[i].number = deck[i].number;
            playerHand[i].color = deck[i].color;
        }
        else
        {
            aiHand[i - HAND_SIZE].number = deck[i].number;
            aiHand[i - HAND_SIZE].color = deck[i].color;
        }
    }
    // for (int i = 0; i < HAND_SIZE; i++)
    //     printf("%d", playerHand[i].number);
    // printf("\n");
    // for (int i = 0; i < HAND_SIZE + HAND_SIZE; i++)
    //     printf("%d", deck[i].number);
    // printf("\n");
    // for (int i = 0; i < HAND_SIZE; i++)
    //     printf("%d", aiHand[i].number);
    // printf("\n");
}
void printBoard(char rBoard[COLORS][COLUMNS])
{
    // printf("printBoard\n");
    for (int i = 0; i < COLORS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
            printf(" %c", rBoard[i][j]);
        printf("\n");
    }
    printf("\n");
}
void initializeBoard(char rBoard[COLORS][COLUMNS], char colors[])
{
    for (int i = 0; i < COLORS; i++)
    {
        rBoard[i][0] = colors[i];
        for (int j = 1; j < COLUMNS; j++)
        {
            rBoard[i][j] = '0' + j;
        }
    }
    // printBoard(rBoard);
}
void revealCards(struct Card deck[], char rBoard[COLORS][COLUMNS])
{
    // printf("revealCArds\n");
    int cardsRevealed[REVEALED]; // in 2 player game, 3 cards after dealing are drawn
    int dealt = HAND_SIZE * 2;   // the index of the cards after 2 dealt hands
    for (int i = 0; i < REVEALED; i++)
    {
        cardsRevealed[i] = deck[dealt + i].number;
        // printf(" %d", cardsRevealed[i]);
    }

    int a = cardsRevealed[0], b = cardsRevealed[1], c = cardsRevealed[2];
    // a = b = c = 3;
    if (a == b && b == c)
    {
        // printf("they all match %d\n", a);
        rBoard[1][a] = '-';
        rBoard[2][b] = '-';
        rBoard[3][c] = '-';
    }
    else if (a != b && a != c && b != c)
    {
        // printf("all unique\n");
        rBoard[3][a] = '-';
        rBoard[3][b] = '-';
        rBoard[3][c] = '-';
    }
    else if (a == b)
    {
        // printf("a and b match\n");
        rBoard[3][a] = '-';
        rBoard[2][b] = '-';
        rBoard[3][c] = '-';
    }
    else if (a == c)
    {
        // printf("a and c match\n");
        rBoard[3][a] = '-';
        rBoard[3][b] = '-';
        rBoard[2][c] = '-';
    }
    else
    {
        // printf("b and c match\n");
        rBoard[3][a] = '-';
        rBoard[3][b] = '-';
        rBoard[2][c] = '-';
    }
}
void playerDiscard(struct Card playerHand[])
{
    int chosenCard;
    bool validCard = false;
    while (!validCard)
    {
        printf("discard a card [");
        for (int i = 0; i < HAND_SIZE; i++)
        {
            printf(" %d", playerHand[i].number);
        }
        printf(" ]: ");

        if (scanf(" %d", &chosenCard) != 1)
        {
            while (getchar() != '\n')
            {
            }         // clear the buffer
            continue; // to while (!validCard)
        }

        for (int i = 0; i < HAND_SIZE; i++)
        {
            if (playerHand[i].number == chosenCard)
            {
                playerHand[i].color = RED;
                validCard = true;
                break;
            }
        }
    }
}
void aiDiscard(struct Card aiHand[])
{
    int discardIndex = rand() % HAND_SIZE;
    aiHand[discardIndex].color = RED;
    printf("ai discards\n\n");
}
bool paradox(char colors[], char playerBoard[], struct Card playerHand[], char rBoard[COLORS][COLUMNS])
{
    for (int i = 0; i < COLORS; i++)
    {
        if (colors[i] == playerBoard[i])
        { // check to see if player board has the color
            for (int j = 1; j < COLUMNS; j++)
            { // check the research board at the color for a valid character number
                if (rBoard[i][j] >= '1' && rBoard[i][j] <= '5')
                    for (int k = 0; k < HAND_SIZE; k++)
                    { // check the hand at the valid char index for a match
                        if ((playerHand[k].number == j) && playerHand[k].color == UNDEFINED)
                        {
                            // printf("card in hand matches spot on board\n");
                            return false; // no paradox
                        }
                    }
            }
        }
    }
    // printf("paradox\n");
    return true;
}
int playerTurn(char colors[], char playerBoard[], struct Card playerHand[], char rBoard[COLORS][COLUMNS], struct Card *playerCard)
{
    printf("player turn\n");

    printf("player hand [");
    for (int i = 0; i < HAND_SIZE; i++)
    {
        if (playerHand[i].color == UNDEFINED)
            printf(" %d", playerHand[i].number);
    }
    printf(" ]\n");

    int handIndex;
    int colorIndex = UNDEFINED;
    int chosenNumber;
    bool validCard = false;
    while (!validCard)
    {
        // gets the color
        char chosenColor = UNDEFINED;
        bool validColor = false;
        while (!validColor)
        {
            printf("pick a color [ ");
            for (int i = 0; i < COLORS; i++)
            {
                if (playerBoard[i] == colors[i])
                    printf("%c ", playerBoard[i]);
            }
            printf("]: ");

            scanf(" %c", &chosenColor);
            for (int i = 0; i < COLORS; i++)
            {
                if (chosenColor == playerBoard[i] && chosenColor != '-')
                {
                    validColor = true;
                    colorIndex = i;
                    break;
                }
            }

            // gets the card number
            bool validNumber = false;
            while (!validNumber)
            {
                printf("pick a number [");
                for (int i = 0; i < HAND_SIZE; i++)
                {
                    if (playerHand[i].color == UNDEFINED)
                        printf(" %d", playerHand[i].number);
                }
                printf(" ]: ");

                if (scanf(" %d", &chosenNumber) != 1)
                {
                    while (getchar() != '\n')
                    {
                    }         // clear the buffer
                    continue; // to while (!validNumber)
                }
                for (int i = 0; i < HAND_SIZE; i++)
                {
                    if (playerHand[i].color == UNDEFINED && playerHand[i].number == chosenNumber)
                    {
                        handIndex = i;
                        validNumber = true; // we found a match!
                        break;
                    }
                }
            }
        }

        char boardToken = rBoard[colorIndex][chosenNumber];
        if (boardToken >= '1' && boardToken <= '5')
        {
            validCard = true;
            rBoard[colorIndex][chosenNumber] = playerToken;
            playerHand[handIndex].color = colorIndex;
        }
        else
        {
            printf("spot taken\n");
        }
    }

    // printf("chosen number %d\n", chosenNumber);
    playerCard->color = colorIndex;
    playerCard->number = chosenNumber;
    return colorIndex; // 0 is red, 1 is blue etc.
}
int aiTurn(char colors[], char aiBoard[], struct Card aiHand[], char rBoard[COLORS][COLUMNS], int ledColor, struct Card *playerCard, struct Card *aiCard)
{
    // printf("playerCard number %d\n", playerCard->number);
    printf("ai turn ");
    printf("["); // print ai color board
    for (int i = 0; i < COLORS; i++)
        if (aiBoard[i] == colors[i])
            printf(" %c", aiBoard[i]);
    printf(" ]:");

    // printf("["); // print ai hand
    // for (int i = 0; i < HAND_SIZE; i++)
    //     if (aiHand[i].color == UNDEFINED)
    //         printf(" %d", aiHand[i].number);
    // printf(" ]:\n");

    if ((ledColor != UNDEFINED) && (aiBoard[ledColor] == colors[ledColor]))
    {
        // ai is following and has the led color available
        for (int i = 1; i < COLUMNS; i++)
        { // check from player card +1. loop around the row on the rBoard
            int potentialSpot = (playerCard->number + i) % COLUMNS;
            if (rBoard[ledColor][potentialSpot] >= '1' && rBoard[ledColor][potentialSpot] <= '5')
            {
                for (int j = 0; j < HAND_SIZE; j++)
                    if ((aiHand[j].color == UNDEFINED) && (aiHand[j].number) == potentialSpot)
                    {
                        aiHand[j].color = ledColor;
                        aiCard->color = ledColor;
                        printf(" %c", aiBoard[ledColor]);
                        aiCard->number = potentialSpot;
                        printf(" %d\n", aiCard->number);
                        rBoard[ledColor][potentialSpot] = aiToken;
                        return ledColor;
                    }

                /*
                if (aiHand[aiCardNumber].color == UNDEFINED)
                {
                    aiHand[aiCardNumber].color = ledColor;
                    printf(" %d\n", aiCardNumber);
                    rBoard[ledColor][aiCardNumber] = aiToken;
                    aiCard->color = ledColor;
                    aiCard->number = aiCardNumber;
                    return ledColor; // i is the now the following color
                }
               */
            }
        }
    }

    // ai is leading the trick or doesn't have the led color
    for (int i = 0; i < COLORS; i++)
    {
        if (aiBoard[i] == colors[i])
        {
            for (int j = CARD_MAX; j >= CARD_MIN; j--)
                if (rBoard[i][j] >= '1' && rBoard[i][j] <= '5')
                {
                    for (int k = 0; k < HAND_SIZE; k++)
                    {
                        if ((aiHand[k].color == UNDEFINED) && (aiHand[k].number == j))
                        {
                            aiHand[k].color = i;
                            aiCard->color = i;
                            printf(" %c", aiBoard[i]);
                            aiCard->number = j;
                            printf(" %d\n", aiCard->number);
                            rBoard[i][j] = aiToken;
                            return i;
                        }
                    }
                    // need to check that card in ai hand is undefined color
                    /*
                    if (aiHand[i].color == UNDEFINED)
                    {
                        rBoard[i][aiCardNumber] = aiToken;
                        printf(" %c %d\n", aiBoard[i], aiCardNumber);
                        aiCard->color = i;
                        aiCard->number = aiCardNumber;
                        return i; // i is the now the leading color
                    }
                    */
                }
        }
    }
}
void colorRemover(int ledColor, int nonLedColor, char colorBoard[])
{
    // printf("color remover\n");
    if (nonLedColor != ledColor)
        colorBoard[ledColor] = neutralToken;
}
bool didPlayerWinTrick(int ledColor, struct Card *playerCard, struct Card *aiCard)
{
    // printf("who won\n");
    if (playerCard->color == RED && aiCard->color != RED)
        return true;

    if (playerCard->color != RED && aiCard->color == RED)
        return false;

    if (playerCard->color == RED && aiCard->color == RED)
    {
        if (playerCard->number > aiCard->number)
            return true;
        else
            return false;
    }

    if (playerCard->color == ledColor && aiCard->color != ledColor)
        return true;

    if (playerCard->color != ledColor && aiCard->color == ledColor)
        return false;

    if (playerCard->color == ledColor && aiCard->color == ledColor)
    {
        if (playerCard->number > aiCard->number)
            return true;
        else
            return false;
    }

    if (playerCard->color == ledColor && aiCard->color != ledColor)
        return true;
    else
        return false;
}
//int bonusScore(char token, bool paradox, char rBoard[COLORS][COLUMNS]);
int bonusScore(char token, bool paradox, char rBoard[COLORS][COLUMNS])
{
    if (paradox)
        return 0;

    bool counted[COLORS][COLUMNS];
    int decisionSpots[SPOTS][COORDINATES];
    int bonusScore = 0, groupSize = 0;
    for (int i = 0; i < COLORS; i++)
    {
        for (int j = 1; j < COLUMNS; j++)
        {
            // initialize 2d array counted to all false
            for (int k = 0; k < COLORS; k++)
                for (int l = 0; l < COLUMNS; l++)
                    counted[k][l] = false;

            // initialize a place to hold decision spots to empty
            int empty = -1;
            for (int k = 0; k < SPOTS; k++)
                decisionSpots[k][0] = empty;

            // if the char is match at rBoard search from its location
            int y = i, x = j;
            bool novel = !counted[y][x];
            bool hasToken = rBoard[y][x] == token;
            bool searching = hasToken;
            bool viableDirection[DIRECTIONS] = {false};
            // if (hasToken)
            //     printf("\n new start %d %d\n", i, j);
            while (searching)
            {
                // printf("at locadion %d %d\n", y, x);
                if (!counted[y][x])
                {
                    ++groupSize;
                    counted[y][x] = true;
                }

                // reset vaibleDirection, reset map
                for (int k = 0; k < DIRECTIONS; k++)
                    viableDirection[k] = false;
                // fill vaibleDirection, scout and mark map
                for (int k = 0; k < DIRECTIONS; k++)
                {
                    switch (k)
                    {
                    case up:
                        novel = !counted[y - 1][x];
                        hasToken = rBoard[y - 1][x] == token;
                        if (novel && hasToken)
                            viableDirection[k] = true;
                        break;
                    case right:
                        novel = !counted[y][x + 1];
                        hasToken = rBoard[y][x + 1] == token;
                        if (novel && hasToken)
                            viableDirection[k] = true;
                        break;
                    case down:
                        novel = !counted[y + 1][x];
                        hasToken = rBoard[y + 1][x] == token;
                        if (novel && hasToken)
                            viableDirection[k] = true;
                        break;
                    case left:
                        novel = !counted[y][x - 1];
                        hasToken = rBoard[y][x - 1] == token;
                        if (novel && hasToken)
                            viableDirection[k] = true;
                        break;
                    }
                }

                // take inventory of possible directions and choose one
                int surroundingSpotsWTokens = 0;
                int nextSpot;
                for (int k = 0; k < DIRECTIONS; k++)
                    if (viableDirection[k] == true)
                    {
                        ++surroundingSpotsWTokens;
                        nextSpot = k;
                    }
                // printf("surrounding spots %d\n", surroundingSpotsWTokens);

                bool decisionSpotsEmpty = true;
                for (int k = 0; k < SPOTS; k++)
                    if (decisionSpots[k][0] != empty)
                    { // wow very different from (decisionSpots[k][0] == !empty)
                        decisionSpotsEmpty = false;
                        break;
                    }

                if (surroundingSpotsWTokens == 0)
                {
                    // printf("decision spots empty %d\n", decisionSpotsEmpty);

                    if (decisionSpotsEmpty)
                        searching = false; // we're done
                    else                   // decision spots not empty
                    {                      // there is a spot where a decision was made
                        int jumpTo;
                        for (int k = 0; k < SPOTS; k++)
                            if (decisionSpots[k][0] != empty)
                            {
                                jumpTo = k;
                                break;
                            }
                        // next spot to move to, clear it from list
                        y = decisionSpots[jumpTo][0];
                        x = decisionSpots[jumpTo][1];
                        decisionSpots[jumpTo][0] = empty;
                    }
                }
                else
                {
                    if (surroundingSpotsWTokens > 1)
                    { // mark this spot to come back to
                        int emptyIndex;
                        for (int k = 0; k < SPOTS; k++)
                            if (decisionSpots[k][0] == empty)
                            { // look for an unused place in the list
                                emptyIndex = k;
                                break;
                            }
                        decisionSpots[emptyIndex][0] = y;
                        decisionSpots[emptyIndex][1] = x;
                        // printf("\tdecision spot found %d %d\n", y, x);
                    }

                    // move to new spot keep searching
                    switch (nextSpot)
                    {
                    case up:
                        --y;
                        break;
                    case right:
                        ++x;
                        break;
                    case down:
                        ++y;
                        break;
                    case left:
                        --x;
                        break;
                    }
                }
            }
            // if (groupSize > 0)
            //     printf("group size %d\n", groupSize);
            if (groupSize > bonusScore)
                bonusScore = groupSize;
            groupSize = 0;
        }
    }
    return bonusScore;
}
///////////////////////////////////////////////////////////////////////////////
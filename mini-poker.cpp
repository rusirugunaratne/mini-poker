#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iterator>
using namespace std;

///////////////////////////////
//Global Variables
//////////////////////////////
int PLAYER_COUNT = 0;
int ALL_SCORE = 0;

///////////////////////////////
//Prints the winner
//////////////////////////////
void printWinner(int index)
{
    cout << endl;
    cout << "***********************" << endl;
    cout << "-----------------------" << endl;
    cout << "  -------------------" << endl;
    cout << "    ---------------" << endl;
    cout << "        -------" << endl;
    cout << "        -------" << endl;
    cout << "        -------" << endl;
    cout << "        -------" << endl;
    cout << "    ---------------" << endl;
    cout << "  -------------------" << endl;
    cout << "-----------------------" << endl;
    cout << "***********************" << endl;
    cout << "THE WINNER IS PLAYER " << index + 1 << endl;
    ofstream outfile;
    outfile.open("log.txt", ios_base::app);
    outfile << "THE WINNER IS PLAYER " << index + 1 << endl;
    outfile.close();
}

///////////////////////////////
//Card class
//////////////////////////////
class Card
{
private:
    string cardShape;
    string cardValue;

public:
    //constructors
    Card() {}
    Card(string cardShape, string cardValue)
    {
        this->cardShape = cardShape;
        this->cardValue = cardValue;
    }
    //getters and setters
    void setcardShape(string cardShape)
    {
        this->cardShape = cardShape;
    }
    void setCardValue(string cardValue)
    {
        this->cardValue = cardValue;
    }
    string getcardShape()
    {
        return cardShape;
    }
    string getCardValue()
    {
        return cardValue;
    }
    void printCard()
    {
        cout << cardValue << " of " << cardShape << endl;
    }
    //operator overloading
    bool operator==(const Card card)
    {
        if (cardShape == card.cardShape && cardValue == card.cardValue)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

///////////////////////////////
//Vectors for storing the
//card pack related variables
//////////////////////////////
vector<string> cardShapes = {
    "Spade", "Diamond", "Heart", "Club"};
vector<string> cardValues = {
    "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "King", "Queen", "Aces"};
vector<Card> cardPack;
vector<Card> shfl;

///////////////////////////////
//Player Class
//////////////////////////////
class Player
{
private:
    int playerNumber;
    int playerScore = 0;

public:
    vector<Card> dealtCards;
    bool isInGame = true;
    int playerCardCombinationValue = 0;
    Player() {}
    Player(int playerNumber, int playerScore)
    {
        this->playerNumber = playerNumber;
        this->playerScore = playerScore;
    }
    void setPlayerNumber(int playerNumber)
    {
        this->playerNumber = playerNumber;
    }
    void setPlayerScore(int playerScore)
    {
        this->playerScore += playerScore;
    }
    int getPlayerNumber()
    {
        return playerNumber;
    }
    int getPlayerScore()
    {
        return playerScore;
    }
};

///////////////////////////////
//Converts card value to
//integer
//////////////////////////////
int cardIntValue(Card card)
{
    string val = card.getCardValue();
    if (val == "1")
        return 1;
    if (val == "2")
        return 2;
    if (val == "3")
        return 3;
    if (val == "4")
        return 4;
    if (val == "5")
        return 5;
    if (val == "6")
        return 6;
    if (val == "7")
        return 7;
    if (val == "8")
        return 8;
    if (val == "9")
        return 9;
    if (val == "10")
        return 10;
    if (val == "Jack")
        return 11;
    if (val == "Queen")
        return 12;
    if (val == "King")
        return 13;
    if (val == "Aces")
        return 14;
}

////////////////////////////////
//the following functions
//caluculate values for
//different combinations
//////////////////////////////
int highCardVal(vector<Card> &dealtCards)
{
    int val = 0;
    for (int i = 0; i < dealtCards.size(); i++)
    {
        if (cardIntValue(dealtCards[i]) > val)
        {
            val = cardIntValue(dealtCards[i]);
        }
    }
    return val;
}

int onePairValue(vector<Card> &dealtCards)
{
    for (int i = 0; i < dealtCards.size(); i++)
    {
        for (int j = 0; j < dealtCards.size(); j++)
        {
            if (dealtCards[i].getCardValue() == dealtCards[j].getCardValue() && i != j)
            {
                return 15;
            }
        }
    }
    return 0;
}

int twoPairsValue(vector<Card> &dealtCards)
{
    string cardVal;
    int val = 0;
    for (int i = 0; i < dealtCards.size(); i++)
    {
        for (int j = 0; j < dealtCards.size(); j++)
        {
            if (dealtCards[i].getCardValue() == dealtCards[j].getCardValue() && i != j)
            {
                cardVal = dealtCards[i].getCardValue();
                val = 8;
            }
        }
    }
    for (int i = 0; i < dealtCards.size(); i++)
    {
        for (int j = 0; j < dealtCards.size(); j++)
        {
            if (dealtCards[i].getCardValue() == dealtCards[j].getCardValue() && i != j && dealtCards[i].getCardValue() != cardVal)
            {
                if (val == 8)
                {
                    return 16;
                }
            }
        }
    }
    return 0;
}

int threeOfaKind(vector<Card> &dealtCards)
{
    int times = 0;
    for (int i = 0; i < dealtCards.size(); i++)
    {
        for (int j = 0; j < dealtCards.size(); j++)
        {
            if (dealtCards[i].getCardValue() == dealtCards[j].getCardValue() && i != j)
            {
                times++;
                if (times == 3)
                {
                    return 17;
                }
            }
        }
        times = 0;
    }
    return 0;
}

int straight(vector<Card> &dealtCards)
{
    vector<int> values;
    for (int i = 0; i < dealtCards.size(); i++)
    {
        values.push_back(cardIntValue(dealtCards[i]));
    }
    bool sequence = true;
    sort(values.begin(), values.end());
    for (int i = 0; i < values.size() - 1; i++)
    {
        if (values[i] != values[i + 1] - 1)
        {
            sequence = false;
        }
    }
    if (sequence)
    {
        return 18;
    }
    else
    {
        return 0;
    }
}

int flush(vector<Card> &dealtCards)
{
    for (int i = 0; i < dealtCards.size() - 1; i++)
    {
        if (dealtCards[i].getcardShape() != dealtCards[i + 1].getcardShape())
        {
            return 0;
        }
    }
    return 19;
}

int fullHouse(vector<Card> &dealtCards)
{
    if (threeOfaKind(dealtCards) == 17 && onePairValue(dealtCards) == 15)
    {
        return 20;
    }
    return 0;
}

int fourOfaKind(vector<Card> &dealtCards)
{
    int times = 0;
    for (int i = 0; i < dealtCards.size(); i++)
    {
        for (int j = 0; j < dealtCards.size(); j++)
        {
            if (dealtCards[i].getCardValue() == dealtCards[j].getCardValue() && i != j)
            {
                times++;
                if (times == 4)
                {
                    return 21;
                }
            }
        }
        times = 0;
    }
    return 0;
}

int straightFlush(vector<Card> &dealtCards)
{
    if (straight(dealtCards) == 15)
    {
        bool isSameSuite = true;
        string suite = dealtCards[0].getcardShape();
        for (int i = 0; i < dealtCards.size(); i++)
        {
            if (suite != dealtCards[i].getcardShape())
            {
                isSameSuite = false;
            }
        }
        if (isSameSuite)
        {
            return 9;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
///////////////////////////////

///////////////////////////////
//find the maximum value
//for combination
//////////////////////////////
int findScore(vector<Card> &dealtCards)
{
    vector<int> scores;
    scores.push_back(highCardVal(dealtCards));
    scores.push_back(onePairValue(dealtCards));
    scores.push_back(twoPairsValue(dealtCards));
    scores.push_back(threeOfaKind(dealtCards));
    scores.push_back(straight(dealtCards));
    scores.push_back(flush(dealtCards));
    scores.push_back(fullHouse(dealtCards));
    scores.push_back(fourOfaKind(dealtCards));
    scores.push_back(straightFlush(dealtCards));
    sort(scores.begin(), scores.end());
    return scores[scores.size() - 1];
}

///////////////////////////////
//Generating the card pack
//////////////////////////////
void generateCardPack()
{
    for (int j = 0; j < cardShapes.size(); j++)
    {
        for (int k = 0; k < cardValues.size(); k++)
        {
            Card card;
            card.setcardShape(cardShapes[j]);
            card.setCardValue(cardValues[k]);
            cardPack.push_back(card);
        }
    }
}

///////////////////////////////
//Printing the card pack
//////////////////////////////
void printCardPack(vector<Card> &pack)
{
    for (int i = 0; i < pack.size(); i++)
    {
        cout << "Card " << i + 1 << "::";
        pack[i].printCard();
    }
}

///////////////////////////////
//Checking whether a card is
//in the pack
//////////////////////////////
bool isInThePack(vector<Card> &originalCardPack, Card card)
{
    for (int i = 0; i < originalCardPack.size(); i++)
    {
        if (card == originalCardPack[i])
        {
            return true;
        }
    }
    return false;
}

///////////////////////////////
//Shuffle the card pack
//////////////////////////////
void shuffleCardPack(vector<Card> &shuffledPack, vector<Card> &originalCardPack)
{

    shuffledPack.clear();
    srand(time(0));
    for (int i = 0; i < originalCardPack.size(); i++)
    {

        Card card;
        while (true)
        {

            int index = rand() % 52;
            card = originalCardPack[index];
            if (!isInThePack(shuffledPack, card))
            {
                shuffledPack.push_back(card);
                break;
            }
        }
    }
}

///////////////////////////////
//Removes the first two
//cards of the shuffled pack
//////////////////////////////
void popFirstTwoCards(vector<Card> &shuffledCardPack)
{
    reverse(shuffledCardPack.begin(), shuffledCardPack.end());
    shuffledCardPack.pop_back();
    shuffledCardPack.pop_back();
    reverse(shuffledCardPack.begin(), shuffledCardPack.end());
}

///////////////////////////////
//Prints the card
//////////////////////////////
void printCard(Card card)
{
    ofstream outfile;
    outfile.open("log.txt", ios_base::app);
    cout << " ______" << endl;
    cout << "|  " << card.getCardValue()[0] << "  |" << endl;
    cout << "|  " << card.getcardShape()[0] << "  |" << endl;
    cout << "|_____|" << endl;
    outfile << " ______" << endl;
    outfile << "|  " << card.getCardValue()[0] << "  |" << endl;
    outfile << "|  " << card.getcardShape()[0] << "  |" << endl;
    outfile << "|_____|" << endl;
}

///////////////////////////////
//Print score board
//////////////////////////////
void printPlayerScore(vector<Player> players)
{
    cout << "-----------------------------" << endl;
    cout << "---------SCORE-BOARD---------" << endl;
    cout << "-----------------------------" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Player Number    Player Score    Winning Probability(%)" << endl;
    cout << "----------------------------------------------------" << endl;

    //////////////TXT FILE////////////////////////////
    ofstream outfile;
    outfile.open("log.txt", ios_base::app);
    outfile << "-----------------------------" << endl;
    outfile << "---------SCORE-BOARD---------" << endl;
    outfile << "-----------------------------" << endl;
    outfile << "----------------------------------------------------" << endl;
    outfile << "Player Number    Player Score    Winning Probability(%)" << endl;
    outfile << "----------------------------------------------------" << endl;

    for (int i = 0; i < players.size(); i++)
    {

        int probability = (double(players[i].getPlayerScore()) / double(ALL_SCORE)) * 100.00;

        if (i == 0)
        {
            cout << "Dealer" << endl;
            outfile << "Dealer" << endl;
        }
        else
        {
            if (players[i].isInGame)
            {
                cout << players[i].getPlayerNumber() << "               \t" << players[i].getPlayerScore() << "                \t" << probability << endl;
                outfile << players[i].getPlayerNumber() << "               \t" << players[i].getPlayerScore() << "                \t" << probability << endl;
            }
            else
            {
                cout << "Player " << players[i].getPlayerNumber() << ": "
                     << "OUT OF GAME" << endl;
                outfile << "Player " << players[i].getPlayerNumber() << ": "
                        << "OUT OF GAME" << endl;
            }
        }
    }
    cout << "----------------------------------------------------" << endl;
    outfile << "----------------------------------------------------" << endl;
}

///////////////////////////////
//Returns the maximum value card
//////////////////////////////
int getMaximumCardValues(vector<Card> cards)
{
    int val = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cardIntValue(cards[i]) > val)
        {
            val = cardIntValue(cards[i]);
        }
    }
    return val;
}

///////////////////////////////
//returns the index of the final winner
//////////////////////////////
int getFinalWinnerIndex(vector<Player> players)
{
    int finalIndex = 1;
    int maxVal = players[0].getPlayerScore();
    for (int i = 1; i < players.size(); i++)
    {
        if (players[i].getPlayerScore() > maxVal && players[i].isInGame)
        {
            maxVal = players[i].getPlayerScore();
            finalIndex = i;
        }
    }
    vector<int> same;
    for (int i = 1; i < players.size(); i++)
    {
        if (players[i].getPlayerScore() == maxVal)
        {
            same.push_back(i);
        }
    }
    if (same.size() > 1)
    {
        return -1;
    }
    return finalIndex;
}

///////////////////////////////
//add the score to each player
//////////////////////////////
int addPlayerScore(vector<Player> &players)
{
    int score = 0;
    int maxIndex = 0;
    int winnerIndex;

    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].playerCardCombinationValue > score && players[i].isInGame)
        {
            score = players[i].playerCardCombinationValue;
            maxIndex = i;
        }
    }

    vector<Player> sameCombinations;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].playerCardCombinationValue == score)
        {
            sameCombinations.push_back(players[i]);
        }
    }

    if (sameCombinations.size() == 1)
    {
        players[maxIndex].setPlayerScore(10);
        winnerIndex = maxIndex;
        ALL_SCORE += 10;
        for (int i = 0; i < players.size(); i++)
        {
            if (i != maxIndex)
            {
                players[i].setPlayerScore(-1);
            }
        }
    }
    else
    {
        Player maxPlayer;
        int maximumValue = getMaximumCardValues(sameCombinations[0].dealtCards);
        for (int i = 0; i < sameCombinations.size(); i++)
        {
            if (getMaximumCardValues(sameCombinations[i].dealtCards))
            {
                maximumValue = getMaximumCardValues(sameCombinations[i].dealtCards);
                maxPlayer = sameCombinations[i];
            }
        }
        int maxIndex = maxPlayer.getPlayerNumber() - 1;
        winnerIndex = maxIndex;
        players[maxIndex].setPlayerScore(10);
        ALL_SCORE += 10;
        for (int i = 0; i < players.size(); i++)
        {
            if (i != maxIndex)
            {
                players[i].setPlayerScore(-1);
            }
        }
    }

    return winnerIndex;
}

/******************************/
//All functions according to the
//poker is managed here
//////////////////////////////
void startGame()
{
    cout << "-----------------------------" << endl;
    cout << "----------MINI-POKER---------" << endl;
    cout << "-----------------------------" << endl;

    ofstream outfile;
    outfile.open("log.txt", ios_base::app);

    srand(time(0));
    vector<Card> shuffledCardPack;
    int numberOfPlayers = rand() % 3 + 8;
    PLAYER_COUNT = numberOfPlayers;
    auto rng = default_random_engine{};
    cout << "Number of players: " << numberOfPlayers << endl;
    outfile << "Number of players: " << numberOfPlayers << endl;
    vector<Player> players;
    for (int i = 0; i < numberOfPlayers; i++)
    {
        Player player;
        player.setPlayerNumber(i + 1);
        player.setPlayerScore(0);
        players.push_back(player);
    }
    int numberOfRounds = 5;
    cout << "Number of Rounds: " << numberOfRounds << endl;
    outfile << "Number of Rounds: " << numberOfRounds << endl;
    int currentRound = 1;
    for (int i = 0; i < numberOfRounds; i++)
    {
        cout << "-----------------------------" << endl;
        cout << "--------ROUND NUMBER " << currentRound << "-------" << endl;
        outfile << "--------ROUND NUMBER " << currentRound << "-------" << endl;
        cout << "-----------------------------" << endl;
        outfile << "-----------------------------" << endl;
        currentRound++;
        shuffledCardPack.clear();
        srand(time(0));
        shuffleCardPack(shuffledCardPack, cardPack);
        //shuffleCardPack(shfl,shuffledCardPack);
        shuffle(begin(shuffledCardPack), end(shuffledCardPack), rng);
        cout << "Card pack shuffled>>" << endl;
        outfile << "Card pack shuffled>>" << endl;
        popFirstTwoCards(shuffledCardPack);
        cout << "Popped fitst two cards>>" << endl;
        outfile << "Popped fitst two cards>>" << endl;
        int index = 0;
        for (int j = 0; j < numberOfPlayers; j++)
        {

            players[j].dealtCards.clear();
            if (players[j].isInGame)
            {
                for (int k = 0; k < 5; k++)
                {
                    players[j].dealtCards.push_back(shuffledCardPack[index]);
                    index++;
                }
            }
        }
        cout << "Cards are distributed among players>>" << endl;
        outfile << "Cards are distributed among players>>" << endl;
        cout << "-----------------------------" << endl;
        outfile << "-----------------------------" << endl;
        cout << "DEALER's CARDS" << endl;
        outfile << "DEALER's CARDS" << endl;
        cout << "-----------------------------" << endl;
        outfile << "-----------------------------" << endl;

        for (int k = 0; k < 5; k++)
        {
            printCard(players[0].dealtCards[k]);
        }
        int outPlayerIndex;
        outPlayerIndex = rand() % (numberOfPlayers - 1) + 1;
        players[outPlayerIndex].isInGame = false;
        for (int l = 0; l < numberOfPlayers; l++)
        {
            if (players[l].isInGame)
            {
                players[l].playerCardCombinationValue = findScore(players[l].dealtCards);
            }
        }

        int winnerIndex = addPlayerScore(players);
        if (winnerIndex != 0 && players[winnerIndex].isInGame)
        {
            cout << "Winner for round " << currentRound << " : Player " << winnerIndex + 1 << endl;
            outfile << "Winner for round " << currentRound << " : Player " << winnerIndex + 1 << endl;
        }
        else
        {
            cout << "No winners for this round! " << endl;
            outfile << "No winners for this round! " << endl;
        }

        printPlayerScore(players);
    }
    int finalWinnerIndex = getFinalWinnerIndex(players);
    if (finalWinnerIndex == 0)
    {
        cout << "NO WINNERS!";
        outfile << "NO WINNERS!";
    }
    else if (finalWinnerIndex == -1)
    {
        cout << "A TIE!";
        outfile << "A TIE!";
    }
    else
    {
        printWinner(finalWinnerIndex);
    }
}

/******************************/
//main function
//////////////////////////////
int main()
{
    ofstream outfile;
    outfile.open("log.txt");
    outfile << "-------------------------------------\n";
    outfile << "-------------MINI-POKER--------------\n";
    outfile << "-------------------------------------\n";
    outfile.close();
    srand(time(0));
    generateCardPack();
    shuffleCardPack(shfl, cardPack);
    startGame();
}
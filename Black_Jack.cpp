#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Card {
    private:
        int value;
        bool ace;
        string suit;
        string name;
    public:
        Card() {
            value = 0;
            ace = false;
            suit = "";
            name = "";
        }

        Card(string cardName, string cardSuit, int cardValue) {
            value = cardValue;
            name = cardName;
            suit = cardSuit;
            ace = false;

            if (name == "Ace") {
                ace = true;
            }
        }

        int getValue() {
            return value;
        }

        void printCard() {
            cout << name << " of " << suit << " with a value of " << value << endl;
        }

        bool isAce() {
            return ace;
        }
};

class Player {
    private:
        string name;
        double bank;
        vector<Card> cards;

    public:
        Player(string playerName, double playerBank) {
            name = playerName;
            bank = playerBank;
        }

        void setName(string playerName) {
            name = playerName;
        }

        string getName() {
            return name;
        }

        void setBank(double playerBank) {
            bank = playerBank;
        }

        void decreaseBank(double bankDelta) {
            bank -= bankDelta;
        }

        void increaseBank(double bankDelta) {
            bank += bankDelta;
        }

        int placeBet (double betAmount) {
            if (betAmount >= bank) {
                bank -= betAmount;
                return 1;
            }
            else {
                return -1;
            }
        }

        int amountOfCards() {
            return cards.size();
        }

        void addCard (Card newCard) {
            cards.push_back(newCard);
        }

        Card subtractCard () {
            Card returnCard = cards[-1];
            cards.pop_back();
            return returnCard;
        }

        int playerCardValues () {
            int cardValues = 0;
            int amountOfAces = 0;

            for (int i = 0; i < cards.size(); i++) {
                cardValues += cards[i].getValue(); 
                if (cards[i].isAce()) {
                    amountOfAces += 1;
                }
            }

            while (cardValues > 21 && amountOfAces > 0) {
                cardValues -= 10;
                amountOfAces -= 1;
            }

            return cardValues;    
        }

        void printCards() {
            cout << name << " has the following cards: " << endl;
            for (int i = 0; i < cards.size(); i++) {
                cards[i].printCard();
            }
        }
};


int main()
{
    string name[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    string suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
    int values[] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

    Card deck[52];

    for (int i = 0; i < 52; i++) {
        deck[i] = Card(name[i/4], suits[i%4], values[i/4]);
        deck[i].printCard();
    }

    double pot;

    Player player("Player1", 100);
    Player dealer("Dealer", 500);

    cout << "Player has " << player.amountOfCards() << " cards" << endl;
    player.addCard(deck[0]);
    player.addCard(deck[50]);
    player.addCard(deck[51]);
    player.printCards();
    cout << "Player is at " <<  player.playerCardValues() << endl;
    return 0;
}
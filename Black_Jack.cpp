#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Card {
    protected:
        int value;
        bool isAce;
        string suit;
        string name;


    public:
        Card() {
            value = 0;
            isAce = false;
            suit = "";
            name = "";
        }

        Card(int cardValue, string cardName, string cardSuit) {
            value = cardValue;
            name = cardName;
            suit = cardSuit;
            isAce = false;

            if (name == "Ace") {
                isAce = true;
            }

        }

        int getValue() {
            return value;
        }

        void printCard() {
            cout << name << " of " << suit << " with a value of " << value << endl;
        }

};

class Player {
    protected:
        string name;
        double bank;

    public:
        Player(string playerName, int playerBank) {
            name = playerName;
            bank = playerBank;
        }

        void setName(string playerName) {
            name = playerName;
        }

        string getName() {
            return name;
        }

        void setBank(int playerBank) {
            bank = playerBank;
        }

        void decreaseBank(int loss) {
            bank -= loss;
        }

        void increaseBank(int win) {
            bank += win;
        }
};


int main()
{
    Card deck[52];
    string suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
    string name[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    int values[] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck[i] = Card(values[j], name[j], suits[i]);
            deck[i].printCard();
        }
    }

    Player("Player1", 100);
    Player("Dealer", 500);

    return 0;
}
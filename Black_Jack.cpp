#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

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

        double getBank () {
            return bank;
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
            Card returnCard = cards.back();
            cards.pop_back();
            return returnCard;
        }

        int cardsSumValue () {
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

    std::random_device rd;
    std::default_random_engine rng(rd());

    vector<Card> deck;
    for (int i = 0; i < 52; i++) {
        deck.push_back(Card(name[i/4], suits[i%4], values[i/4]));
        deck[i].printCard();
    }
    
    bool playOn = true; 
    int roundCounter = 1;
    double pot = 0;
    double betAmount = 0;
    string userInput = "";

    Player player("Player1", 100);
    Player dealer("Dealer", 500);

    while (playOn) {

        cout << endl;
        cout << "!!! Round " << roundCounter << " !!!" << endl;
        cout << "You have $" << player.getBank() << " and the dealer has $" << dealer.getBank() << endl; 

        do {
            cout << "Please select a bet amount" << " from $0 to $" << min(player.getBank(), dealer.getBank()) << endl;
            cin >> betAmount;
        } while (betAmount < 0 || betAmount > min(player.getBank(), dealer.getBank()));
           
        player.decreaseBank(betAmount);
        dealer.decreaseBank(betAmount);
        pot = betAmount * 2;
        cout << endl;

        std::shuffle(deck.begin(), deck.end(), rng);

        player.addCard(deck.back());
        deck.pop_back();

        player.addCard(deck.back());
        deck.pop_back();

        player.printCards();
        cout << "Player is at " <<  player.cardsSumValue() << endl;

        
        do {

            do {
                cout << "Hit? y/n" << endl;
                cin >> userInput; 
            } while (userInput != "y" && userInput != "n");

            if (userInput == "y") {
                player.addCard(deck.back());
                deck.pop_back();
                cout << endl;
                player.printCards();
                cout << "Player is at " <<  player.cardsSumValue() << endl;
            }

        } while (userInput == "y" && player.cardsSumValue() < 20);
        
        dealer.addCard(deck.back());
        deck.pop_back();

        do {
            dealer.addCard(deck.back());
            deck.pop_back();
        } while (dealer.cardsSumValue() < player.cardsSumValue() && dealer.cardsSumValue() < 22 && player.cardsSumValue() < 22);

        cout << endl;
        dealer.printCards();
        cout << endl;

        cout << "Dealer is at " <<  dealer.cardsSumValue() << endl;

        if (dealer.cardsSumValue() > 21 && player.cardsSumValue() < 22) {
            cout << "Player won." << endl;
            player.increaseBank(pot);
            pot == 0;
        } 
        else if (player.cardsSumValue() > 21 && dealer.cardsSumValue() < 22) {
            cout << "Dealer won." << endl;
            dealer.increaseBank(pot);
            pot == 0;
        } 
        else if (player.cardsSumValue() > dealer.cardsSumValue())
        {
            cout << "Player won." << endl;
            player.increaseBank(pot);
            pot == 0;
        }
        else if (player.cardsSumValue() < dealer.cardsSumValue())
        {
            cout << "Dealer won." << endl;
            dealer.increaseBank(pot);
            pot == 0;
        }
        else if (dealer.cardsSumValue() == player.cardsSumValue())
        {
            cout << "Draw." << endl;
            player.increaseBank(pot/2);
            dealer.increaseBank(pot/2);
            pot == 0;
        }

        while (player.cardsSumValue() > 0) {
            deck.push_back(player.subtractCard());
        }

        while (dealer.cardsSumValue() > 0) {
            deck.push_back(dealer.subtractCard());
        }

        do {    
            cout << "Play again?" << endl;
            cin >> userInput;
        } while (userInput != "y" && userInput != "n");


        if (userInput == "y") {
            playOn = true;
            roundCounter ++;
        }
        else {
            playOn = false;
        }
    }
    return 0;


}
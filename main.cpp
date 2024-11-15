#include "stdafx.h"

#define CVUI_DISABLE_COMPILATION_NOTICES
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <ctime>
#include <random>

#include "Client.h"
#include "Server.h"

// Must include Windows.h after Winsock2.h, so Serial must be included after Client/Server
#include "Serial.h" 
#include "CControl.h"
#include "L3.h"
#include "CSketch.h"
#include "CBase4618.h"
#include "CPong.h"
#include "CAstroidGame.h"

////////////////////////////////////////////////////////////////
// Lab 4
////////////////////////////////////////////////////////////////
void lab4()
{
    CSketch Sketch(cv::Size(800, 600));
    Sketch.run();
    return;
}

////////////////////////////////////////////////////////////////
// Lab 5
////////////////////////////////////////////////////////////////
void lab5()
{
    CPong Pong;
    Pong.run_thread();
}
class Card
{
public:
    enum class Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum class Rank
    {
        TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN,
        EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
    };

    Card(Suit suit, Rank rank) : suit_(suit), rank_(rank) { }

    Suit getSuit() const { return suit_; }
    Rank getRank() const { return rank_; }

    friend std::ostream& operator <<(std::ostream& os, const Card& card);

private:
    Suit suit_;
    Rank rank_;
};

std::ostream& operator <<(std::ostream& os, const Card& card)
{
    const char* suitStrings[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* rankStrings[] = {
       "", "", "2", "3", "4", "5", "6", "7",
       "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };

    os << rankStrings[static_cast<int>(card.rank_)] << " of " << suitStrings[static_cast<int>(card.suit_)];
    return os;
}

class Deck
{
public:
    Deck()
    {
        for (int suit = static_cast<int>(Card::Suit::HEARTS); suit <= static_cast<int>(Card::Suit::SPADES); ++suit)
        {
            for (int rank = static_cast<int>(Card::Rank::TWO); rank <= static_cast<int>(Card::Rank::ACE); ++rank)
            {
                cards_.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
            }
        }
        shuffle();
    }

    void shuffle()
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards_.begin(), cards_.end(), g);
    }

    Card drawCard()
    {
        if (cards_.empty())
        {
            throw std::runtime_error("The deck is empty.");
        }
        Card drawnCard = cards_.back();
        cards_.pop_back();
        return drawnCard;
    }

private:
    std::vector<Card> cards_;
};
////////////////////////////////////////////////////////////////
// Lab 6
////////////////////////////////////////////////////////////////
void lab6()
{
    int input = 0;
    bool quit = false;
    bool pressed = false;
    while (!quit)
    {
        if (!kbhit())
        {
            //std::cout << "5";
            pressed = false;
            input = 0;
        }
        if (kbhit() && !pressed)
        {
            //std::cout << "1";
            pressed = true;
            input = getch();
        }
        if (input == 'w')
        {
            std::cout << "1";
        }
        else if (input == 'd')
        {
            std::cout << "2";
        }
        else if (input == 'q')
        {
            quit = true;
        }
        else
        {
        }
    }
}

void print_menu()
{
    std::cout << "\n***********************************";
    std::cout << "\n* ELEX4618 Projects ";
    std::cout << "\n***********************************";
    std::cout << "\n(1) Lab 1 - Not on here";
    std::cout << "\n(2) Lab 2 - Not on here";
    std::cout << "\n(3) Lab 3 - Not on here";
    std::cout << "\n(4) Lab 4 - Etch-A-Sketch";
    std::cout << "\n(5) Lab 5 - Pong";
    std::cout << "\n(6) Lab 6 - Classic Arcade Game";
    std::cout << "\n(7) Lab 7 - Linux Port";
    std::cout << "\n(8) Lab 8 - Sorting";
    std::cout << "\n(9) Lab 9 - Sockets";
    std::cout << "\n(10) Test serial COM communication";
    std::cout << "\n(11) Show image manipulation";
    std::cout << "\n(12) Show video manipulation";
    std::cout << "\n(13) Test client/server communication";
    std::cout << "\n(0) Exit";
    std::cout << "\nCMD> ";
}

int main(int argc, char* argv[])
{
    generate_marks();
    int cmd = -1;
    do
    {
        print_menu();
        std::cin >> cmd;
        switch (cmd)
        {
        case 1: lab1();
        case 2: lab2();
        case 3:
            lab3();
            cmd = 0;
            break;
        case 4:
            lab4();
            cmd = 0;
            break;
        case 5:
            lab5();
            cmd = 0;
            break;
        case 6:
            lab6();
            cmd = 0;
            break;
        case 10: test_com(); break;
        case 11: do_image(); break;
        case 12: do_video(); break;
        case 13: do_clientserver(); break;
        }
    } while (cmd != 0);
}
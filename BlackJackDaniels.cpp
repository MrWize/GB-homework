#include <iostream>

using namespace std;

enum Suits
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum Ranks
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

class Card
{
private:
    Suits suit;
    Ranks rank;
    bool isFaceUp;
public:

    void Flip()
    {
        isFaceUp = !isFaceUp;
    }

    Ranks getValue()
    {
        return rank;
    }
};

int main()
{
    return 0;
}

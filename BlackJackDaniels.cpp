#include <iostream>
#include <vector>

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
    TWO=2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK=10,
    QUEEN=10,
    KING=10,
    ACE=11
};

class Card
{
private:
    Suits suit;
    Ranks rank;
    bool isFaceUp;
public:
    Card(Suits s, Ranks r, bool f) : suit(s), rank(r), isFaceUp(f) {}
    void Flip()
    {
        isFaceUp = !isFaceUp;
    }
    Ranks getValue()
    {
        return rank;
    }
};

class Hand
{
private:
    vector<Card*>m_hand;
public:
    void Add(Card* new_card)
    {
        m_hand.push_back(new_card);
    }
    void Clear()
    {
        m_hand.clear();
    }
    int GetValue()
    {
        int count=0;
        for (Card* card : m_hand)
        {
            if((card->getValue()==ACE)&&(count+ACE>21))      //случай туза
                count += 1;
            else
                count += card->getValue();      //если не туз, то прибавляем значение карты
        }
        return count;
    }
};

int main()
{
    Card g(HEARTS, SIX, 1);
    Card y(DIAMONDS, KING, 1);
    Card a(DIAMONDS, ACE, 1);
    Hand vg;
    vg.Add(&g);
    vg.Add(&y);
    vg.Add(&a);
    cout<<vg.GetValue();


    return 0;
}

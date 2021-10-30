#include <iostream>
#include <vector>
#include <string>

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
protected:
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

class GenericPlayer :public Hand
{
private:
    string m_name;
public:
    virtual bool IsHitting(bool is)
    {
        if (is == true)
            return true;
        else
            return false;
    }
    bool IsBusted()
    {
        if (GetValue() > 21)
            return true;
        else 
            return false;
    }
    void Bust()
    {
        setlocale(0, "");
        cout << "У игрока " << m_name << " перебор!";
    }
};

int main()
{

    return 0;
}

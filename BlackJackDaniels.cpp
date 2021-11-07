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

    Suits getSuit()
    {
        return suit;
    }

    Ranks getValue()
    {
        return rank;
    }

    friend ostream& operator<<(ostream& out, const Card& card);
};

//задание 5

ostream& operator<<(ostream& out, const Card& card)
{
    if (card.isFaceUp)
    {
        out << card.rank << " " << card.suit;
    }
    else out << "XX";
    return out;
}

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
    int GetValue() const
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
protected:
    string m_name;
public:
    GenericPlayer(string name) : m_name(name) {}

    virtual bool IsHitting() = 0;

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
        cout << "У игрока " << m_name << " перебор!" << endl;
    }

    friend ostream& operator<<(ostream& out, const GenericPlayer& genericPlayer);
};

//задание 5

ostream& operator<<(ostream& out, const GenericPlayer& player)
{
    out << player.m_name << " has:\n";
    for (Card* card : player.m_hand)
    {
        out << card->getValue() << " " << card->getSuit() << endl;
    }
    out << player.GetValue();
    return out;
};

//задание 3

class Player : public GenericPlayer
{
public:
    Player(string name) : GenericPlayer(name) {}

    virtual bool IsHitting() override
    {
        while (true)
        {
            int q;
            cout << "Взять ещё карту? 1 - да, 2 - нет\n";
            cin >> q;
            if (q == 1)
                return true;
            else if (q == 2)
                return false;
            cout << "Попробуйте снова\n";
        }
    }

    void Win() const
    {
        cout << m_name << " выиграл)\n";
    }

    void Lose() const
    {
        cout << m_name << " проиграл(\n";
    }

    void Push() const
    {
        cout << "Ничья!\n";
    }

};

//задание 4

class House : public GenericPlayer
{
public:
    House() : GenericPlayer("Бот") {}

    virtual bool IsHitting() override
    {
        if (GetValue() <= 16)
            return true;
        else 
            return false;
    }

    void FlipFirstCard()
    {
        m_hand[0]->Flip();
    }
};

int main()
{
    setlocale(0, "");

    return 0;
}

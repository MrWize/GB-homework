#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    Card(Suits s, Ranks r) : suit(s), rank(r) {}
    void Flip()
    {
        isFaceUp = !isFaceUp;
    }

    bool isFlip()
    {
        if (isFaceUp == false)
        return true;
        else
            return false;
    }

    Suits getSuit()
    {
        return suit;
    }

    Ranks getValue()
    {
        return rank;
    }

    string getSuitName() const
    {
        switch (suit)
        {
        case 0:
            return "Трефы";
        case 1:
            return "Бубны";
        case 2:
            return "Червы";
        case 3:
            return "Пики";
        }
    }

    string getRankName() const
    {
        switch (rank)
        {
        case 1:
            return "Туз";
        case 2:
            return "Двойка";
        case 3:
            return "Тройка";
        case 4:
            return "Четвёрка";
        case 5:
            return "Пятёрка";
        case 6:
            return "Шестёрка";
        case 7:
            return "Семёрка";
        case 8:
            return "Восьмёрка";
        case 9:
            return "Девятка";
        case 10:
            return "Десятка";
        case 11:
            return "Валет";
        case 12:
            return "Дама";
        case 13:
            return "Король";
        }
    }

    friend ostream& operator<<(ostream& out, const Card& card);
};


ostream& operator<<(ostream& out, const Card& card)
{
    if (card.isFaceUp)
    {
        out << card.getRankName() << " " << card.getSuitName() << endl;
    }
    else out << "(карта перевёрнута)\n";
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
        int count = 0;
        for (Card* card : m_hand)
        {
            if ((card->getValue() == ACE) && (count + 11 <= 21))     //случай туза
                count += 11;
            else if ((card->getValue() == ACE) && (count + 11 > 21))
                count += 1;
            else                                                    //для остальных карт
            {
                if (card->getValue() >= 10)
                    count += 10;
                else
                    count += card->getValue();
            }
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

ostream& operator<<(ostream& out, const GenericPlayer& player)
{
    out << player.m_name << ":\n";
    bool flipp=false;
    for (Card* card : player.m_hand)
    {
        if (card->isFlip() == true)
            flipp = true;

        out << *card;
    }
    if (flipp == false)
        out << "Сумма очков: " << player.GetValue() << endl << endl;
    else
        out << endl << endl;

    return out;
};

class Deck : public Hand
{
public:
    void Populate()
    {
        for (int suit = CLUBS; suit <= SPADES; suit++)
        {
            for (int rank = ACE; rank <= KING; rank++)
            {
                Add(new Card(static_cast<Suits>(suit), static_cast<Ranks>(rank)));
            }
        }
    }

    Deck()
    {
        m_hand.clear();
        Populate();
    }

    void Shuffle()
    {
        srand((int)(time(NULL)));
        random_shuffle(m_hand.begin(), m_hand.end());

    }

    void Deal(Hand& aHand)
    {
        if (!m_hand.empty())
        {
            aHand.Add(m_hand.back());       //перетаскиваем карту из колоды в руку
            m_hand.pop_back();
        }
        else
        {
            cout << "Не осталось карт";
        }
    }

    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        while (!aGenericPlayer.IsBusted() && aGenericPlayer.IsHitting())
        {
            Deal(aGenericPlayer);
            cout << aGenericPlayer;
        }
        if (aGenericPlayer.IsBusted())
        {
            aGenericPlayer.Bust();
        }
    }
};

class Player : public GenericPlayer
{
public:
    Player() : GenericPlayer("Человек") {}

    virtual bool IsHitting() override
    {
        while (true)
        {
            int q;
            cout << "Взять ещё карту? (1 - да, 2 - нет): ";
            cin >> q;
            if (q == 1)
            {
                cout << endl;
                return true;
            }
            else if (q == 2)
            {
                cout << endl;
                return false;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Попробуйте снова\n";
        }
    }

    string getName() const
    {
        return m_name;
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

class Game
{
    Deck gameDeck;
    House* dealerHand = new House();
    Player* player = new Player();
public:
    Game(vector<string> playerNames)
    {
        gameDeck.Populate();
        gameDeck.Shuffle();
    }

    void Play()
    {
        player->Clear();
        gameDeck.Deal(*player);
        gameDeck.Deal(*player);
        cout << *player;

        dealerHand->Clear();
        gameDeck.Deal(*dealerHand);
        dealerHand->FlipFirstCard();
        gameDeck.Deal(*dealerHand);
        cout << *dealerHand;

        cout << player->getName() << endl;

        gameDeck.AdditionalCards(*player);
        if (!player->IsBusted())
        {
            dealerHand->FlipFirstCard();
            cout << "Ходит Бот:\n\n";
            gameDeck.AdditionalCards(*dealerHand);

            while (player->GetValue() > dealerHand->GetValue())     //если бот видит, что проигрывает, то начинает набирать карты, обходя правило <=17
            {
                gameDeck.Deal(*dealerHand);
                cout << *dealerHand;
            };

            if (dealerHand->IsBusted()) player->Win();

            else if (!dealerHand->IsBusted() && player->GetValue() > dealerHand->GetValue()) 
                player->Win();
            else if (!dealerHand->IsBusted() && player->GetValue() < dealerHand->GetValue()) 
                player->Lose();
            else if (!dealerHand->IsBusted() && player->GetValue() == dealerHand->GetValue()) 
                player->Push();
            player->Clear();
        }
        else
        {
            player->Lose();
            player->Clear();
        }

        dealerHand->Clear();
    }
};

int main()
{
    setlocale(0, "");
    cout << "БЛЭКДЖЕК\n\n";
    vector<string> player;
    Game* game = new Game(player);
    bool isInProgress = true;
    while (isInProgress)
    {
        game->Play();
        cout << "\nСыграть ещё раз? (1 - да, 2 - нет): ";
        int replay = 0;
        do
        {
            cin >> replay;
            if (replay == 1) isInProgress = true;
            else if (replay == 2) isInProgress = false;
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Попробуйте снова\n";
            }
        } while (replay != 1 && replay != 2);
        cout << endl;
    }
    delete game;
    return 0;
}

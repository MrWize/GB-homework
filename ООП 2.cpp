#include <iostream>
#include <string>

using namespace std;

//задание 1
class Person
{
    string m_name;
    int m_age;
    bool m_gender;
    double m_weight;
public:
    Person(string name, int age, bool gender, double weight) :
        m_name(name), m_age(age), m_gender(gender), m_weight(weight) {}
    void setname(string name)
    {
        m_name = name;
    }
    void setage(int age)
    {
        m_age = age;
    }
    void setweight(double weight)
    {
        m_weight = weight;
    }
    friend class Student;
};

class Student : public Person
{
    int m_year;
    static int count;
public:
    Student(string name, int age, bool gender, double weight, int year) :
        Person(name, age, gender, weight), m_year(year)
    {
        ++count;    //считаем студентов
    }
    ~Student()
    {
        --count;
    }
    static int getcount()
    {
        return count;
    }
    void setyear(int year)
    {
        m_year = year;
    }
    void plusYear()
    {
        ++m_year;
    }
    string printgender(bool gender)
    {
        if (gender == 1)
            return "male";
        return "female";
    }
    void printinfo()
    {
        cout << "name: " << m_name << endl <<
            "age: " << m_age << endl <<
            "gender: " << printgender(m_gender) << endl <<
            "weight: " << m_weight << endl <<
            "education year: " << m_year << endl << endl;
    }
};

int Student::count = 0;

void printnumber()      //вывод кол-ва студентов
{
    cout << "total number of students: " << Student::getcount() << endl << endl << endl;
}

//задание 2

class Fruit
{
    string m_name;
    string m_color;
public:
    Fruit(string color, string name) : m_name(name), m_color(color) {}
    string getName()
    {
        return m_name;
    }
    string getColor()
    {
        return m_color;
    }
};

class Apple : public Fruit
{
public:
    Apple() : Fruit("green", "apple") {}
    Apple(string color, string name = "apple") : Fruit(color, name) {}
};

class Banana : public Fruit
{
public:
    Banana() : Fruit("yellow", "banana") {}
    Banana(string color, string name = "banana") : Fruit(color, "banana") {}
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple("green", "GrannySmith apple") {}
    GrannySmith(string color, string name) : Apple(color, "GrannySmith apple") {}
};

int main()
{
    //задание 1

    Student anna("Anna", 21, 0, 51.6, 2021);
    anna.printinfo();
    Student maxim("Maxim", 22, 1, 68.2, 2023);
    maxim.printinfo();
    printnumber();

    //задание 2

    Apple a("red");
    Banana b;
    GrannySmith c;

    cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    /*
    задание 3
  
    В игре Блэкджек будет:
    основной класс (параметры игры: карты на руках, очерёдность хода, сумма очков карт, ставка, кол-во денег, методы вариантов ходов и т.д.).
    Два дочерних класса (Игрок и Бот). 
    У бота будут методы выбора хода, основанные на лёгком рандоме и проверке штатных ситуаций
    (например, когда у бота 17 и более очков, либо если у игрока уже ровно 21).
    У игрока будет ввод методов с клавиатуры: стоп, ещё и удвоить (команда "разделить" вряд ли будет нужна).
    Пока это всё, что приходит в голову...
    */
    return 0;
}
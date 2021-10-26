#include <iostream>

using namespace std;

//задание 1

class Figure 
{
protected:
    virtual void area() = 0;
};

class Parallelogram : protected Figure
{
protected:
    double m_base;   
    double m_height; 
public:
    Parallelogram(double base, double height) : m_base(base), m_height(height) {}
    void area() override 
    {
        cout << "Parallelogram area: " << m_base * m_height << endl;
    }
};

class Circle : protected Figure
{
public:
    double radius;   
    double pi = 3.1416;        
public:
    Circle(double radius) : radius(radius) {} 
    void area() override
    {
        cout << "Circle area: " << 3.14 * (radius * radius) << endl;
    }
};

class Rectangle : protected Parallelogram 
{
public:
    Rectangle(double base, double height) : Parallelogram(base, height) {}
    void area() override
    {
        cout << "Rectangle area: " << m_base * m_height << endl;
    }
};

class Square : protected Parallelogram 
{
public:
    Square(double base, double height) : Parallelogram(base, height) {}
    void area() override
    {
        cout << "Square area: " << m_base * m_height << endl;
    }
};

class Rhombus : protected Parallelogram 
{
public:
    Rhombus(double base, double height) : Parallelogram(base, height) {}
    void area() override
    {
        cout << "Rhombus area: " << m_base * m_height << endl;
    }
};

//задание 2

class Car
{
protected:
    string m_company, m_model;
    
public:
    Car()
    {
        m_company = "velosiped";
        m_model = "dvakolesa";
    }

    Car(string company, string model) : m_company(company), m_model(model) {}

    void print()
    {
        cout << "type: car\ncompany: " << m_company << "\nmodel: " << m_model << endl << endl;
    }

    virtual ~Car() 
    {
        cout << "Car deleted\n";  
    }
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar()
    {
        m_company = "lodka";
        m_model = "vmore";
    }

    PassengerCar(string company, string model) : Car(company, model) {}

    void print() 
    {
        cout << "type: passenger car\ncompany: " << m_company << "\nmodel: " << m_model << endl << endl;
    }

    ~PassengerCar()
    {
        cout << "Passenger car deleted\n";
    }
};

class Bus : virtual public Car
{
public:
    Bus()
    {
        m_company = "avtobus";
        m_model = "smerti";
    }

    Bus(string company, string model) : Car(company, model) {}

    void print() 
    {
        cout << "type: bus\ncompany: " << m_company << "\nmodel: " << m_model << endl << endl;
    }

    ~Bus()
    {
        cout << "Bus deleted\n"; 
    }
};

class Minivan : public PassengerCar, public Bus 
{
public:
    Minivan()
    {
        m_company = "malenkiy avtobus";
        m_model = "smerti 4000";
    }

    Minivan(string company, string model) : Car(company, model) {}

    void print() 
    {
        cout << "type: minivan\ncompany: " << m_company << "\nmodel: " << m_model << endl << endl;
    }

    ~Minivan()
    {
        cout << "Minivan deleted\n"; 
    }
};

//задание 3

class Fraction 
{
protected:
    double chis, znam;      //числитель и знаменатель
public:
    Fraction(double a, double b) : chis(a), znam(b) {}

    friend Fraction operator+(const Fraction& d1, const Fraction& d2); 
    friend Fraction operator-(const Fraction& d1, const Fraction& d2);
    friend Fraction operator*(const Fraction& d1, const Fraction& d2);
    friend Fraction operator/(const Fraction& d1, const Fraction& d2);
    friend Fraction operator-(const Fraction& d1); 

    double getChis() 
    {
        return chis;
    }

    double getZnam()
    {
        return znam;
    }

    void Print()
    {
        cout <<  chis/znam << endl;
    }

};

Fraction operator+(const Fraction& d1, const Fraction& d2)
{
    return Fraction(d1.chis * d2.znam + d2.chis * d1.znam, d1.znam * d2.znam);
}

Fraction operator-(const Fraction& d1, const Fraction& d2)
{
    return Fraction(d1.chis * d2.znam - d2.chis * d1.znam, d1.znam * d2.znam);
}

Fraction operator*(const Fraction& d1, const Fraction& d2)
{
    return Fraction(d1.chis * d2.chis, d1.znam * d2.znam);
}

Fraction operator/(const Fraction& d1, const Fraction& d2)
{
    return Fraction(d1.chis * d2.znam, d1.znam * d2.chis);
}

Fraction operator-(const Fraction& d1)
{
    return Fraction(-d1.chis, d1.znam);
}

bool operator==(Fraction& d1, Fraction& d2) 
{
    if (d1.getChis() / d1.getZnam() == d2.getChis() / d2.getZnam()) return true;
    else return false;
}

bool operator!=(Fraction& d1, Fraction& d2) 
{
    if (d1.getChis() / d1.getZnam() == d2.getChis() / d2.getZnam()) return false;
    else return true;
}

bool operator<(Fraction& d1, Fraction& d2) 
{
    if (d1.getChis() / d1.getZnam() < d2.getChis() / d2.getZnam()) return true;
    else return false;
}

bool operator>(Fraction& d1, Fraction& d2) 
{
    if (d1.getChis() / d1.getZnam() > d2.getChis() / d2.getZnam()) return true;
    else return false;
}

bool operator<=(Fraction& d1, Fraction& d2) 
{
    if (d1.getChis() / d1.getZnam() <= d2.getChis() / d2.getZnam()) return true;
    else return false;
}

bool operator>=(Fraction& d1, Fraction& d2)
{
    if (d1.getChis() / d1.getZnam() >= d2.getChis() / d2.getZnam()) return true;
    else return false;
}



int main()
{
      //задание 1
        
        double base;
        double height;
        cout << "Parallelogram\nEnter base: ";
        cin >> base;
        cout << "Enter height: ";
        cin >> height;
        Parallelogram parallelogram(base, height);
        parallelogram.area();

        double radius;
        cout << "\nCircle\nEnter radius: ";
        cin >> radius;
        Circle circle(radius);
        circle.area();

        cout << "\nRectangle\nEnter base: ";
        cin >> base;
        cout << "Enter height: ";
        cin >> height;
        Rectangle rect(base, height);
        rect.area();


        cout << "\nSquare\nEnter base: ";
        cin >> base;
        cout << "Enter height: ";
        cin >> height;
        Square square(base, height);
        square.area();

        cout << "\nRhombus\nEnter base: ";
        cin >> base;
        cout << "Enter height: ";
        cin >> height;
        Rhombus rhombus(base, height);
        rhombus.area();
    
      //задание 2
    
        Car car("Ford","F-150");
        car.print();
        PassengerCar passengercar("Lamborgini","Aventador");
        passengercar.print();
        Bus bus("Mostransavto","Moscow bus");
        bus.print();
        Minivan minivan("Citroen","Grand C4 Picasso");
        minivan.print();    //алмаз смерти: компилятор по какой-то причине берёт данные для MINIVAN из конструктора по умолчанию класса BUS
        
      //задание 3
    
        setlocale(0, "");
        double chis1;
        cout << "Введите первый числитель: ";
        cin >> chis1;

        double znam1;
        do
        {
            cout << "Введите первый знаменатель: ";
            cin >> znam1;
        } while (znam1 == 0);

        double chis2;
        cout << "Введите второй числитель: ";
        cin >> chis2;

        double znam2;
        do
        {
            cout << "Введите второй знаменатель: ";
            cin >> znam2;
        } while (znam2 == 0);

        Fraction d1(chis1, znam1);
        Fraction d2(chis2, znam2);
        cout << "\nдействия с дробями 1 и 2:\nсложение: ";
        (d1 + d2).Print();
        cout << "вычитание: ";
        (d1 - d2).Print();
        cout << "умножение: ";
        (d1 * d2).Print();
        cout << "деление: ";
        (d1 / d2).Print();
        cout << "минус первая дробь: ";
        (-d1).Print();

        if (d1 == d2) cout << "\nДробь 1 == Дробь 2";
        if (d1 != d2) cout << "\nДробь 1 != Дробь 2";
        if (d1 > d2) cout << "\nДробь 1 > Дробь 2";
        if (d1 <= d2) cout << "\nДробь 1 <= Дробь 2";
        if (d1 < d2) cout << "\nДробь 1 < Дробь 2";
        if (d1 >= d2) cout << "\nДробь 1 >= Дробь 2\n\n";
    
    return 0;
}
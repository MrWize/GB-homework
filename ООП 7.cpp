#include <iostream>

using namespace std;

//задание 1

class Date
{
    int day;
    int month;
    int year;
public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int getDay()
    {
        return day;
    }

    int getMonth()
    {
        return month;
    }

    int getYear()
    {
        return year;
    }

    void setDay(int d)
    {
        day = d;
    }

    void setMonth(int m)
    {
        month = m;
    }

    void setYear(int y)
    {
        year = y;
    }


    friend ostream& operator<< (ostream& out, const Date& date);
};

ostream& operator<< (ostream& out, const Date& date)
{
    out << date.day << "." << date.month << "." << date.year;
    return out;
}

//задание 2

Date compare(unique_ptr<Date>& d1, unique_ptr<Date>& d2)
{
    if (d1->getYear() > d2->getYear()) return *d1;
    else if (d1->getYear() < d2->getYear()) return *d2;

    if (d1->getMonth() > d2->getMonth()) return *d1;
    else if (d1->getMonth() < d2->getMonth()) return *d2;

    if (d1->getDay() > d2->getDay()) return *d1;
    else if (d1->getDay() < d2->getDay()) return *d2;

    return *d1;
}

void swapPtr(unique_ptr<Date>& d1, unique_ptr<Date>& d2)
{
    unique_ptr<Date> d3(new Date(0, 0, 0));

    d3->setDay(d1->getDay());
    d3->setMonth(d1->getMonth());
    d3->setYear(d1->getYear());

    d1->setDay(d2->getDay());
    d1->setMonth(d2->getMonth());
    d1->setYear(d2->getYear());

    d2->setDay(d3->getDay());
    d2->setMonth(d3->getMonth());
    d2->setYear(d3->getYear());
}

int main()
{
    //задание 1

    unique_ptr<Date> today(new Date(10, 11, 2021));
    cout << today->getDay() << "." << today->getMonth() << "." << today->getYear() << endl;
    cout << *today << endl;
    unique_ptr<Date> date(move(today));

    if (today == nullptr)
        cout << "today is nullptr\n";
    else
        cout << "today is NOT nullptr\n";

    if (date == nullptr)
        cout << "date is nullptr\n";
    else
        cout << "date is NOT nullptr\n\n";

    //задание 2

    unique_ptr<Date> date1(new Date(17, 5, 2021));
    unique_ptr<Date> date2(new Date(29, 1, 2023));

    cout << *date1 << "    " << *date2 << endl;
    cout << compare(date1, date2) << " is later!\n";

    swapPtr(date1, date2);

    cout << *date1 << "    " << *date2 << endl;

    return 0;
}

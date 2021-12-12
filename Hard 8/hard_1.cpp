#pragma once

#include <iostream>
#include <tuple>
#include <optional>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

class Person
{
private:
	string last_name;
	string first_name;
	optional<string> patronymic;
public:
	Person() : last_name("-"), first_name("-"), patronymic(nullopt) {}

	Person(string l, string f, string p) : last_name(l), first_name(f), patronymic(p) {}

	Person(string l, string f) : last_name(l), first_name(f), patronymic(nullopt) {}

	void SetPerson(istringstream& file)
	{
		string temp;
		file >> last_name >> first_name >> temp;

		if (temp == "-")
			return;
		else
			patronymic = temp;
	}

	string GetFirstName() const { return first_name; }

	string GetPatronimic() const 
	{
		if (patronymic.has_value())
			return patronymic.value();
		else
			return "";
	}

	string GetLastName() const { return last_name; }

	friend ostream& operator << (ostream& out, const Person& person);

	friend bool operator< (const Person& p1, const Person& p2);

	friend bool operator== (const Person& p1, const Person& p2);

};

ostream& operator<< (ostream& out, const Person& person)
{
	out << person.last_name << " " << person.first_name;
	if (person.patronymic.has_value())
		out << " " << person.patronymic.value();
	out << endl;

	return out;
}

bool operator< (const Person& p1, const Person& p2) {
	return tie(p1.last_name, p1.first_name, p1.patronymic) <
		tie(p2.last_name, p2.first_name, p2.patronymic);
}

bool operator== (const Person& p1, const Person& p2) {
	return tie(p1.last_name, p1.first_name, p1.patronymic) ==
		tie(p2.last_name, p2.first_name, p2.patronymic);
}

class PhoneNumber
{
private:
	int country;
	int city;
	string number;
	optional<int> add;
public:
	PhoneNumber() : country(0), city(0), number("0"), add(nullopt) {};

	PhoneNumber(int co, int ci, string num, optional<int> ad) : country(co), city(ci), number{ move(num) }, add(ad) {};

	PhoneNumber(int co, int ci, string num) : country(co), city(ci), number{ move(num) }, add(nullopt) {};

	int getCountry() const { return country; }

	int GetCity() const { return city; }

	string GetNumber() const { return number; }

	int GetAdd() const {
		if (add.has_value())
			return add.value();
		else
			return 0;
	}

	void SetPhoneNumber(istringstream& file)
	{
		char temp;
		file >> country >> city >> number >> temp;

		if (temp == '-')
			return;
		else
			add = static_cast<int>(temp);
	}

	static PhoneNumber ReadFromStream(istringstream& file)
	{
		PhoneNumber phone;
		if (file.peek() == ' ')
			file.ignore(1);

		file >> phone.country >> phone.city >>
			phone.number;

		if (file.peek() != '-') {
			file >> phone.add.emplace();
		}

		return phone;
	};


	friend ostream& operator<< (ostream& out, const PhoneNumber& phone_number);

	friend bool operator< (const PhoneNumber& num1, const PhoneNumber& num2);

};

ostream& operator<< (ostream& out, const PhoneNumber& phone)
{
	out << '+' << phone.getCountry() << "(" << phone.GetCity() << ")" << phone.GetNumber() << ' ';
	if (phone.add.has_value())
		out << phone.add.value();

	out << endl;
	return out;
}

bool operator< (const PhoneNumber& num1, const PhoneNumber& num2)
{
	return tie(num1.country, num1.city, num1.number, num1.add) <
		tie(num2.country, num2.city, num2.number, num2.add);
}

class PhoneBook
{
private:
	string line;
	vector<pair<Person, PhoneNumber>> phonebook;
public:
	PhoneBook(ifstream& file)
	{
		while (!file.eof())
		{
			getline(file, line);

			istringstream str(line);
			Person person;
			PhoneNumber number;

			person.SetPerson(str);
			number.SetPhoneNumber(str);
			phonebook.push_back(make_pair(person, number));
		};
	}

	void SortByName()
	{
		sort(phonebook.begin(), phonebook.end(), [](pair<Person, PhoneNumber> p1,
			pair<Person, PhoneNumber> p2)
			{
				return p1.first < p2.first;
			}
		);
	};

	void SortByPhone()
	{
		sort(phonebook.begin(), phonebook.end(), [](pair<Person, PhoneNumber> n1,
			pair<Person, PhoneNumber> n2)
			{
				return n1.second < n2.second;
			}
		);
	};

	tuple<string, PhoneNumber> GetPhoneNumber(const string& last)
	{
		int count = 0;
		const PhoneNumber* number{};

		auto lambda = [&](auto& str)
		{
			if (str.first.GetLastName() == last)
			{
				count++;
				number = &str.second;
			}
		};

		for_each(phonebook.begin(), phonebook.end(), lambda);

		if (count == 0)
			return { "Нет совпадений\n", {} };

		else if (count > 1)
			return { "Найдено больше одного человека\n", *number };

		return { "", *number };
	};

	void ChangePhoneNumber(const Person& person, PhoneNumber number)
	{
		auto user = find_if(phonebook.begin(), phonebook.end(), [&person](pair<Person, PhoneNumber>& p)
			{
				return p.first == person;
			}
		);

		if (user != phonebook.end())
			user->second = number;
	};

	friend ostream& operator<< (ostream& out, PhoneBook& book);
};

ostream& operator<< (ostream& out, PhoneBook& pb)
{
	for (const auto& n : pb.phonebook)
		out << n.first << ' ' << n.second << endl;
	return out;
};
#include "hard_1.cpp"	//включаем ДЗ1

void test_true(bool expression, const string& test_name)
{
	if (expression)
		cout << "[" << test_name << "] - " << "Test passed!\n";
	else
		cerr << "[" << test_name << "] - " << "Test failed!\n";
}

template <typename T>
void test_equals(T lhs, T rhs, const string& test_name)
{
	if (lhs==rhs)
		cout << "[" << test_name << "] - " << "Test passed!\n";
	else
		cerr << "[" << test_name << "] - " << "Test failed!\n";
}

void test_open(const string& name)
{
	ifstream file(name);
	string test_name = "Opening file: " + name;

	test_true(file.is_open(), test_name);

	if(file.is_open())
		file.close();
}

void test_read_from_file()
{
	string line;
	ifstream file("Phones.txt");
	getline(file, line);
	getline(file, line);		//считываем вторую строку
	file.close();

	istringstream str(line);

	Person person;
	person.SetPerson(str);

	test_equals(person.GetFirstName(), (string)("Andrey"), "Reading first name");
	test_equals(person.GetLastName(), (string)("Ivanov"), "Reading last name");
	test_equals(person.GetPatronimic(), (string)("Ivanovich"), "Reading patronimic");

	cout << endl;

	PhoneNumber number;
	number.SetPhoneNumber(str);

	string lhs = to_string(number.getCountry()) + to_string(number.GetCity()) + number.GetNumber() + to_string(number.GetAdd());
	string rhs = "866698765453";

	test_equals(lhs, rhs, "Reading phone number");
}

void test_change_phone_number()
{
	ifstream file("Phones.txt");
	PhoneBook book(file);
	file.close();

	book.ChangePhoneNumber(Person{ "Andreev", "Ivan", "Ivanovich" }, PhoneNumber{ 9, 999, "999999", 99 });
	PhoneNumber phone = get<1>(book.GetPhoneNumber("Andreev"));

	string lhs = to_string(phone.getCountry()) + to_string(phone.GetCity()) + phone.GetNumber() + to_string(phone.GetAdd());
	string rhs = "999999999999";

	test_equals(lhs, rhs, "Changing phone number");
}

int main()
{
	test_open("Phones.txt");
	test_open("pHonEs.TxT");
	test_open("phones");

	cout << endl;

	test_read_from_file();

	cout << endl;

	test_change_phone_number();

	return 0;
}
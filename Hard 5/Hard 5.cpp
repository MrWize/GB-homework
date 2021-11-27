#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <array>
#include <map>

using namespace std;

//задание 1

template<class T>
void uniqueWords(T& begin, T& end)
{
    sort(begin, end);
    int sum = 0;
    cout << "Повторяющиеся слова:\n\n";

    for (auto it = begin; it < end; ++it)
    {
        int n = count(begin, end, *it);
        if (n == 1)
            ++sum;
        else if (n > 1)
        {
            cout << *it << endl;
                it += n-1;
        }
    };
    cout << "\nНайдено " << sum << " уникальных слов.\n\n";
}

int main()
{
    setlocale(0, "");
    
    //задание 1

    string s1 = "The subdued smile which, though it did not suit her faded features, always played round her lips expressed, as in a spoiled child, a continual consciousness of her charming defect, which she neither wished, nor could, nor considered it necessary, to correct.";
    istringstream iss(s1);
    vector<string> str;

    do
    {
        string word;
        iss >> word;
        str.push_back(word);    //делаем вектор из слов
    } while (iss);

    vector<string>::iterator begin1 = str.begin();
    vector<string>::iterator end1 = str.end();
    uniqueWords(begin1,end1);

    array<char,10> s2 = { 'C','Q','U','T','P','Q','Q','M','Q','C'};
    array<char, 10>::iterator begin2 = s2.begin();
    array<char, 10>::iterator end2 = s2.end();
    uniqueWords(begin2, end2);

    //задание 2

    cout << endl << "Введите текст, разделяя предложения точками: \n";

    string phrase;
    getline(cin, phrase);

    multimap <int,string> text;

    string sentence = "";

    for (string::iterator strit = phrase.begin(); strit != phrase.end(); ++strit)
    {
        
        if (*strit == '.')    //обнаружение конца фразы
        {
            text.insert({ sentence.size(),sentence });
            sentence = "";
        }
        else
            sentence += *strit;

        if (strit + 1 == phrase.end())
        {
            text.insert({ sentence.size(),sentence });
            break;
        }
    };

    cout << endl << "Отсортировано по длине: \n";
    for_each(text.begin(), text.end(), [](pair<int,string> s) {cout << s.second << endl; });
}


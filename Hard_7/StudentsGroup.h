#pragma once

#include <cstdlib>
#include <tuple>
#include <fstream>
#include <string>
#include <vector>
#include "class.pb.h"

using namespace std;

class IRepository {
    virtual void Open(string filename) = 0;     // бинарная десериализация в файл
    virtual void Save() = 0;                    // бинарная сериализация в файл
};

class IMethods {
    virtual double GetAverageScore(const n_first::n_second::FullName& name) = 0;
    virtual string GetAllInfo(const n_first::n_second::FullName& name) = 0;
    virtual string GetAllInfo() = 0;
};

class StudentsGroup : public IRepository, public IMethods {
public:
    void Open(string filename) override
    {
        ifstream in(filename, ios_base::binary);
        size_t size = 0;

        while (size--) {
            n_first::n_second::Student student;
            student.ParseFromIstream(&in);
            _students.push_back(move(student));
        }
        in.close();
    };

    void Save() override
    {
        ofstream out("students.bin", ios_base::binary);

        for (auto& student : _students) {
            student.SerializePartialToOstream(&out);
        }
        out.close();
    };

    void Push(n_first::n_second::Student&& student)
    {
        _students.push_back(student);
    };

    double GetAverageScore(const n_first::n_second::FullName& rhs) override
    {
        auto student = [&](const n_first::n_second::Student& lhs) {
            return tie(lhs.full_name().name(), lhs.full_name().surname(), lhs.full_name().patronimic()) ==
                tie(rhs.name(), rhs.surname(), rhs.patronimic());
        };
        auto iter{ find_if(_students.begin(), _students.end(), student) };
        return iter->gpa();
    };

    string GetAllInfo(const n_first::n_second::FullName& rhs) override
    {
        string information;
        auto student = [&](const n_first::n_second::Student& lhs) {
            return tie(lhs.full_name().name(), lhs.full_name().surname(), lhs.full_name().patronimic()) ==
                tie(rhs.name(), rhs.surname(), rhs.patronimic());
        };

        auto iter = find_if(_students.begin(), _students.end(), student);
        information.append(iter->full_name().name());
        information.push_back(' ');
        information.append((iter->full_name().has_patronimic() ? iter->full_name().patronimic() : ""));
        information.push_back(' ');
        information.append(iter->full_name().surname());
        information.push_back('\t');

        for (const auto& g : iter->grades()) {
            information.append(to_string(g));
            information.push_back(' ');
        }

        information.push_back('\t');
        information.append(to_string(iter->gpa()));

        return information;
    };

    string GetAllInfo() override
    {
        string information;
        auto iter{ _students.begin() };

        while (iter != _students.end()) {
            information.append(GetAllInfo(iter->full_name()));
            information.push_back('\n');
            iter++;
        };

        return information;
    };

    vector<n_first::n_second::Student> GetStudents() const { return _students; }

private:
    vector<n_first::n_second::Student> _students;
};
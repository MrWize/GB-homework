#include <iostream>
#include <numeric>
#include "StudentsGroup.h"

void PrintGroup(n_first::n_second::StudentsGroup group) {
    for (size_t i = 0; i < group.student_size(); ++i) {
        cout << group.student(i).full_name().name() << ' ' << (group.student(i).full_name().has_patronimic() ?
            group.student(i).full_name().patronimic() : "") << ' ' << group.student(i).full_name().surname() <<
            ". The student's gpa is: " << group.student(i).gpa() << endl;
    }
}

void PrintGroup(StudentsGroup group) {
    for (const auto& student : group.GetStudents()) {
        cout << student.full_name().name() << ' ' << (student.full_name().has_patronimic() ?
            student.full_name().patronimic() : "") << ' ' << student.full_name().surname() <<
            ". The student's gpa is: " << student.gpa() << endl;
    }
}

void Task2() {
    n_first::n_second::FullName studname1;
    studname1.set_name("Andrey");
    studname1.set_surname("Nikolaev");
    studname1.set_patronimic("Vasilyevich");

    n_first::n_second::Student student;
    *student.mutable_full_name() = studname1;
    student.add_grades(3);
    student.add_grades(4);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    double avg = accumulate(student.grades().begin(), student.grades().end(), 0.0) / student.grades().size();
    student.set_gpa(avg);

    n_first::n_second::FullName studname2;
    studname2.set_name("Anna");
    studname2.set_surname("Williams");

    n_first::n_second::Student student1;
    *student1.mutable_full_name() = studname2;
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(5);
    avg = accumulate(student1.grades().begin(), student1.grades().end(), 0.0) / student1.grades().size();
    student1.set_gpa(avg);

    n_first::n_second::StudentsGroup group1;
    *group1.add_student() = student;
    *group1.add_student() = student1;

    ofstream out("students.bin", ios_base::binary);
    group1.SerializeToOstream(&out);
    out.close();
    ifstream in("students.bin", ios_base::binary);
    n_first::n_second::StudentsGroup group2;
    group2.ParseFromIstream(&in);
    in.close();
    PrintGroup(group2);
}

void Task3() {
    n_first::n_second::FullName studname1;
    studname1.set_name("Andrey");
    studname1.set_surname("Nikolaev");
    studname1.set_patronimic("Vasilyevich");

    n_first::n_second::Student student;
    *student.mutable_full_name() = studname1;
    student.add_grades(3);
    student.add_grades(4);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    double avg = accumulate(student.grades().begin(), student.grades().end(), 0.0) / student.grades().size();
    student.set_gpa(avg);

    n_first::n_second::FullName studname2;
    studname2.set_name("Anna");
    studname2.set_surname("Williams");

    n_first::n_second::Student student1;
    *student1.mutable_full_name() = studname2;
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(5);
    avg = accumulate(student1.grades().begin(), student1.grades().end(), 0.0) / student1.grades().size();
    student1.set_gpa(avg);

    StudentsGroup studentg;
    studentg.Push(move(student));
    studentg.Push(move(student1));
    studentg.Save();

    double gpa{ studentg.GetAverageScore(studname1) };
    string a_student{ studentg.GetAllInfo(studname1) };
    string b_student{ studentg.GetAllInfo(studname2) };
    string students{ studentg.GetAllInfo() };

    cout << "The students' gpa is " << gpa << endl;
    double gpa2{ studentg.GetAverageScore(studname2) };
    cout << "The students' gpa is " << gpa2 << endl;
    cout << a_student << endl;
    cout << endl;
    cout << b_student << endl;
    cout << endl;
    cout << students << endl;
    cout << endl;
    cout << endl;
    studentg.Open("students.bin");
    string students2{ studentg.GetAllInfo() };
    cout << students2 << endl;
    PrintGroup(studentg);
}

int main() {
    Task2();
    cout << endl;
    Task3();
    return 0;
}
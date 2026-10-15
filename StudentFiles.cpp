#include "StudentFiles.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

bool readFromFile(const string& fileName, vector<Person>& students) {
    ifstream file(fileName);
    if (!file) {
        cout << "Could not open file: " << fileName << "\n";
        return false;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        string name, surname;
        ss >> name >> surname;

        vector<double> values;
        double x;
        while (ss >> x) values.push_back(x);
        if (values.empty()) continue;

        double exam = values.back();   // last number is the exam
        values.pop_back();             // the rest are homework
        students.push_back(Person(name, surname, values, exam));
    }
    return true;
}

void printTable(vector<Person>& students) {
    // Sort by name, then by surname
    sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
        if (a.getName() == b.getName()) return a.getSurname() < b.getSurname();
        return a.getName() < b.getName();
    });

    cout << "\n" << left << setw(15) << "Name"
         << setw(15) << "Surname"
         << right << setw(14) << "Final (Avg.)" << " |"
         << setw(13) << "Final (Med.)" << "\n";
    cout << string(58, '-') << "\n";

    for (const Person& s : students) cout << s << "\n";
}

#include "StudentFiles.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

void readFromFile(const string& fileName, vector<Person>& students) {
    ifstream file(fileName);
    if (!file) throw runtime_error("Could not open file: " + fileName);

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        if (line.empty() || line == "\r") continue;
        students.push_back(Person::fromLine(line));
    }
}

void sortByName(vector<Person>& students) {
    sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
        if (a.getName() == b.getName()) return a.getSurname() < b.getSurname();
        return a.getName() < b.getName();
    });
}

void printTable(vector<Person>& students) {
    sortByName(students);

    cout << "\n" << left << setw(15) << "Name"
         << setw(15) << "Surname"
         << right << setw(14) << "Final (Avg.)" << " |"
         << setw(13) << "Final (Med.)" << "\n";
    cout << string(58, '-') << "\n";

    for (const Person& s : students) cout << s << "\n";
}

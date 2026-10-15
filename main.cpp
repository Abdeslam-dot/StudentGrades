#include <iostream>
#include <string>
#include <vector>

#include "Person.h"
#include "StudentFiles.h"

using namespace std;

int main() {
    vector<Person> students;

    int mode;
    cout << "1 - Enter data manually\n";
    cout << "2 - Generate random scores\n";
    cout << "3 - Read data from file\n";
    cout << "Choose: ";
    cin >> mode;

    if (mode == 3) {
        string fileName;
        cout << "File name (e.g. Students.txt): ";
        cin >> fileName;
        if (!readFromFile(fileName, students)) return 1;
    } else {
        int n;
        cout << "How many students? ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            Person p;
            cout << "\n--- Student " << i + 1 << " ---\n";
            if (mode == 2) {
                string name, surname;
                int hwCount;
                cout << "First name: ";
                cin >> name;
                cout << "Surname: ";
                cin >> surname;
                cout << "Number of homework results to generate: ";
                cin >> hwCount;
                p.setName(name, surname);
                p.generateRandom(hwCount);
            } else {
                cin >> p;
            }
            students.push_back(p);
        }
    }

    printTable(students);
    return 0;
}

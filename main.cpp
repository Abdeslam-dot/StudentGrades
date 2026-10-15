#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Person.h"
#include "StudentFiles.h"

using namespace std;

const vector<int> TEST_SIZES = {1000, 10000, 100000, 1000000, 10000000};

int main() {
    try {
        vector<Person> students;

        int mode;
        cout << "1 - Enter data manually\n";
        cout << "2 - Generate random scores\n";
        cout << "3 - Read data from file\n";
        cout << "4 - Generate test files (1 000 ... 10 000 000 students)\n";
        cout << "Choose: ";
        if (!(cin >> mode) || mode < 1 || mode > 4) throw invalid_argument("Choose a number from 1 to 4");

        if (mode == 4) {
            for (int n : TEST_SIZES) {
                string name = "students" + to_string(n) + ".txt";
                generateFile(name, n);
                cout << "Generated " << name << "\n";
            }
            return 0;
        }

        if (mode == 3) {
            string fileName;
            cout << "File name (e.g. Students.txt): ";
            cin >> fileName;
            readFromFile(fileName, students);
        } else {
            int n;
            cout << "How many students? ";
            if (!(cin >> n) || n <= 0) throw invalid_argument("Number of students must be positive");

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
                    if (!(cin >> hwCount)) throw invalid_argument("Homework count must be a number");
                    p.setName(name, surname);
                    p.generateRandom(hwCount);
                } else {
                    cin >> p;
                }
                students.push_back(p);
            }
        }

        printTable(students);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

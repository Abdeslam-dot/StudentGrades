#include <deque>
#include <exception>
#include <iomanip>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

#include "Person.h"
#include "StudentFiles.h"
#include "Timer.h"

using namespace std;

const vector<int> TEST_SIZES = {1000, 10000, 100000, 1000000, 10000000};

// Read -> sort -> split -> write two new files, measuring every step,
// for one container type (vector, list or deque)
template <typename Container>
void speedTest(const string& fileName, const string& containerName) {
    cout << "\n=== " << fileName << " [" << containerName << "] ===\n" << fixed << setprecision(4);
    Timer total, t;

    Container students;
    readFromFile(fileName, students);
    cout << "Reading " << students.size() << " records: " << t.elapsed() << " s\n";

    t.reset();
    sortStudents(students, byFinal);
    cout << "Sorting:                 " << t.elapsed() << " s\n";

    t.reset();
    Container failed, passed;
    splitStudents(students, failed, passed);
    cout << "Splitting in two:        " << t.elapsed() << " s"
         << "  (failed: " << failed.size() << ", passed: " << passed.size() << ")\n";

    t.reset();
    string base = fileName.substr(0, fileName.rfind('.')) + "_" + containerName;
    writeToFile(base + "_failed.txt", failed);
    writeToFile(base + "_passed.txt", passed);
    cout << "Writing two files:       " << t.elapsed() << " s\n";

    cout << "Total time:              " << total.elapsed() << " s\n";
}

int main() {
    try {
        vector<Person> students;

        int mode;
        cout << "1 - Enter data manually\n";
        cout << "2 - Generate random scores\n";
        cout << "3 - Read data from file\n";
        cout << "4 - Generate test files (1 000 ... 10 000 000 students)\n";
        cout << "5 - Speed analysis (read, sort, split, write) on test files\n";
        cout << "Choose: ";
        if (!(cin >> mode) || mode < 1 || mode > 5) throw invalid_argument("Choose a number from 1 to 5");

        if (mode == 4) {
            for (int n : TEST_SIZES) {
                string name = "students" + to_string(n) + ".txt";
                Timer t;
                generateFile(name, n);
                cout << "Generated " << name << " in " << fixed << setprecision(4) << t.elapsed() << " s\n";
            }
            return 0;
        }

        if (mode == 5) {
            int c;
            cout << "Container: 1 - vector, 2 - list, 3 - deque, 4 - all three\nChoose: ";
            if (!(cin >> c) || c < 1 || c > 4) throw invalid_argument("Choose a number from 1 to 4");

            for (int n : TEST_SIZES) {
                string fileName = "students" + to_string(n) + ".txt";
                try {
                    if (c == 1 || c == 4) speedTest<vector<Person>>(fileName, "vector");
                    if (c == 2 || c == 4) speedTest<list<Person>>(fileName, "list");
                    if (c == 3 || c == 4) speedTest<deque<Person>>(fileName, "deque");
                } catch (const runtime_error& e) {   // e.g. file does not exist
                    cout << "Error: " << e.what() << " (generate it with option 4)\n";
                }
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

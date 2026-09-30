#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Person {
private:
    string name;
    string surname;
    vector<double> hw;   // homework results
    double exam;
    double finalAvg;
    double finalMed;

public:
    // Default constructor
    Person() : name(""), surname(""), exam(0), finalAvg(0), finalMed(0) {}

    // Constructor with values
    Person(const string& n, const string& s, const vector<double>& h, double e)
        : name(n), surname(s), hw(h), exam(e), finalAvg(0), finalMed(0) {
        calculateFinal();
    }

    // Copy constructor
    Person(const Person& other)
        : name(other.name), surname(other.surname), hw(other.hw),
          exam(other.exam), finalAvg(other.finalAvg), finalMed(other.finalMed) {}

    // Copy assignment operator
    Person& operator=(const Person& other) {
        if (this == &other) return *this;
        name = other.name;
        surname = other.surname;
        hw = other.hw;
        exam = other.exam;
        finalAvg = other.finalAvg;
        finalMed = other.finalMed;
        return *this;
    }

    // Destructor
    ~Person() {
        hw.clear();
    }

    string getName() const { return name; }
    string getSurname() const { return surname; }
    double getFinalAvg() const { return finalAvg; }
    double getFinalMed() const { return finalMed; }

    double average() const {
        if (hw.empty()) return 0;
        double sum = 0;
        for (double x : hw) sum += x;
        return sum / hw.size();
    }

    double median() const {
        if (hw.empty()) return 0;
        vector<double> tmp = hw;
        sort(tmp.begin(), tmp.end());
        size_t n = tmp.size();
        if (n % 2 == 0) return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
        return tmp[n / 2];
    }

    // Calculates both final grades (by average and by median)
    void calculateFinal() {
        finalAvg = 0.4 * average() + 0.6 * exam;
        finalMed = 0.4 * median() + 0.6 * exam;
    }

    // Fill homework and exam with random scores (1-10)
    void generateRandom(int hwCount) {
        static mt19937 gen(random_device{}());
        uniform_int_distribution<int> dist(1, 10);
        hw.clear();
        for (int i = 0; i < hwCount; i++) hw.push_back(dist(gen));
        exam = dist(gen);
        calculateFinal();
    }

    void setName(const string& n, const string& s) {
        name = n;
        surname = s;
    }

    // Input: homework results until the user types -1
    friend istream& operator>>(istream& in, Person& p) {
        cout << "First name: ";
        in >> p.name;
        cout << "Surname: ";
        in >> p.surname;

        p.hw.clear();
        cout << "Enter homework results (type -1 when finished):\n";
        double x;
        while (true) {
            cout << "Homework " << p.hw.size() + 1 << ": ";
            in >> x;
            if (x == -1) break;
            if (x < 0 || x > 10) {
                cout << "Result must be between 0 and 10.\n";
                continue;
            }
            p.hw.push_back(x);
        }

        cout << "Exam result: ";
        in >> p.exam;
        p.calculateFinal();
        return in;
    }

    // Output: name, surname, final (avg) | final (med)
    friend ostream& operator<<(ostream& out, const Person& p) {
        out << left << setw(15) << p.name
            << setw(15) << p.surname
            << right << fixed << setprecision(2)
            << setw(14) << p.finalAvg << " |"
            << setw(13) << p.finalMed;
        return out;
    }
};

// Reads students from a file. First line is the header.
// Each line: Name Surname HW1 HW2 ... HWn Exam
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
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Person {
private:
    string name;
    string surname;
    int hwCount;
    double* hw;      // homework results (dynamic array)
    double exam;
    double finalGrade;

public:
    // Default constructor
    Person() : name(""), surname(""), hwCount(0), hw(nullptr), exam(0), finalGrade(0) {}

    // Copy constructor
    Person(const Person& other)
        : name(other.name), surname(other.surname), hwCount(other.hwCount),
          hw(nullptr), exam(other.exam), finalGrade(other.finalGrade) {
        if (hwCount > 0) {
            hw = new double[hwCount];
            for (int i = 0; i < hwCount; i++) hw[i] = other.hw[i];
        }
    }

    // Copy assignment operator
    Person& operator=(const Person& other) {
        if (this == &other) return *this;
        delete[] hw;
        name = other.name;
        surname = other.surname;
        hwCount = other.hwCount;
        exam = other.exam;
        finalGrade = other.finalGrade;
        hw = nullptr;
        if (hwCount > 0) {
            hw = new double[hwCount];
            for (int i = 0; i < hwCount; i++) hw[i] = other.hw[i];
        }
        return *this;
    }

    // Destructor
    ~Person() {
        delete[] hw;
    }

    // Final grade using the homework average
    void calculateFinal() {
        double sum = 0;
        for (int i = 0; i < hwCount; i++) sum += hw[i];
        double avg = (hwCount > 0) ? sum / hwCount : 0;
        finalGrade = 0.4 * avg + 0.6 * exam;
    }

    // Input
    friend istream& operator>>(istream& in, Person& p) {
        cout << "First name: ";
        in >> p.name;
        cout << "Surname: ";
        in >> p.surname;
        cout << "Number of homework results: ";
        in >> p.hwCount;

        delete[] p.hw;
        p.hw = (p.hwCount > 0) ? new double[p.hwCount] : nullptr;
        for (int i = 0; i < p.hwCount; i++) {
            cout << "Homework " << i + 1 << ": ";
            in >> p.hw[i];
        }
        cout << "Exam result: ";
        in >> p.exam;

        p.calculateFinal();
        return in;
    }

    // Output
    friend ostream& operator<<(ostream& out, const Person& p) {
        out << left << setw(12) << p.name
            << setw(15) << p.surname
            << right << setw(18) << fixed << setprecision(2) << p.finalGrade;
        return out;
    }
};

int main() {
    int n;
    cout << "How many students? ";
    cin >> n;

    Person* students = new Person[n];
    for (int i = 0; i < n; i++) {
        cout << "\n--- Student " << i + 1 << " ---\n";
        cin >> students[i];
    }

    cout << "\n" << left << setw(12) << "Name"
         << setw(15) << "Surname"
         << right << setw(18) << "Final_Point(Aver.)" << "\n";
    cout << string(45, '-') << "\n";

    for (int i = 0; i < n; i++) {
        cout << students[i] << "\n";
    }

    delete[] students;
    return 0;
}
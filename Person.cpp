#include "Person.h"

#include <algorithm>
#include <iomanip>
#include <random>
#include <sstream>
#include <stdexcept>

using namespace std;

// Default constructor
Person::Person() : name(""), surname(""), exam(0), finalAvg(0), finalMed(0) {}

// Constructor with values
Person::Person(const string& n, const string& s, const vector<double>& h, double e)
    : name(n), surname(s), hw(h), exam(e), finalAvg(0), finalMed(0) {
    calculateFinal();
}

// Copy constructor
Person::Person(const Person& other)
    : name(other.name), surname(other.surname), hw(other.hw),
      exam(other.exam), finalAvg(other.finalAvg), finalMed(other.finalMed) {}

// Copy assignment operator
Person& Person::operator=(const Person& other) {
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
Person::~Person() {
    hw.clear();
}

double Person::average() const {
    if (hw.empty()) throw domain_error("No homework results for " + name + " " + surname);
    double sum = 0;
    for (double x : hw) sum += x;
    return sum / hw.size();
}

double Person::median() const {
    if (hw.empty()) throw domain_error("No homework results for " + name + " " + surname);
    vector<double> tmp = hw;
    sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    if (n % 2 == 0) return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
    return tmp[n / 2];
}

void Person::calculateFinal() {
    finalAvg = 0.4 * average() + 0.6 * exam;
    finalMed = 0.4 * median() + 0.6 * exam;
}

void Person::generateRandom(int hwCount) {
    if (hwCount <= 0) throw invalid_argument("Number of homework results must be positive");
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 10);
    hw.clear();
    for (int i = 0; i < hwCount; i++) hw.push_back(dist(gen));
    exam = dist(gen);
    calculateFinal();
}

void Person::setName(const string& n, const string& s) {
    name = n;
    surname = s;
}

Person Person::fromLine(const string& line) {
    istringstream ss(line);
    string name, surname;
    if (!(ss >> name >> surname))
        throw invalid_argument("Bad line (missing name/surname): " + line);

    vector<double> values;
    double x;
    while (ss >> x) {
        if (x < 0 || x > 10) throw out_of_range("Grade not in 0-10 range: " + line);
        values.push_back(x);
    }
    if (values.size() < 2)
        throw invalid_argument("Bad line (need homework and exam): " + line);

    double exam = values.back();   // last number is the exam
    values.pop_back();             // the rest are homework
    return Person(name, surname, values, exam);
}

istream& operator>>(istream& in, Person& p) {
    cout << "First name: ";
    in >> p.name;
    cout << "Surname: ";
    in >> p.surname;

    p.hw.clear();
    cout << "Enter homework results (type -1 when finished):\n";
    double x;
    while (true) {
        cout << "Homework " << p.hw.size() + 1 << ": ";
        if (!(in >> x)) throw invalid_argument("Homework result must be a number");
        if (x == -1) break;
        if (x < 0 || x > 10) {
            cout << "Result must be between 0 and 10.\n";
            continue;
        }
        p.hw.push_back(x);
    }

    cout << "Exam result: ";
    if (!(in >> p.exam)) throw invalid_argument("Exam result must be a number");
    if (p.exam < 0 || p.exam > 10) throw out_of_range("Exam result must be between 0 and 10");
    p.calculateFinal();   // throws if no homework was entered
    return in;
}

ostream& operator<<(ostream& out, const Person& p) {
    out << left << setw(15) << p.name
        << setw(15) << p.surname
        << right << fixed << setprecision(2)
        << setw(14) << p.finalAvg << " |"
        << setw(13) << p.finalMed;
    return out;
}

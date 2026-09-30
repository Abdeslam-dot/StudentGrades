#include <iostream>
#include <iomanip>
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
    double finalGrade;

public:
    // Default constructor
    Person() : name(""), surname(""), exam(0), finalGrade(0) {}

    // Copy constructor
    Person(const Person& other)
        : name(other.name), surname(other.surname), hw(other.hw),
          exam(other.exam), finalGrade(other.finalGrade) {}

    // Copy assignment operator
    Person& operator=(const Person& other) {
        if (this == &other) return *this;
        name = other.name;
        surname = other.surname;
        hw = other.hw;
        exam = other.exam;
        finalGrade = other.finalGrade;
        return *this;
    }

    // Destructor
    ~Person() {
        hw.clear();
    }

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

    // useMedian = true -> median, false -> average
    void calculateFinal(bool useMedian) {
        double hwPart = useMedian ? median() : average();
        finalGrade = 0.4 * hwPart + 0.6 * exam;
    }

    // Fill homework and exam with random scores (1-10)
    void generateRandom(int hwCount) {
        static mt19937 gen(random_device{}());
        uniform_int_distribution<int> dist(1, 10);
        hw.clear();
        for (int i = 0; i < hwCount; i++) hw.push_back(dist(gen));
        exam = dist(gen);
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
    vector<Person> students;

    int mode;
    cout << "1 - Enter data manually\n";
    cout << "2 - Generate random scores\n";
    cout << "Choose: ";
    cin >> mode;

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

    char choice;
    cout << "\nCalculate final grade by (A)verage or (M)edian? ";
    cin >> choice;
    bool useMedian = (choice == 'M' || choice == 'm');

    for (Person& s : students) s.calculateFinal(useMedian);

    string title = useMedian ? "Final_Point(Med.)" : "Final_Point(Aver.)";
    cout << "\n" << left << setw(12) << "Name"
         << setw(15) << "Surname"
         << right << setw(18) << title << "\n";
    cout << string(45, '-') << "\n";

    for (const Person& s : students) cout << s << "\n";

    return 0;
}
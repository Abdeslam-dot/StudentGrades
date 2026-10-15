#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

// Student data: name, surname, homework results, exam result and final grades.
// Follows the rule of three (copy constructor, copy assignment, destructor).
class Person {
private:
    std::string name;
    std::string surname;
    std::vector<double> hw;   // homework results
    double exam;
    double finalAvg;
    double finalMed;

public:
    Person();
    Person(const std::string& n, const std::string& s, const std::vector<double>& h, double e);
    Person(const Person& other);              // copy constructor
    Person& operator=(const Person& other);   // copy assignment operator
    ~Person();                                // destructor

    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    double getFinalAvg() const { return finalAvg; }
    double getFinalMed() const { return finalMed; }

    double average() const;
    double median() const;

    // Calculates both final grades (by average and by median)
    void calculateFinal();

    // Fill homework and exam with random scores (1-10)
    void generateRandom(int hwCount);

    void setName(const std::string& n, const std::string& s);

    // Input: homework results until the user types -1
    friend std::istream& operator>>(std::istream& in, Person& p);
    // Output: name, surname, final (avg) | final (med)
    friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

#endif

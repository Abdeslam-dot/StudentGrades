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

    // Throw std::domain_error if there are no homework results
    double average() const;
    double median() const;

    // Calculates both final grades (by average and by median)
    void calculateFinal();

    // Fill homework and exam with random scores (1-10)
    void generateRandom(int hwCount);

    void setName(const std::string& n, const std::string& s);

    // Builds a Person from one file line: Name Surname HW1 ... HWn Exam
    // Throws std::invalid_argument / std::out_of_range on bad data
    static Person fromLine(const std::string& line);

    // Input: homework results until the user types -1
    friend std::istream& operator>>(std::istream& in, Person& p);
    // Output: name, surname, final (avg) | final (med)
    friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

#endif

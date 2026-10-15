#ifndef STUDENTFILES_H
#define STUDENTFILES_H

// v0.25: the same functions as v0.2, written as templates so the same code
// works with std::vector, std::list and std::deque.

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "Person.h"

const int GEN_HW_COUNT = 10;     // homework results per generated student
const double PASS_MARK = 5.0;    // final points >= 5.0 -> passed

// Generates a file with `count` random students (Name1 Surname1, Name2 Surname2, ...)
void generateFile(const std::string& fileName, int count);

// Reads students from a file into any container. Throws std::runtime_error if the file does not exist
template <typename Container>
void readFromFile(const std::string& fileName, Container& students) {
    std::ifstream file(fileName);
    if (!file) throw std::runtime_error("Could not open file: " + fileName);

    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        if (line.empty() || line == "\r") continue;
        students.push_back(Person::fromLine(line));
    }
}

inline bool byFinal(const Person& a, const Person& b) { return a.getFinalAvg() > b.getFinalAvg(); }

inline bool byName(const Person& a, const Person& b) {
    if (a.getName() == b.getName()) return a.getSurname() < b.getSurname();
    return a.getName() < b.getName();
}

// std::list has no random-access iterators, so it must use its own list::sort()
template <typename Container, typename Compare>
void sortStudents(Container& students, Compare cmp) {
    if constexpr (std::is_same_v<Container, std::list<Person>>)
        students.sort(cmp);
    else
        std::sort(students.begin(), students.end(), cmp);
}

// Divide students into "failed" (< 5.0) and "passed" (>= 5.0)
template <typename Container>
void splitStudents(const Container& students, Container& failed, Container& passed) {
    for (const Person& s : students) {
        if (s.getFinalAvg() < PASS_MARK) failed.push_back(s);
        else passed.push_back(s);
    }
}

template <typename Container>
void writeToFile(const std::string& fileName, const Container& students) {
    std::ofstream file(fileName);
    if (!file) throw std::runtime_error("Could not create file: " + fileName);

    std::ostringstream buf;
    buf << std::left << std::setw(15) << "Name" << std::setw(15) << "Surname"
        << std::right << std::setw(14) << "Final (Avg.)" << " |" << std::setw(13) << "Final (Med.)" << "\n"
        << std::string(58, '-') << "\n";
    int i = 0;
    for (const Person& s : students) {
        buf << s << "\n";
        if (++i % 100000 == 0) { file << buf.str(); buf.str(""); }
    }
    file << buf.str();
}

template <typename Container>
void printTable(Container& students) {
    sortStudents(students, byName);
    std::cout << "\n" << std::left << std::setw(15) << "Name" << std::setw(15) << "Surname"
              << std::right << std::setw(14) << "Final (Avg.)" << " |" << std::setw(13) << "Final (Med.)" << "\n"
              << std::string(58, '-') << "\n";
    for (const Person& s : students) std::cout << s << "\n";
}

#endif

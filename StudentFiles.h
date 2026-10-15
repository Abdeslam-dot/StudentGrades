#ifndef STUDENTFILES_H
#define STUDENTFILES_H

#include <string>
#include <vector>

#include "Person.h"

const int GEN_HW_COUNT = 10;     // homework results per generated student
const double PASS_MARK = 5.0;    // final points >= 5.0 -> passed

// Generates a file with `count` random students (Name1 Surname1, Name2 Surname2, ...)
// Throws std::runtime_error if the file cannot be created
void generateFile(const std::string& fileName, int count);

// Reads students from a file. First line is the header.
// Throws std::runtime_error if the file does not exist
void readFromFile(const std::string& fileName, std::vector<Person>& students);

// Sort by final points (highest first)
void sortByFinal(std::vector<Person>& students);

// Sort by name, then by surname (used for the screen table)
void sortByName(std::vector<Person>& students);

// Divide students into "failed" (< 5.0) and "passed" (>= 5.0)
void splitStudents(const std::vector<Person>& students,
                   std::vector<Person>& failed, std::vector<Person>& passed);

// Writes students to a new file. Throws std::runtime_error on failure
void writeToFile(const std::string& fileName, const std::vector<Person>& students);

void printTable(std::vector<Person>& students);

#endif

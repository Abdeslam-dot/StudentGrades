#ifndef STUDENTFILES_H
#define STUDENTFILES_H

#include <string>
#include <vector>

#include "Person.h"

// Reads students from a file. First line is the header.
// Each line: Name Surname HW1 HW2 ... HWn Exam
bool readFromFile(const std::string& fileName, std::vector<Person>& students);

// Sorts by name, then by surname, and prints the table
void printTable(std::vector<Person>& students);

#endif

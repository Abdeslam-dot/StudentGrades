#ifndef STUDENTFILES_H
#define STUDENTFILES_H

#include <string>
#include <vector>

#include "Person.h"


// Reads students from a file. First line is the header.
// Throws std::runtime_error if the file does not exist
void readFromFile(const std::string& fileName, std::vector<Person>& students);

// Sort by name, then by surname (used for the screen table)
void sortByName(std::vector<Person>& students);

void printTable(std::vector<Person>& students);

#endif

#include "StudentFiles.h"

using namespace std;

void generateFile(const string& fileName, int count) {
    ofstream file(fileName);
    if (!file) throw runtime_error("Could not create file: " + fileName);

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 10);

    // Build text in a buffer and write in big chunks (much faster)
    ostringstream buf;
    buf << left << setw(20) << "Name" << setw(20) << "Surname";
    for (int i = 1; i <= GEN_HW_COUNT; i++) buf << setw(6) << ("HW" + to_string(i));
    buf << "Exam\n";

    for (int i = 1; i <= count; i++) {
        buf << setw(20) << ("Name" + to_string(i)) << setw(20) << ("Surname" + to_string(i));
        for (int h = 0; h < GEN_HW_COUNT; h++) buf << setw(6) << dist(gen);
        buf << dist(gen) << "\n";
        if (i % 100000 == 0) { file << buf.str(); buf.str(""); }
    }
    file << buf.str();
}

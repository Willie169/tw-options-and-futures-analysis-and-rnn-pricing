#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "date.hpp"
using namespace std;

int main() {
    ifstream inputFile("downloads/forward/EG55D01_utf8.csv");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    ofstream outputFile("downloads/forward/forward_exchange_rate_utf8_fer1.csv");
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open output file.\n";
        return 2;
    }

    vector<string> sl;
    string modifiedStr, line, subline;
    ostringstream oss;
    int temp;
    bool c = true;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        while (getline(iss, subline, ',')) {
            sl.push_back(subline);
        }

        if (c == true) {
            c = false;
            for (string& s : sl) {
            s.erase(remove(s.begin(), s.end(), '\"'), s.end());
            }
            sl.erase(sl.end() - 4, sl.end() - 2);
        } else {
            temp = stoi(sl[0].substr(1, 4));
            if (temp < 2015 || temp > 2022) {
                sl.clear();
                continue;
            } else {
                for (string& s : sl) {
                    s.erase(remove(s.begin(), s.end(), '\"'), s.end());
                }
                sl[0] = to_string(date5(sl[0]));
                sl.erase(sl.end() - 4, sl.end() - 2);
            }
        }

        for (size_t i = 0; i < sl.size() - 1; ++i) {
            oss << sl[i];
            oss << ",";
        }
        oss << sl[sl.size() - 1];
        oss << "\n";

        sl.clear();
    }

    inputFile.close();

    outputFile << oss.str();
    outputFile.close();

    return 0;
}

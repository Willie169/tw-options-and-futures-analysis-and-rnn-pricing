#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "date.hpp"

using namespace std;

int pfut1_15t16() {
    string in1 = "201";
    string in2 = "_fut_utf8";
    int y = 5;
    string sy;
    string line;
    while (true) {
        ostringstream oss;
        sy = to_string(y);
        ifstream inputFile("downloads/future/" + in1 + sy + in2 + ".csv");
        if (!inputFile.is_open()) {
            cerr << "Unable to open file for reading.\n";
            break;
        }

        ofstream outFile("downloads/future/" + in1 + sy + in2 + "_pfut1.csv");
        if (!outFile.is_open()) {
            cerr << "Unable to open file for writing.\n";
            break;
        }

        bool c = true;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            vector<string> sl;
            while (getline(iss, line, ',')) {
                sl.push_back(line);
            }

            if ((sl[1] == "TX") && (sl[2].size() != 13)) {
                sl.erase(sl.begin() + 4, sl.begin() + 6);
                sl.erase(sl.begin() + 5, sl.begin() + 7);
                sl.erase(sl.begin() + 6);
                sl.erase(sl.begin() + 7, sl.begin() + 11);
                sl[2].erase(remove(sl[2].begin(), sl[2].end(), ' '), sl[2].end());
                sl.erase(sl.begin() + 1);

                time_t a = date1(sl[0]);
                sl[0] = to_string(a);
                sl[1] = to_string(expirationDiff(sl[1], a));

                for (size_t k = 0; k < sl.size() - 1; ++k) {
                    oss << sl[k] << ",";
                }
                oss << sl[sl.size() - 1] << "\n";
            } else if (c == true) {
                c = false;

                sl.erase(sl.begin() + 4, sl.begin() + 6);
                sl.erase(sl.begin() + 5, sl.begin() + 7);
                sl.erase(sl.begin() + 6);
                sl.erase(sl.begin() + 7, sl.begin() + 12);
                sl.erase(sl.begin() + 1);

                for (size_t k = 0; k < sl.size() - 1; ++k) {
                    oss << sl[k] << ",";
                }
                oss << sl[sl.size() - 1] << "\n";
            }
        }
        outFile << oss.str();
        inputFile.close();
        outFile.close();
        cerr << "ok\n";

        if (y == 6) {
            break;
        }
        ++y;
    }
    return 0;
}

int pfut1_17() {
    string line;
    ostringstream oss;
    ifstream inputFile("downloads/future/2017_fut_utf8.csv");
    if (!inputFile.is_open()) {
        cerr << "Unable to open file for reading.\n";
    }

    ofstream outFile("downloads/future/2017_fut_utf8_pfut1.csv");
    if (!outFile.is_open()) {
        cerr << "Unable to open file for writing.\n";
    }

    bool c = true;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<string> sl;
        while (getline(iss, line, ',')) {
            sl.push_back(line);
        }

        if ((sl[1] == "TX") && (sl[2].size() != 13) && (sl[sl.size() - 1].find("一般") != string::npos)) {
            sl.erase(sl.begin() + 4, sl.begin() + 6);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 6);
            sl.erase(sl.begin() + 7, sl.begin() + 13);
            sl[2].erase(remove(sl[2].begin(), sl[2].end(), ' '), sl[2].end());
            sl.erase(sl.begin() + 1);
            time_t a = date1(sl[0]);
            sl[0] = to_string(a);
            sl[1] = to_string(expirationDiff(sl[1], a));

            for (size_t k = 0; k < sl.size() - 1; ++k) {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
        } else if (c == true) {
            c = false;

            sl.erase(sl.begin() + 4, sl.begin() + 6);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 6);
            sl.erase(sl.begin() + 7, sl.begin() + 12);
            sl.erase(sl.begin() + 8);
            sl.erase(sl.begin() + 1);
            sl.erase(sl.end() - 1);

            for (size_t k = 0; k < sl.size() - 1; ++k) {
                if (sl[k] == "-") { sl[k] = "0"; }
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
        }
    }
    outFile << oss.str();
    inputFile.close();
    outFile.close();
    cerr << "ok\n";
    return 0;
}

int pfut1_18t22() {
    string in1 = "20";
    string in2 = "_fut_utf8";
    int y = 18;
    string sy;
    string line;
    while (true) {
        ostringstream oss;
        sy = to_string(y);
        ifstream inputFile("downloads/future/" + in1 + sy + in2 + ".csv");
        if (!inputFile.is_open()) {
            cerr << "Unable to open file for reading.\n";
            break;
        }

        ofstream outFile("downloads/future/" + in1 + sy + in2 + "_pfut1.csv");
        if (!outFile.is_open()) {
            cerr << "Unable to open file for writing.\n";
            break;
        }

        bool c = true;

        while (getline(inputFile, line)) {
            if ((line.find("一般") == string::npos) && not c) continue;
            
            istringstream iss(line);
            vector<string> sl;
            while (getline(iss, line, ',')) {
                sl.push_back(line);
            }

            if (sl[1] == "TX") {
                sl[2].erase(remove(sl[2].begin(), sl[2].end(), ' '), sl[2].end());
                if (sl[2].size() == 13) continue;
                sl.erase(sl.begin() + 4, sl.begin() + 6);
                sl.erase(sl.begin() + 5, sl.begin() + 7);
                sl.erase(sl.begin() + 6);
                sl.erase(sl.begin() + 7, sl.end());
                sl.erase(sl.begin() + 1);
                time_t a = date1(sl[0]);
                sl[0] = to_string(a);
                sl[1] = to_string(expirationDiff(sl[1], a));

                for (size_t k = 0; k < sl.size() - 1; ++k) {
                    if ((sl[k] == " ") || (sl[k] == "") || (sl[k] == "-")) {
                        sl[k] = "0";
                    }
                    oss << sl[k] << ",";
                }
                oss << sl[sl.size() - 1] << "\n";
            } else if (c == true) {
                c = false;

                sl.erase(sl.begin() + 4, sl.begin() + 6);
                sl.erase(sl.begin() + 5, sl.begin() + 7);
                sl.erase(sl.begin() + 6);
                sl.erase(sl.begin() + 7, sl.end());
                sl.erase(sl.begin() + 1);

                for (size_t k = 0; k < sl.size() - 1; ++k) {
                    if (sl[k] == "-") { sl[k] = "0"; }
                    oss << sl[k] << ",";
                }
                oss << sl[sl.size() - 1] << "\n";
            }
        }
        outFile << oss.str();
        inputFile.close();
        outFile.close();
        cerr << "ok\n";

        if (y == 22) {
            break;
        }
        ++y;
    }
    return 0;
}

int main() {
    int a = pfut1_15t16();
    cout << a << endl;
    int b = pfut1_17();
    cout << b << endl;
    int c = pfut1_18t22();
    cout << c << endl;
    return 0;
}

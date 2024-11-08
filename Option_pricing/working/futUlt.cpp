#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <memory>
#include "date.hpp"
using namespace std;

int main() {
    ifstream co("fut_count.csv");
    if (!co.is_open()) {
        cerr << "Can't open fut_count.csv" << endl;
        return 1;
    }
    string line;
    getline(co, line);
    int dateMax = stoi(line);
    cout << "Date Max: " << dateMax << endl;
    co.close();

    ifstream head("futHeader.csv");
    if (!head.is_open()) {
        cerr << "Can't open futHeader.csv";
        return 1;
    }
    getline(head, line);
    head.close();
    ostringstream hoss;
    hoss << line;
    string hd = hoss.str();

    ifstream futfs("futFiles.csv");
    if (!futfs.is_open()) {
        cerr << "Can't open futFiles.csv";
        return 1;
    }
    vector<vector<double>> allvec;
    while (getline(futfs, line)) {
        ifstream futi("downloads/future/" + line);
        if (!futi.is_open()) {
            cerr << "Can't open file: downloads/future/" << line << endl;
            return 1;
        }
        cout << "downloads/future/" + line << " opened" << endl;
        getline(futi, line);
        while (getline(futi, line)) {
            if (line.empty()) continue;
            istringstream iss(line);
            vector<double> svec;
            string cell;
            while (getline(iss, cell, ',')) {
                svec.push_back(stod(cell));
            }
            allvec.push_back(svec);
        }
        futi.close();
    }
    futfs.close();

    double date = allvec[0][0];
    vector<double> osvec;
    int dateCount = 0;
    vector<vector<double>> oallvec;
    osvec.push_back(date);
    for (auto svec : allvec) {
        if (date == svec[0]) {
            dateCount ++;
            for (size_t k = 1; k < svec.size(); k++) {
                osvec.push_back(svec[k]);
            }
        } else {
            date = svec[0];
            for (int i = 0; i < (dateMax - dateCount); i++) {
                for (int j = 0; j < 5; j++) {
                    osvec.push_back(0);
                }
            }
            dateCount = 1;
            oallvec.push_back(osvec);
            osvec = {};
            osvec.clear();
            osvec.push_back(date);
            for (size_t k = 1; k < svec.size(); k++) {
                osvec.push_back(svec[k]);
            }
        }
    }
    for (int i = 0; i < (dateMax - dateCount); i++) {
        for (int j = 0; j < 5; j++) {
            osvec.push_back(0);
        }
    }
    oallvec.push_back(osvec); 
    cout << "Processed" << endl;

    ostringstream oss;
    int year = 16;
    for (auto i : oallvec) {
        if (i[0] >= date2("20" + to_string(year) + "-01-01")) {
            ofstream output("futData/20" + to_string(year - 1) + "futData.csv");
            if (!output.is_open()) {
                cerr << "Can't open futData/20" + to_string(year - 1) + "futData.csv";
                return 1;
            }
            output << hd << oss.str();
            output.close();
            cout << "Outputted to futData/20" + to_string(year - 1) + "futData.csv" << endl;
            oss.str("");
            oss.clear();
            year ++;
        }
        oss << "\n";
        for (auto j : i) {
            oss << fixed << setprecision(6) << j << ",";
        }
        string temp = oss.str();
        oss.str("");
        oss.clear();
        if (!temp.empty()) temp.pop_back();
        oss << temp;
    }
    ofstream output("futData/20" + to_string(year - 1) + "futData.csv");
    if (!output.is_open()) {
        cerr << "Can't open futData/20" + to_string(year - 1) + "futData.csv";
        return 1;
    }
    output << hd << oss.str();
    output.close();
    cout << "Outputted to futData/20" + to_string(year - 1) + "futData.csv" << endl;

    return 0;
}

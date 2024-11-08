#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "date.hpp"

using namespace std;

int parse(const string fn, const string ofn) {
    ifstream cpi(fn);
    if (!cpi.is_open()) {
        cerr << "Error: Could not open the file:" << fn << endl;
        return 1;
    }

    string line, sline;
    vector<string> sv;
    ostringstream oss;
    bool firstLine = true;

    while (getline(cpi, line)) {
        sv.clear();
        stringstream ss(line);

        while (getline(ss, sline, ',')) {
            sv.push_back(sline);
        }

        if (!sv.empty() && !firstLine) {
            sv[0] = to_string(date3(sv[0]));
        }
        
        if (firstLine) {
            firstLine = false;
        }

        oss << sv[0];
        for (size_t i = 1; i < sv.size(); ++i) {
            oss << "," << sv[i];
        }
        oss << "\n";
    }

    cpi.close();

    ofstream cpi_c(ofn);
    if (!cpi_c.is_open()) {
        cerr << "Error: Could not open the file:" << ofn << endl;
        return 1;
    }

    cpi_c << oss.str();
    cpi_c.close();

    return 0;
}

int main() {
    ifstream c("cpiFiles.csv");
    ofstream d("1mfiles.csv");
    string line, fn, mod;
    int a;
    while (getline(c, line)) {
        size_t pos = line.find(",");
        fn = line.substr(0, pos);
        mod = fn.substr(0, fn.size() - 4) + "_c" + fn.substr(fn.size() - 4);
        a = parse(fn, mod);
        cout << a << endl;
        d << mod << line.substr(pos) << "\n";
    }
    c.close();
    d.close();
    return 0;
}

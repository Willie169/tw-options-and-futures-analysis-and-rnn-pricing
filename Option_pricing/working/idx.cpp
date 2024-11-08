#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "date.hpp"

using namespace std;

int idx1(string file)
{
    ifstream inputFile(file);
    if (!inputFile.is_open())
    {
        cerr << "Unable to open file for reading:" << file << endl;
        return 1;
    }
    
    size_t pos = file.find_last_of('.');
    string newfile = file.substr(0, pos) + "_idx1" + file.substr(pos);

    ofstream outFile(newfile);
    if (!outFile.is_open())
    {
        cerr << "Unable to open file for writing:" << newfile << endl;
        return 1;
    }

	bool c = 1;
    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<string> sl;
        while (getline(iss, line, ','))
        {
            sl.push_back(line);
        }

        sl.erase(sl.begin() + 2, sl.begin() + 4);
        sl.erase(sl.begin() + 3);
        if (c == 1) {
        	c = 0;
        } else {
        	sl[0] = to_string(date2(sl[0]));
        }
        ostringstream oss;
        for (size_t k = 0; k < sl.size()-1; ++k)
        {
            oss << sl[k] << ",";
        }
        oss << sl[sl.size()-1] << "\n";
        outFile << oss.str();
    }

    inputFile.close();
    outFile.close();
    cerr << "ok\n";

    return 0;
}

int main() {
    int c = idx1("downloads/twii/^TWII.csv");
    cout << c << endl;
    int d = idx1("downloads/ixic/^IXIC.csv");
    cout << d << endl;
    return 0;
}

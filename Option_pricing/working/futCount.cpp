#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int count(const string& fn) {
	ifstream fut(fn);
	int count = 1, mc = 0;
	string d = "";
	string line;
	while (getline(fut, line)) {
		size_t pos = line.find(",");
		string date = line.substr(0, pos);
		if (d == date) {
            count ++;
		} else {
			d = date;
			mc = max(mc, count);
			count = 1;
		}
	}
	
	fut.close();
	
	return mc;
}

int main()
{
	ifstream ff("futFiles.csv");
	
	string line;
	int c = 0;
	while (getline(ff, line)) {
		int d = count("downloads/future/" + line);
        c = max(c, d);
	}
	
	ff.close();
	
	ofstream fu("fut_count.csv");

    cout << c << endl;
    fu << to_string(c) << "\n";
    
    fu.close();
	
	return 0;
}

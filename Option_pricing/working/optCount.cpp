#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> count(const string& fn) {
	ifstream opt(fn);
	int count = 1, mc = 0, count2 = 1, mc2 = 0, count3 = 1, mc3 = 0;
	string d = "", e = "", f = "";
	string line;
	while (getline(opt, line)) {
		size_t pos = line.find(",");
		string date = line.substr(0, pos);
		string left = line.substr(pos + 1);
		size_t pos2 = left.find(",");
		string expr = left.substr(0, pos2);
		left = left.substr(pos2 + 1);
		size_t pos3 = left.find(",");
		left = left.substr(0, pos3);
		if (d == date) {
			if (e == expr) {
				if (f == left) {
					count3 ++;
				} else {
					f = left;
					mc3 = max(mc3, count3);
					count3 = 1;
					count2 ++;
				}
			} else {
				f = "";
				mc3 = max(mc3, count3);
				count3 = 1;
				e = expr;
				mc2 = max(mc2, count2);
				count2 = 1;
			    count ++;
			}
		} else {
			f = "";
			mc3 = max(mc3, count3);
			count3 = 1;
			e = "";
			mc2 = max(mc2, count2);
			count2 = 1;
			d = date;
			mc = max(mc, count);
			count = 1;
		}
	}
	
	opt.close();
	
	vector<int> vec = {mc, mc2, mc3};
	
	return vec;
}

int main()
{
	ifstream ff("optFiles.csv");
	
	string line;
	vector<int> c = {0, 0, 0};
	while (getline(ff, line)) {
		vector<int> d = count("downloads/option/" + line);

		for (size_t i = 0; i < c.size(); i++) {
			c[i] = max(c[i], d[i]);
		}
	}
	
	ff.close();
	
	ofstream op("opt_count.csv");
	for (auto i : c) {
        cout << i << endl;
		op << to_string(i) << "\n";
	}
	op.close();
	
	return 0;
}

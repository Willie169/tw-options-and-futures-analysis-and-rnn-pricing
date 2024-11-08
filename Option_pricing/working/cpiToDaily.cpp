#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

int main()
{
	ifstream mf("1mfiles.csv");
	string line, fn, key;
    vector<string> dk, mk1, dk1;
	size_t pos;
    vector<vector<string>> cpis;

	ostringstream oss;
	ifstream od("1dData.csv");
	getline(od, line);
	oss << line;

    while (getline(mf, line)) {
        size_t p = line.find(",");
        fn = line.substr(0, p);
        ifstream cpi(fn);
        oss << line.substr(p);
    	getline(cpi, line);
        vector<string> vec;
        getline(cpi, line);
    	while (getline(cpi, line))
    	{
    		vec.push_back(line);
    	}
        cpi.close();
        cpis.push_back(vec);
    }
    oss << "\n";    

    for (auto vec : cpis) {
    	pos = vec[0].find(",");
    	if (pos != string::npos)
    	{
    		dk.push_back(vec[0].substr(pos + 1));
    	}
    
    	pos = vec[1].find(",");
    	if (pos != string::npos)
    	{
    		mk1.push_back(vec[1].substr(0, pos));
    		dk1.push_back(vec[1].substr(pos + 1));
    	}
    }

    int i = 2;
	while (getline(od, line))
	{
		pos = line.find(',');
		if (pos != string::npos)
		{
			key = line.substr(0, pos);
		} else {
            cout << "e";
            return 1;
        }
        oss << line;

        for (size_t j = 0; j < cpis.size(); j++) {
    		if (stoi(key) >= stoi(mk1[j]))
    		{
    			dk[j] = dk1[j];
    			if (i < cpis[j].size())
    			{
    				pos = cpis[j][i].find(',');
    				mk1[j] = cpis[j][i].substr(0, pos);
                    dk1[j] = cpis[j][i].substr(pos + 1);
    				i++;
    			}
    		}
    		oss << "," << dk[j];
        }
        oss << "\n";
	}

	ofstream output("Daily.csv");
	string k = oss.str();
	if (k.empty())
		return 1;
	k.pop_back();
	output << k;
	output.close();

	return 0;
}

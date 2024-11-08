#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ostream>
#include "date.hpp"

using namespace std;

int main()
{
	ifstream inputFile("downloads/treasury/yield-curve-rates-1990-2023.csv");
	if (!inputFile.is_open())
	{
		cerr << "Error: Unable to open input file" << endl;
		return 1;
	}

	vector<string> lines;
	vector<string> sl;
	string line;
	string temp;
	bool c = true;

	while (getline(inputFile, line))
	{
		istringstream iss(line);
		vector<string>().swap(sl);
		ostringstream oss;
		bool d = 1, k = 0;

		if (c == true)
		{
			c = false;
			while (getline(iss, line, ','))
			{
				sl.push_back(line);
			}
			sl.erase(sl.begin() + 2);
			sl.erase(sl.begin() + 3);
		}
		else
		{
			while (getline(iss, line, ','))
			{
				if (d == true)
				{
					temp = line;
					d = false;
					if (temp.substr(1, 1) == "/")
					{
						temp = "0" + temp;
					}

					if (temp.substr(4, 1) == "/")
					{
						temp = temp.substr(0, 3) + "0" + temp.substr(3);
					}

					temp = "20" + temp.substr(6) + "/" + temp.substr(0, 5);
					if (stoi(temp.substr(0, 4)) > 2014 && stoi(temp.substr(0, 4)) < 2023)
					{
						time_t ttemp = date1(temp);
						sl.push_back(to_string(ttemp));
					}
					else
					{
						k = 1;
						break;
					}
				}
				else
				{
					sl.push_back(line);
				}
			}
			if (k == 0)
			{
				sl.erase(sl.begin() + 2);
				sl.erase(sl.begin() + 3);
			}
			else
			{
				continue;
			}
		}

		for (size_t i = 0; i < sl.size(); ++i)
		{
			oss << sl[i];
			if (i < sl.size() - 1)
			{
				oss << ",";
			}
		}

		lines.push_back(oss.str());
	}

	inputFile.close();

	lines.erase(remove(lines.begin(), lines.end(), ""), lines.end());
	reverse(lines.begin() + 1, lines.end());

	ostringstream alloss;

	for (const string &sortedLine : lines)
	{
		alloss << sortedLine << '\n';
	}

	ofstream outputFile("downloads/treasury/yield-curve-rates-2015-2022.csv");
	if (!outputFile.is_open())
	{
		cerr << "Error: Unable to open output file\n";
		return 1;
	}

	outputFile << alloss.str();

	outputFile.close();

	return 0;
}

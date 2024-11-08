#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "date.hpp"

using namespace std;

string popt1_15(const string& csvContent)
{
    istringstream inputFile(csvContent);
    ostringstream outputFile;
    string line;
    bool c = true;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<string> sl;
        string token;
        while (getline(iss, token, ','))
        {
            sl.push_back(token);
        }

        if (sl[1] == "TXO")
        {
            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl[1].erase(remove(sl[1].begin(), sl[1].end(), ' '), sl[1].end());

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1];
            outputFile << oss.str() << "\n";
        }
        else if (c == true)
        {
            c = false;

            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl.erase(sl.end() - 1);

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1];
            outputFile << oss.str() << "\n";
        }
    }
	string o = outputFile.str();
    o.erase(o.size() - 1);
    return o;
}

string popt1_16(const string& csvContent)
{
    istringstream inputFile(csvContent);
    ostringstream outputFile;
    string line;
    bool c = true;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<string> sl;
        string token;
        while (getline(iss, token, ','))
        {
            sl.push_back(token);
        }

        if (sl[1] == "TXO")
        {
            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl[1].erase(remove(sl[1].begin(), sl[1].end(), ' '), sl[1].end());

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
        else if (c)
        {
            c = false;

            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl.erase(sl.end() - 1);

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
    }
	string o = outputFile.str();
    o.erase(o.size() - 1);
    return o;
}

string popt1_17(const string& csvContent)
{
    istringstream inputFile(csvContent);
    ostringstream outputFile;
    string line;
    bool c = true;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<string> sl;
        string token;
        while (getline(iss, token, ','))
        {
            sl.push_back(token);
        }

        if (sl[1] == "TXO")
        {
            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl[1].erase(remove(sl[1].begin(), sl[1].end(), ' '), sl[1].end());
            sl.erase(sl.end() - 2);

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
        else if (c)
        {
            c = false;

            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl.erase(sl.end() - 2);

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
    }
	string o = outputFile.str();
    o.erase(o.size() - 1);
    return o;
}

string popt1_18t21(const string& csvContent)
{
    istringstream inputFile(csvContent);
    ostringstream outputFile;
    string line;
    bool c = true;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<string> sl;
        string token;
        while (getline(iss, token, ','))
        {
            sl.push_back(token);
        }

        if (sl[1] == "TXO")
        {
            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl[1].erase(remove(sl[1].begin(), sl[1].end(), ' '), sl[1].end());
            sl.erase(sl.end() - 2);

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
        else if (c)
        {
            c = false;

            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7);
            sl.erase(sl.begin() + 8, sl.begin() + 13);
            sl.erase(sl.end() - 2);

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
    }
	string o = outputFile.str();
    o.erase(o.size() - 1);
    return o;
}

string popt1_22(const string& csvContent)
{
    istringstream inputFile(csvContent);
    ostringstream outputFile;
    string line;
    bool c = true;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<string> sl;
        while (getline(iss, line, ','))
        {
            sl.push_back(line);
        }

        if (sl[1] == "TXO")
        {
        	sl.erase(sl.begin() + 1);
    		sl.erase(sl.begin() + 5, sl.begin() + 7);
    		sl.erase(sl.begin() + 7, sl.begin() + 14);
    		sl.erase(sl.begin() + 8, sl.end());

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
        else if (c)
        {
            c = false;

            sl.erase(sl.begin() + 1);
            sl.erase(sl.begin() + 5, sl.begin() + 7);
            sl.erase(sl.begin() + 7, sl.begin() + 14);
            sl.erase(sl.begin() + 8, sl.end());

            ostringstream oss;
            for (size_t k = 0; k < sl.size() - 1; ++k)
            {
                oss << sl[k] << ",";
            }
            oss << sl[sl.size() - 1] << "\n";
            outputFile << oss.str();
        }
    }
	string o = outputFile.str();
    o.erase(o.size() - 1);
    return o;
}

vector<string> popt1(const string &dirc, const vector<string> &pfiles) {
    vector<string> files = pfiles;
    for (int index = 0; index < files.size(); ++index) {
        string &i = files[index];
        ifstream file(dirc + i);
        string content;

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                content += line + "\n";
            }
            file.close();
            content.pop_back();
        } else {
            cerr << "Unable to open file: " << i << endl;
            vector<string> e = {"ife"};
            return e;
        }

        int y = stoi(i.substr(2, 2));
        i.insert(i.size() - 4, "_popt1");
        ofstream output_file(dirc + i);
        if (output_file.is_open()) {
            if (y == 15) {
                output_file << popt1_15(content);
            } else if (y == 16) {
                output_file << popt1_16(content);
            } else if (y == 17) {
                output_file << popt1_17(content);
            } else if (y >= 18 && y <= 21) {
                output_file << popt1_18t21(content);
            } else if (y == 22) {
                output_file << popt1_22(content);
            } else {
                cerr << "File name out of scope: " << i << endl;
                i = i.substr(1);
                files.push_back("ine");
                return files;
            }
            output_file.close();
        } else {
            cerr << "Unable to create output file: " << i << endl;
            i = i.substr(1);
            files.push_back("ofe");
            return files;
        }
    }
    return files;
}

string popt2_15t16(const string &csvContent)
{
	istringstream inputFile(csvContent);
	ostringstream outputFile;
	string line;
	bool c = true;

	while (getline(inputFile, line))
	{
		istringstream iss(line);
		vector<string> sl;
		string token;
		while (getline(iss, token, ','))
		{
			sl.push_back(token);
		}

		if (c == true)
		{
			c = false;
			ostringstream oss;
			for (size_t k = 0; k < sl.size() - 1; ++k)
			{
				oss << sl[k] << ",";
			}
			oss << sl[sl.size() - 1];
			outputFile << oss.str() << "\n";
		}
		else
		{
			time_t date = date1(sl[0]);
			sl[0] = to_string(date);
			time_t diff = expirationDiff(sl[1], date);
			sl[1] = to_string(diff);
			sl[3] = (sl[3] == "買權") ? "1" : "0";
			ostringstream oss;
			for (size_t k = 0; k < sl.size() - 1; ++k)
			{
				oss << sl[k] << ",";
			}
			oss << sl[sl.size() - 1];
			outputFile << oss.str() << "\n";
		}
	}
	string o = outputFile.str();
    if (!o.empty()) o.erase(o.size() - 1);
    return o;
}

string popt2_17t22(const string &csvContent)
{
	istringstream inputFile(csvContent);
	ostringstream outputFile;
	string line;
	bool c = true;

	while (getline(inputFile, line))
	{
		istringstream iss(line);
		vector<string> sl;
		string token;
		while (getline(iss, token, ','))
		{
			sl.push_back(token);
		}

		if (c == true)
		{
			c = false;
			sl.erase(sl.end() - 1);
            for (auto i : sl) {
                i.erase(remove(i.begin(), i.end(), ' '), i.end());
                i.erase(remove(i.begin(), i.end(), '-'), i.end());
            }
			ostringstream oss;
			for (size_t k = 0; k < sl.size() - 1; ++k)
			{
				oss << sl[k] << ",";
			}
			oss << sl[sl.size() - 1];
			outputFile << oss.str() << "\n";
		}
		else if (sl.back().find("一般") != string::npos)
		{
			time_t date = date1(sl[0]);
			sl[0] = to_string(date);
			time_t diff = expirationDiff(sl[1], date);
			sl[1] = to_string(diff);
			sl[3] = (sl[3] == "買權") ? "1" : "0";
			ostringstream oss;
            sl.erase(sl.end() - 1);
			for (size_t k = 0; k < sl.size() - 1; ++k)
			{
				if (sl[k] == "-" || sl[k] == "")
				{
					sl[k] = "0";
				}
				oss << sl[k] << ",";
			}
			oss << sl[sl.size() - 1];
			outputFile << oss.str() << "\n";
		}
	}
	string o = outputFile.str();
    if (!o.empty()) o.erase(o.size() - 1);
    return o;
}

vector<string> popt2(const string &dirc, const vector<string> &pfiles) {
    vector<string> files = pfiles;
    for (int index = 0; index < files.size(); ++index) {
        string &i = files[index];
        ifstream file(dirc + i);
        string content;

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                content += line + "\n";
            }
            file.close();
            content.pop_back();
        } else {
            cerr << "Unable to open file: " << i << endl;
            vector<string> e = {"ife"};
            return e;
        }

        int y = stoi(i.substr(2, 2));
        i.insert(i.size() - 4, "_popt2");
        ofstream output_file(dirc + i);
        if (output_file.is_open()) {
            if (y >= 15 && y <= 16) {
                output_file << popt2_15t16(content);
            } else if (y >= 17 && y <= 22) {
                output_file << popt2_17t22(content);
            } else {
                cerr << "File name out of scope: " << i << endl;
                i = i.substr(1);
                files.push_back("ine");
                return files;
            }
            output_file.close();
        } else {
            cerr << "Unable to create output file: " << i << endl;
            i = i.substr(1);
            files.push_back("ofe");
            return files;
        }
    }
    return files;
}

int main()
{
    ifstream opt("opt_files.csv");
	vector<string> files;
    string line;
    while (getline(opt, line)) {
        files.push_back(line);
    }
    opt.close();
	string dirc = "downloads/option/";
    files = popt1(dirc, files);
    for (auto i : files){
        cout << i << endl;
    }
    files = popt2(dirc, files);
    for (auto i : files){
        cout << i << endl;
    }
    return 0;
}

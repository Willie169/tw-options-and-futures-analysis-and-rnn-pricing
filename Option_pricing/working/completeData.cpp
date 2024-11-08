#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <tuple>
#include "date.hpp"
using namespace std;

map<double, vector<double>> mergeMaps(const map<double, vector<double>>& map1, const map<double, vector<double>>& map2) {
    map<double, vector<double>> result = map1;
    
    for (auto it = map2.begin(); it != map2.end(); ++it) {
        result[it->first] = it->second;
    }
    
    return result;
}

tuple<string, map<double, vector<double>>> read_csv(const string& filename) {
    cout << "Reading " << filename << endl;
    ifstream file(filename);
    if (!file.is_open()) cerr << "Can't open " << filename;
    map<double, vector<double>> data;
    string line, cell;

    getline(file, line);
    
    size_t cpos = line.find(",");
    string head = line.substr(cpos);
	
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream lineStream(line);
        vector<double> row;
        double key;
        bool i = 0;

        while (getline(lineStream, cell, ',')) {
            if (!i) {
                key = stod(cell);
                i = 1;
            } else {
                try{
                	row.push_back(stod(cell));
                } catch (const exception& e) {
                	cout << cell << endl << e.what() << endl;
                	row.push_back(0);
                }
            }
        }

        data[key] = row;
    }

    file.close();

    auto result = make_tuple(head, data);
    return result;
}

map<double, string> merge_csv(const vector<map<double, vector<double>>>& data_maps) {
    ostringstream file;
    set<double> all_keys;
    map<double, string> mm;

    for (const auto& data_map : data_maps) {
        for (const auto& entry : data_map) {
            all_keys.insert(entry.first);
        }
    }
    for (const auto& key : all_keys) {
        for (const auto& data_map : data_maps) {
            if (data_map.find(key) != data_map.end()) {
                for (const auto& value : data_map.at(key)) {
                    file << "," << fixed << setprecision(6) << value;
                }
            } else {
                for (size_t x = 0; x < (data_map.begin()->second).size(); x++) {
                    file << "," << fixed << setprecision(6) << 0;
                }
            }
        }
        mm[key] = file.str();
        file.str("");
        file.clear();
    }

    return mm;
}

int main() {
    vector<map<double, vector<double>>> data_maps(3);
    ostringstream header;
    header << "日期（Unix time）";
    string temp;

    auto da = read_csv("Daily.csv");
    header << get<0>(da);
    data_maps[0] = get<1>(da);

    vector<string> files;
    string line;
    ifstream fdf("futDataFiles.csv");
    while (getline(fdf, line)) {
    	files.push_back(line);
    }
    fdf.close();
    for (size_t i = 0; i < files.size(); ++i) {
        tuple<string, map<double, vector<double>>> r = read_csv("futData/" + files[i]);
        data_maps[1] = mergeMaps(data_maps[1], get<1>(r));
        if (i == 0) temp = get<0>(r);
    }
    header << temp;

    files = {};
    files.clear();
    ifstream odf("optDataFiles.csv");
    while (getline(odf, line)) {
    	files.push_back(line);
    }
    odf.close();
    for (size_t i = 0; i < files.size(); ++i) {
        tuple<string, map<double, vector<double>>> r = read_csv("optData/" + files[i]);
        data_maps[2] = mergeMaps(data_maps[2], get<1>(r));
        if (i == 0) temp = get<0>(r);
    }
    header << temp;

    const auto& merged = merge_csv(data_maps);

    ostringstream oss;
    int year = 16;
    for (const auto& pair : merged) {
        if (pair.first >= date2("20" + to_string(year) + "-01-01")) {
            ofstream output("completeData/20" + to_string(year - 1) + "completeData.csv");
            output << header.str() << "\n" << oss.str();
            output.close();
            cout << "completeData/20" + to_string(year - 1) + "completeData.csv" << endl;
            oss.str("");
            oss.clear();
            year ++;
        }
        oss << fixed << setprecision(6) << pair.first << pair.second << "\n";
    }
    ofstream output("completeData/20" + to_string(year - 1) + "completeData.csv");
    output << header.str() << "\n" << oss.str();
    output.close();
    cout << "completeData/20" + to_string(year - 1) + "completeData.csv" << endl;

    cout << "CSV files merged successfully." << endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <set>
using namespace std;

string replaceAll(const string& str, const string& from, const string& to) {
    string result = str;
    size_t start_pos = 0;
    while((start_pos = result.find(from, start_pos)) != string::npos) {
        result.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return result;
}

map<string, vector<string>> read_csv(const string& filename) {
    ifstream file(filename);
    ostringstream oss;
    map<string, vector<string>> data;
    string line, cell;
    bool i = 0;
    
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream lineStream(line);
        vector<string> row;
        string key;
        i = 0;

        while (getline(lineStream, cell, ',')) {
            if (!i) {
                key = cell;
                i = 1;
            } else {
                try{
                    double db = stod(cell);
                } catch (...) {
                    cell = "0";
                }
                row.push_back(cell);
            }
        }

        data[key] = row;
    }

    file.close();

    return data;
}

string merge_csv(const vector<map<string, vector<string>>>& data_maps) {
    ostringstream file;
    set<string> all_keys;

    for (const auto& data_map : data_maps) {
        for (const auto& entry : data_map) {
            all_keys.insert(entry.first);
        }
    }
    for (const string& key : all_keys) {
        file << key;
        for (const auto& data_map : data_maps) {
            if (data_map.find(key) != data_map.end()) {
                for (const auto& value : data_map.at(key)) {
                    file << "," << value;
                }
            } else {
                for (size_t x = 0; x < (data_map.begin()->second).size(); x++) {
                    file << ",0";
                }
            }
        }
        file << "\n";
    }

    string result = file.str();
    if (!result.empty()) result.pop_back();

    return result;
}

int main() {
    vector<map<string, vector<string>>> data_maps;
    ostringstream h;
    h << "日期,臺灣加權指數開盤價,臺灣加權指數收盤價,臺灣加權指數成交量,納斯達克指數開盤價,納斯達克指數收盤價,納斯達克指數成交量,美國公債殖利率1月期,美國公債殖利率3月期,美國公債殖利率6月期,美國公債殖利率1年期,美國公債殖利率2年期,美國公債殖利率3年期,美國公債殖利率5年期,美國公債殖利率7年期,美國公債殖利率10年期,美國公債殖利率20年期,美國公債殖利率30年期,新臺幣兌美元即期銀行與顧客間買進匯率,新臺幣兌美元即期銀行與顧客間賣出匯率,新臺幣兌美元即期銀行間收盤匯率,遠期信用狀美金年利率,新臺幣兌美元10天買入匯率,新臺幣兌美元10天賣出匯率,新臺幣兌美元30天買入匯率,新臺幣兌美元30天賣出匯率,新臺幣兌美元60天買入匯率,新臺幣兌美元60天賣出匯率,新臺幣兌美元90天買入匯率,新臺幣兌美元90天賣出匯率,新臺幣兌美元120天買入匯率,新臺幣兌美元120天賣出匯率,新臺幣兌美元180天買入匯率,新臺幣兌美元180天賣出匯率\n";
    
    vector<string> files;
    string line;
    ifstream odf("1dfiles.csv");
    while (getline(odf, line)) {
    	files.push_back(line);
    }
    
    for (size_t i = 0; i < files.size(); ++i) {
        map<string, vector<string>> r = read_csv("downloads/" + files[i]);
        data_maps.push_back(r);
    }
    
    string merged = merge_csv(data_maps);
    h << merged;

    ofstream op("1dData.csv");
    op << h.str();
    op.close();
    
    cout << "CSV files merged successfully." << endl;
    return 0;
}

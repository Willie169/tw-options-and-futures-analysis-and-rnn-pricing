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
    ifstream co("opt_count.csv");
    if (!co.is_open()) {
        cerr << "Can't open opt_count.csv" << endl;
        return 1;
    }
    string line;
    getline(co, line);
    int dateMax = stoi(line);
    cout << "Date Max: " << dateMax << endl;
    getline(co, line);
    int exprMax = stoi(line);
    cout << "Expiration Max: " << exprMax << endl;
    co.close();

    ifstream head("optHeader.csv");
    if (!head.is_open()) {
        cerr << "Can't open optHeader.csv";
        return 1;
    }
    getline(head, line);
    head.close();
    ostringstream hoss;
    hoss << line;
    string hd = hoss.str();

    ifstream optfs("optFiles.csv");
    if (!optfs.is_open()) {
        cerr << "Can't open optFiles.csv";
        return 1;
    }
    vector<vector<double>> allvec;
    while (getline(optfs, line)) {
        ifstream opti("downloads/option/" + line);
        if (!opti.is_open()) {
            cerr << "Can't open file: downloads/option/" << line << endl;
            return 1;
        }
        cout << "downloads/option/" + line << " opened" << endl;
        getline(opti, line);
        while (getline(opti, line)) {
            if (line.empty()) continue;
            istringstream iss(line);
            vector<double> svec;
            string cell;
            while (getline(iss, cell, ',')) {
                svec.push_back(stod(cell));
            }
            allvec.push_back(svec);
        }
            opti.close();
    }
    optfs.close();

    double date = allvec[0][0], expr = allvec[0][1], price = allvec[0][2];
    vector<double> osvec, call, put;
    bool c, p;
    int exprCount = 0, dateCount = 0;
    vector<vector<double>> oallvec;
    osvec.push_back(date);
    osvec.push_back(expr);
    for (auto svec : allvec) {
        if (date == svec[0]) {
            if (expr == svec[1]) {
                if (price == svec[2]) {
                    if (svec[3] == 0) {
                        put.push_back(svec[4]);
                        put.push_back(svec[5]);
                        put.push_back(svec[6]);
                        p = 1;
                    } else {
                        call.push_back(svec[4]);
                        call.push_back(svec[5]);
                        call.push_back(svec[6]);
                        c = 1;
                    }
                } else {
                    osvec.push_back(price);
                    price = svec[2];
                    exprCount ++;
                    if (c) {
                        osvec.push_back(call[0]);
                        osvec.push_back(call[1]);
                        osvec.push_back(call[2]);
                    } else {
                        osvec.push_back(0);
                        osvec.push_back(0);
                        osvec.push_back(0);
                    }
                    if (p) {
                        osvec.push_back(put[0]);
                        osvec.push_back(put[1]);
                        osvec.push_back(put[2]);
                    } else {
                        osvec.push_back(0);
                        osvec.push_back(0);
                        osvec.push_back(0);
                    }
                    put = {};
                    call = {};
                    if (svec[3] == 0) {
                        put.push_back(svec[4]);
                        put.push_back(svec[5]);
                        put.push_back(svec[6]);
                        p = 1;
                        c = 0;
                    } else {
                        call.push_back(svec[4]);
                        call.push_back(svec[5]);
                        call.push_back(svec[6]);
                        c = 1;
                        p = 0;
                    }
                }
            } else {
                osvec.push_back(price);
                price = svec[2];
                expr = svec[1];
                exprCount ++;
                dateCount ++;
                if (c) {
                    osvec.push_back(call[0]);
                    osvec.push_back(call[1]);
                    osvec.push_back(call[2]);
                } else {
                    osvec.push_back(0);
                    osvec.push_back(0);
                    osvec.push_back(0);
                }
                if (p) {
                    osvec.push_back(put[0]);
                    osvec.push_back(put[1]);
                    osvec.push_back(put[2]);
                } else {
                    osvec.push_back(0);
                    osvec.push_back(0);
                    osvec.push_back(0);
                }
                put = {};
                call = {};
                if (svec[3] == 0) {
                    put.push_back(svec[4]);
                    put.push_back(svec[5]);
                    put.push_back(svec[6]);
                    p = 1;
                    c = 0;
                } else {
                    call.push_back(svec[4]);
                    call.push_back(svec[5]);
                    call.push_back(svec[6]);
                    c = 1;
                    p = 0;
                }
                for (int i = 0; i < (exprMax - exprCount); i ++) {
                    for (int j = 0; j < 7; j ++) {
                        osvec.push_back(0);
                    }
                }
                exprCount = 0;
                osvec.push_back(expr);
            }
        } else {
            osvec.push_back(price);
            price = svec[2];
            expr = svec[1];
            date = svec[0];
            exprCount ++;
            if (c) {
                osvec.push_back(call[0]);
                osvec.push_back(call[1]);
                osvec.push_back(call[2]);
            } else {
                osvec.push_back(0);
                osvec.push_back(0);
                osvec.push_back(0);
            }
            if (p) {
                osvec.push_back(put[0]);
                osvec.push_back(put[1]);
                osvec.push_back(put[2]);
            } else {
                osvec.push_back(0);
                osvec.push_back(0);
                osvec.push_back(0);
            }
            put = {};
            call = {};
            if (svec[3] == 0) {
                put.push_back(svec[4]);
                put.push_back(svec[5]);
                put.push_back(svec[6]);
                p = 1;
                c = 0;
            } else {
                call.push_back(svec[4]);
                call.push_back(svec[5]);
                call.push_back(svec[6]);
                c = 1;
                p = 0;
            }
            for (int i = 0; i < (exprMax - exprCount); i ++) {
                for (int j = 0; j < 7; j ++) {
                    osvec.push_back(0);
                }
            }
            exprCount = 0;
            for (int h = 0; h < (dateMax - dateCount - 1); h ++) {
                osvec.push_back(0);
                for (int i = 0; i < exprMax; i ++){
                    for (int j = 0; j < 7; j ++) {
                        osvec.push_back(0);
                    }
                }
            }
            dateCount = 0;
            oallvec.push_back(osvec);
            osvec = {};
            osvec.clear();
            osvec.push_back(date);
            osvec.push_back(expr);
        }
    }
    osvec.push_back(price);
    exprCount ++;
    if (c) {
        osvec.push_back(call[0]);
        osvec.push_back(call[1]);
        osvec.push_back(call[2]);
    } else {
        osvec.push_back(0);
        osvec.push_back(0);
        osvec.push_back(0);
    }
    if (p) {
        osvec.push_back(put[0]);
        osvec.push_back(put[1]);
        osvec.push_back(put[2]);
    } else {
        osvec.push_back(0);
        osvec.push_back(0);
        osvec.push_back(0);
    }
    put = {};
    call = {};
    for (int i = 0; i < (exprMax - exprCount); i ++) {
        for (int j = 0; j < 7; j ++) {
            osvec.push_back(0);
        }
    }
    for (int h = 0; h < (dateMax - dateCount - 1); h ++) {
        osvec.push_back(0);
        for (int i = 0; i < exprMax; i ++){
            for (int j = 0; j < 7; j ++) {
                osvec.push_back(0);
            }
        }
    }
    oallvec.push_back(osvec);
    cout << "Processed" << endl;

    ostringstream oss;
    int year = 16;
    for (auto i : oallvec) {
        if (i[0] >= date2("20" + to_string(year) + "-01-01")) {
            ofstream output("optData/20" + to_string(year - 1) + "optData.csv");
            if (!output.is_open()) {
                cerr << "Can't open optData/20" + to_string(year - 1) + "optData.csv";
                return 1;
            }
            output << hd << oss.str();
            output.close();
            cout << "Outputted to optData/20" + to_string(year - 1) + "optData.csv" << endl;
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
    ofstream output("optData/20" + to_string(year - 1) + "optData.csv");
    if (!output.is_open()) {
        cerr << "Can't open optData/20" + to_string(year - 1) + "optData.csv";
        return 1;
    }
    output << hd << oss.str();
    output.close();
    cout << "Outputted to optData/20" + to_string(year - 1) + "optData.csv" << endl;

    return 0;
}

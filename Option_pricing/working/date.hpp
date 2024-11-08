#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

time_t date1(const string& dateStr) {
    tm date = {};
    string dateS = dateStr;
    size_t pos = dateS.find("/");
    date.tm_year = stoi(dateS.substr(0, pos)) - 1900;
    dateS = dateS.substr(pos + 1);
    pos = dateS.find("/");
    date.tm_mon = stoi(dateS.substr(0, pos)) - 1;
    date.tm_mday = stoi(dateS.substr(pos + 1));
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    return mktime(&date);
}

time_t date2(const string& dateStr) {
    tm date = {};
    string dateS = dateStr;
    size_t pos = dateS.find("-");
    date.tm_year = stoi(dateS.substr(0, pos)) - 1900;
    dateS = dateS.substr(pos + 1);
    pos = dateS.find("-");
    date.tm_mon = stoi(dateS.substr(0, pos)) - 1;
    date.tm_mday = stoi(dateS.substr(pos + 1));
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    return mktime(&date);
}

time_t date3(const string dateStr) {
    tm date = {};
    int year, month;
    char discard;
    stringstream ss(dateStr);
    ss >> year >> discard >> month;
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = 1;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    return mktime(&date);
}

time_t date4(const string& dateStr) {
    tm date = {};
    string dateS = dateStr;
    size_t pos = dateS.find("/");
    date.tm_mon = stoi(dateS.substr(0, pos)) - 1;
    dateS = dateS.substr(pos + 1);
    pos = dateS.find("/");
    date.tm_mday = stoi(dateS.substr(0, pos));
    date.tm_year = stoi(dateS.substr(pos + 1)) - 1900;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    return mktime(&date);
}

time_t date5(const string dateStr) {
    tm date = {};
    stringstream ss(dateStr);
    ss >> get_time(&date, "%Y%m%d");
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    return mktime(&date);
}

time_t expirationDiff(const string expStr, time_t date) {
    string expirationStr = expStr;
    if (expirationStr.substr(6, 1) != "W") {
        expirationStr = expirationStr.substr(0, 6) + "W3";
    }
    int year = stoi(expirationStr.substr(0, 4));
    int month = stoi(expirationStr.substr(4, 2));
    int week = stoi(expirationStr.substr(7, 1));
    tm expirationDate = {};
    expirationDate.tm_year = year - 1900;
    expirationDate.tm_mon = month - 1;
    expirationDate.tm_mday = 1;
    mktime(&expirationDate);
    int firstWednesdayOffset = (3 - expirationDate.tm_wday + 7) % 7;
    expirationDate.tm_mday += firstWednesdayOffset + (week - 1) * 7;
    time_t expirationTime = mktime(&expirationDate);
    time_t diff = difftime(expirationTime, date) + 48600;
    if (diff <= 0) {
        int a = stoi(expirationStr.substr(7, 1));
        if (a == 5) return diff;
        expirationStr = expirationStr.substr(0, 7) + to_string(a + 1);
        return expirationDiff(expirationStr, date);
    }
    return diff;
}

void printTm(const tm &date) {
    cout << put_time(&date, "%Y-%m-%d %H:%M:%S") << endl;
}

int test() {
    string dateStr = "2024/05/28";
    string expirationStr = "202405W5";
    cout << expirationDiff(expirationStr, date1(dateStr)) << " seconds difference" << endl;
    time_t date1Time1 = date1("2022/10/01") + 28800;
    tm date1Result1 = *gmtime(&date1Time1);
    time_t date1Time2 = date1("2022/10/1") + 28800;
    tm date1Result2 = *gmtime(&date1Time2);
    time_t date2Time1 = date2("2022-10-01") + 28800;
    tm date2Result1 = *gmtime(&date2Time1);
    time_t date2Time2 = date2("2022-10-1") + 28800;
    tm date2Result2 = *gmtime(&date2Time2);
    time_t date3Time = date3("2022M10") + 28800;
    tm date3Result = *gmtime(&date3Time);
    time_t date4Time = date4("10/1/2022") + 28800;
    tm date4Result = *gmtime(&date4Time);
    time_t date5Time = date5("20221001") + 28800;
    tm date5Result = *gmtime(&date5Time);
    printTm(date1Result1);
    printTm(date1Result2);
    printTm(date2Result1);
    printTm(date2Result2);
    printTm(date3Result);
    printTm(date4Result);
    printTm(date5Result);
    return 0;
}

#endif

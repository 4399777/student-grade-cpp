#include "util.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

string hashPwd(const string& s) {
    unsigned long h = 5381;
    for (unsigned char c : s) h = h * 33 + c;
    return to_string(h);
}

string nowStr() {
    time_t t = time(nullptr); tm* lt = localtime(&t);
    char b[32]; strftime(b, sizeof(b), "%Y-%m-%d %H:%M:%S", lt);
    return b;
}

string stamp() {
    time_t t = time(nullptr); tm* lt = localtime(&t);
    char b[32]; strftime(b, sizeof(b), "%Y%m%d_%H%M%S", lt);
    return b;
}

vector<string> split(const string& s, char d) {
    vector<string> r; string cur;
    for (char c : s) { if (c == d) { r.push_back(cur); cur.clear(); } else cur += c; }
    r.push_back(cur);
    return r;
}

string readLine() {
    string s; getline(cin, s); return s;
}

void pause() {
    cout << "\n按回车继续..."; cin.get();
}

void logOp(const string& uid, const string& role, const string& action, const string& detail) {
    ofstream f("operation_log.txt", ios::app);
    if (f) f << nowStr() << "|" << uid << "|" << role << "|" << action << "|" << detail << "\n";
}
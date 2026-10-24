#include "common.h"
#include "store.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

extern const vector<string> SUBJECTS = {"语文","数学","英语","物理","化学"};
extern const int PASS_LINE = 60;

map<string, Student>   students;
map<string, Teacher>   teachers;
map<string, ClassInfo> classes;
map<string, string>    adminPwd;
map<string, int>       adminActive;
map<string, map<string,int> > scores;
vector<string>         loginRecords;

void saveAll() {
    ofstream fs("students.txt");
    for (map<string,Student>::iterator it = students.begin(); it != students.end(); ++it) {
        Student& s = it->second;
        fs << s.id << "|" << s.name << "|" << s.gender << "|" << s.grade << "|"
           << s.classId << "|" << s.phone << "|" << s.pwdHash << "|" << s.active << "\n";
    }
    ofstream ft("teachers.txt");
    for (map<string,Teacher>::iterator it = teachers.begin(); it != teachers.end(); ++it) {
        Teacher& t = it->second;
        ft << t.id << "|" << t.name << "|";
        for (size_t i = 0; i < t.classIds.size(); i++) { if (i) ft << ","; ft << t.classIds[i]; }
        ft << "|" << t.phone << "|" << t.pwdHash << "|" << t.active << "\n";
    }
    ofstream fc("classes.txt");
    for (map<string,ClassInfo>::iterator it = classes.begin(); it != classes.end(); ++it) {
        ClassInfo& c = it->second;
        fc << c.id << "|" << c.name << "|" << c.teacherId << "|" << c.grade << "\n";
    }
    ofstream fa("admins.txt");
    for (map<string,string>::iterator it = adminPwd.begin(); it != adminPwd.end(); ++it)
        fa << it->first << "|" << it->second << "|" << adminActive[it->first] << "\n";
    ofstream fsc("scores.txt");
    for (map<string, map<string,int> >::iterator it = scores.begin(); it != scores.end(); ++it) {
        fsc << it->first;
        for (size_t i = 0; i < SUBJECTS.size(); i++) {
            fsc << "|";
            map<string,int>::iterator j = it->second.find(SUBJECTS[i]);
            if (j != it->second.end()) fsc << j->second;
        }
        fsc << "\n";
    }
    ofstream fl("login_records.txt");
    for (size_t i = 0; i < loginRecords.size(); i++) fl << loginRecords[i] << "\n";
}

void loadAll() {
    students.clear(); teachers.clear(); classes.clear();
    adminPwd.clear(); adminActive.clear(); scores.clear(); loginRecords.clear();
    string line;
    ifstream fs("students.txt");
    while (getline(fs, line)) {
        if (line.empty()) continue;
        vector<string> p = split(line, '|'); if (p.size() < 8) continue;
        Student s;
        s.id = p[0]; s.name = p[1]; s.gender = p[2]; s.grade = p[3];
        s.classId = p[4]; s.phone = p[5]; s.pwdHash = p[6];
        s.active = atoi(p[7].c_str());
        students[s.id] = s;
    }
    ifstream ft("teachers.txt");
    while (getline(ft, line)) {
        if (line.empty()) continue;
        vector<string> p = split(line, '|'); if (p.size() < 6) continue;
        Teacher t;
        t.id = p[0]; t.name = p[1];
        if (!p[2].empty()) t.classIds = split(p[2], ',');
        t.phone = p[3]; t.pwdHash = p[4]; t.active = atoi(p[5].c_str());
        teachers[t.id] = t;
    }
    ifstream fc("classes.txt");
    while (getline(fc, line)) {
        if (line.empty()) continue;
        vector<string> p = split(line, '|'); if (p.size() < 4) continue;
        ClassInfo c;
        c.id = p[0]; c.name = p[1]; c.teacherId = p[2]; c.grade = p[3];
        classes[c.id] = c;
    }
    ifstream fa("admins.txt");
    while (getline(fa, line)) {
        if (line.empty()) continue;
        vector<string> p = split(line, '|'); if (p.size() < 3) continue;
        adminPwd[p[0]] = p[1]; adminActive[p[0]] = atoi(p[2].c_str());
    }
    ifstream fsc("scores.txt");
    while (getline(fsc, line)) {
        if (line.empty()) continue;
        vector<string> p = split(line, '|'); if (p.size() < 2) continue;
        map<string,int> m;
        for (size_t i = 0; i < SUBJECTS.size() && i + 1 < p.size(); i++)
            if (!p[i+1].empty()) m[SUBJECTS[i]] = atoi(p[i+1].c_str());
        scores[p[0]] = m;
    }
    ifstream fl("login_records.txt");
    while (getline(fl, line)) if (!line.empty()) loginRecords.push_back(line);
}

void initDefault() {
    if (!students.empty() && !teachers.empty()) return;

    ClassInfo c1; c1.id = "CS2101"; c1.name = "计算机2101班"; c1.teacherId = "T001"; c1.grade = "2021";
    ClassInfo c2; c2.id = "CS2102"; c2.name = "计算机2102班"; c2.teacherId = "T002"; c2.grade = "2021";
    classes["CS2101"] = c1; classes["CS2102"] = c2;

    Teacher t1; t1.id = "T001"; t1.name = "李明"; t1.phone = "13800000001";
    t1.pwdHash = hashPwd("123456"); t1.active = 1; t1.classIds.push_back("CS2101");
    Teacher t2; t2.id = "T002"; t2.name = "王芳"; t2.phone = "13800000002";
    t2.pwdHash = hashPwd("123456"); t2.active = 1; t2.classIds.push_back("CS2102");
    teachers["T001"] = t1; teachers["T002"] = t2;

    adminPwd["admin"] = hashPwd("admin123");
    adminActive["admin"] = 1;

    const char* names[]   = {"张伟","李娜","王磊","刘静","陈鹏","赵丽","孙浩","周琳","吴迪","郑爽","冯超","何雯"};
    const char* genders[] = {"男","女","男","女","男","女","男","女","男","女","男","女"};
    srand(2021);
    for (int i = 0; i < 12; i++) {
        Student s;
        char b[16]; sprintf(b, "%04d", i + 1);
        s.id = string("2021") + b;
        s.name = names[i]; s.gender = genders[i]; s.grade = "2021";
        s.classId = (i < 6) ? "CS2101" : "CS2102";
        s.phone = string("1380013") + b;
        s.pwdHash = hashPwd("123456"); s.active = 1;
        students[s.id] = s;
        map<string,int> m;
        for (size_t k = 0; k < SUBJECTS.size(); k++) m[SUBJECTS[k]] = 50 + rand() % 49;
        scores[s.id] = m;
    }
    saveAll();
    logOp("system", "system", "INIT_DATA", "初始化演示数据");
}
#pragma once
#include <string>
#include <vector>
#include <map>

extern const std::vector<std::string> SUBJECTS;
extern const int PASS_LINE;

struct Student  { std::string id, name, gender, grade, classId, phone, pwdHash; int active = 1; };
struct Teacher  { std::string id, name, phone, pwdHash; std::vector<std::string> classIds; int active = 1; };
struct ClassInfo{ std::string id, name, teacherId, grade; };
struct RankItem { std::string id, name; std::map<std::string,int> sc; int total = 0; double avg = 0; };

extern std::map<std::string, Student>   students;
extern std::map<std::string, Teacher>   teachers;
extern std::map<std::string, ClassInfo> classes;
extern std::map<std::string, std::string> adminPwd;
extern std::map<std::string, int>         adminActive;
extern std::map<std::string, std::map<std::string,int>> scores;
extern std::vector<std::string> loginRecords;
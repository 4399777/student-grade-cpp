#pragma once
#include <string>
#include <vector>

std::string trim(const std::string& s);
std::string hashPwd(const std::string& s);
std::string nowStr();
std::string stamp();
std::vector<std::string> split(const std::string& s, char d);
std::string readLine();
void pause();
void logOp(const std::string& uid, const std::string& role,
           const std::string& action, const std::string& detail = "");
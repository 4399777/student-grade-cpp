#include "common.h"
#include "store.h"
#include "util.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"
#include <iostream>
using namespace std;

bool verifyLogin(const string& role, const string& uid, const string& pwd, string& err) {
    string h = hashPwd(pwd);
    if (role == "student") {
        if (!students.count(uid)) { err = "账号不存在"; return false; }
        if (!students[uid].active) { err = "账号已禁用"; return false; }
        if (students[uid].pwdHash != h) { err = "密码错误"; return false; }
    } else if (role == "teacher") {
        if (!teachers.count(uid)) { err = "账号不存在"; return false; }
        if (!teachers[uid].active) { err = "账号已禁用"; return false; }
        if (teachers[uid].pwdHash != h) { err = "密码错误"; return false; }
    } else {
        if (!adminPwd.count(uid)) { err = "账号不存在"; return false; }
        if (!adminActive[uid]) { err = "账号已禁用"; return false; }
        if (adminPwd[uid] != h) { err = "密码错误"; return false; }
    }
    return true;
}

int main() {
    loadAll();
    initDefault();

    while (true) {
        cout << "\n========== 学生成绩管理系统 ==========\n";
        cout << "1.学生登录  2.教师登录  3.管理员登录  0.退出\n请选择：";
        string c = readLine();
        if (c == "0") break;
        string role;
        if (c == "1") role = "student";
        else if (c == "2") role = "teacher";
        else if (c == "3") role = "admin";
        else { cout << "无效选项\n"; continue; }

        cout << "账号："; string uid = trim(readLine());
        cout << "密码："; string pwd = readLine();

        string err;
        if (!verifyLogin(role, uid, pwd, err)) {
            cout << "[登录失败] " << err << "\n";
            logOp(uid, role, "LOGIN_FAIL", err);
            continue;
        }
        loginRecords.push_back(nowStr() + "|" + uid + "|" + role);
        saveAll();
        logOp(uid, role, "LOGIN");

        if (role == "student")      studentMenu(uid);
        else if (role == "teacher") teacherMenu(uid);
        else                        adminMenu(uid);
    }
    cout << "再见！\n";
    return 0;
}
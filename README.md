# 学生成绩管理系统（C++ 控制台版）

## 编译（没有 make 时）
g++ -std=c++11 -Iinclude src/*.cpp -o main.exe

## 编译（有 make 时）
make

## 运行
./main.exe

## 默认账号
| 角色 | 账号 | 密码 |
|---|---|---|
| 学生 | 20210001 ~ 20210012 | 123456 |
| 教师 | T001 / T002 | 123456 |
| 管理员 | admin | admin123 |

## 分工
- 组长：common.h / util.* / store.* / main.cpp
- 成员 A：src/student.cpp
- 成员 B：src/teacher.cpp
- 成员 C：src/admin.cpp
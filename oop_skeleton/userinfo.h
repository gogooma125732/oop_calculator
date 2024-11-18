//
//  userinfo.h
//  oop_skeleton
//
//  Created by Louise Nayeong Koh on 11/17/24.
// "this is second commit_integrated with 'Jieun-Lee' on 11/18/24." 


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iomanip> // for std::setprecision
using namespace std;

class UserInfo {
public:
    string name, id, pw;
    int userType;

    // 사용자 정보를 저장할 생성자
    UserInfo(const string& id, const string& pw, const string& name, const int& userType)
        : id(id), pw(pw), name(name), userType(userType) {}
};

vector<UserInfo> loadUsers(const string& filename) {
    vector<UserInfo> users;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        exit(1);  // 파일 열기 실패 시 프로그램 종료
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // 비어있는 라인은 건너뜁니다.

        stringstream ss(line);
        string name, id, pw, userType;

        if (getline(ss, name, ',') &&
            getline(ss, id, ',') &&
            getline(ss, pw, ',') &&
            getline(ss, userType, ',')) {
            users.push_back({ name, id, pw, userType });
        }
        else {
            cerr << "잘못된 데이터 형식�: " << line << endl;
        }
    }
    file.close();
    return users;
}

UserInfo* authenticateUser(const string& id, const string& pw, vector<UserInfo>& users) {
    for (auto& user : users) {
        if (user.id == id && user.pw == pw) {
            return &user; // 인증 성공 시 해당 사용자를 반환
        }
    }
    return nullptr; // 인증 실패 시 nullptr 반환
}


class Grade {
public:
    string year;
    string semester;
    string courseType;   // �̼�����
    string courseName;
    int credits;         // ����
    string grade;        // ����
    double gradePoint;   // ���� (GPA ȯ��)

    Grade(const string& year, const string& semester, const string& courseType,
        const string& courseName, int credits, const string& grade, double gradePoint)
        : year(year), semester(semester), courseType(courseType), courseName(courseName),
        credits(credits), grade(grade), gradePoint(gradePoint) {}
};

class StudentInfo : public UserInfo {
public:
    vector<Grade> grades;

    StudentInfo(const string& id, const string& pw, const string& name, const int& userType)
        : UserInfo(id, pw, name, userType) {}

    void addGrade(const Grade& grade) {
        grades.push_back(grade);
    }

    double calculateGPA(const string& semester = "��ü") {
        double totalPoints = 0;
        int totalCredits = 0;

        for (const auto& grade : grades) {
            if (semester == "��ü" || grade.semester == semester) {
                if (grade.gradePoint >= 0) { // ������ ��ȿ�� ��츸 ���
                    totalPoints += grade.gradePoint * grade.credits;
                    totalCredits += grade.credits;
                }
            }
        }
        return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
    }
};
#pragma once

//
//  userinfo.h
//  oop_skeleton
//
//  Created by Louise Nayeong Koh on 11/17/24.
// "this is third commit_integrated with 'Siwon-Kim' on 11/21/24."


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



// 교수 클래스
class Professor : public UserInfo {
private:
    vector<Subject> subjects;

public:
    // 생성자
    Professor(const string& id, const string& pw, const string& name, int userType)
        : UserInfo(id, pw, name, userType) {}

    // 과목 조회
    void viewSubjects() const {
        cout << "\n=== 담당 과목 목록 ===" << endl;
        if (subjects.empty()) {
            cout << "담당 과목이 없습니다." << endl;
            return;
        }
        for (size_t i = 0; i < subjects.size(); ++i) {
            cout << i + 1 << ". " << subjects[i].getSubjectName() << endl;
        }
    }

    // 점수 업데이트
    void updateGrades() {
        if (subjects.empty()) {
            cout << "담당 과목이 없습니다." << endl;
            return;
        }
        viewSubjects();
        cout << "점수를 업데이트할 과목의 번호를 선택하세요: "; // 과목 목록 중에서 고르게 하기
        int command;
        cin >> command;

        if (command < 1 || command > subjects.size()) {
            cout << "잘못된 선택입니다." << endl;
            return;
        }

        Subject& selectedSubject = subjects[command - 1]; //선택과목 변수 저장
        selectedSubject.displayInfo(); //학생 목록과 점수 출력

        cout << "\n점수를 업데이트할 학생의 ID를 입력하세요: ";
        string studentId;
        cin >> studentId;

        cout << "새로운 점수를 입력하세요: ";
        double newGrade;
        cin >> newGrade;

        if (selectedSubject.updateGrade(studentId, newGrade)) {
            cout << "점수가 성공적으로 업데이트되었습니다." << endl;
        }
        else {
            cout << "학생 ID를 찾을 수 없습니다." << endl;
        }
    }

    // 메뉴 표시
    void displayMenu() {
        while (true) {
            cout << "\n**** 교수 메뉴 ****" << endl;
            cout << "1. 담당 과목 조회" << endl;
            cout << "2. 학생 점수 업데이트" << endl;
            cout << "3. 종료" << endl;
            cout << "선택: ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                viewSubjects();
                // 선택한 과목의 상세 정보 보기
                if (!subjects.empty()) {
                    cout << "상세 정보를 보려면 과목 번호를 입력하세요 (0은 취소): ";
                    int subChoice;
                    cin >> subChoice;
                    if (subChoice >= 1 && subChoice <= subjects.size()) {
                        subjects[subChoice - 1].displayInfo();
                    }
                }
                break;
            case 2:
                updateGrades();
                break;
            case 3:
                cout << "메뉴를 종료합니다." << endl;
                return;
            default:
                cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
            }
        }
    }
};


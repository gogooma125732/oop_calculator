//
//  subject.h
//  oop_skeleton
//
//  Created by Siwon Kim on 11/21/24.
//


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "userinfo.h"

using namespace std;

// 과목 클래스
class Subject {
private:
    string subjectName;
    string professor;
    unordered_map<string, double> studentGrades; // 학생 ID와 점수 매핑: gpt가 시도하는 건데, 정확히 이해는 못했습니다 ㅠ
    string gradingSystem;

public:
    // 생성자
    Subject(const string& subjectName, const string& professor, const string& gradingSystem)
        : subjectName(subjectName), professor(professor), gradingSystem(gradingSystem) {}

    // 학생: 일단 과목에 대한 성적 입력을 위해 만든 건데, 학생 클래스에 나중에 합쳐질 것 같습니다.
    void addStudent(const string& studentId, double grade = 0.0) {
        studentGrades[studentId] = grade;
    }

    // 과목 정보 출력: for문 부분은 GPT가 제안해준 겁니다.
    void displayInfo() const {
        cout << "과목명: " << subjectName << endl;
        cout << "교수명: " << professor << endl;
        cout << "채점 방식: " << gradingSystem << endl;
        cout << "학생 목록 및 점수:" << endl;
        for (auto it = studentGrades.begin(); it != studentGrades.end(); ++it) {
            cout << " - " << it->first << ": " << it->second << endl;
        }
    }

    // 학생 점수 업데이트: 이부분 특히 어려웠는데, 이후에 학생 아이디를 지정했을때 없는 아이디면 업데이트가 안되는 로직을 활용합니다.
    bool updateGrade(const string& studentId, double newGrade) {
        auto it = studentGrades.find(studentId);
        if (it != studentGrades.end()) {
            it->second = newGrade;
            return true;
        }
        return false;
    }

    // 과목명 반환: 이후에 과목 조회할때 필요함
    string getSubjectName() const {
        return subjectName;
    }

    // 학생 점수 맵 반환: 학생 id와 점수를 매칭칭
    unordered_map<string, double>& getStudentGrades() {
        return studentGrades;
    }
};

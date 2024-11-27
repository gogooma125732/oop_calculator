//
//  subject.h
//  oop_skeleton
//
//  Created by Siwon Kim on 11/21/24.
//  "this is fourth commit_integrated with 'Dohyeon-Kim' on 11/21/24."


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
    // created by Siwon
    string subjectName;
    string professor;
    unordered_map<string, double> studentGrades; // 학생 ID와 점수 매핑: gpt가 시도하는 건데, 정확히 이해는 못했습니다 ㅠ
    string gradingSystem;
    
    // created by Dohyeon
    string classname; // -> subjectName;
    int credit; // 학점
    int capacity; // 수강가능한 인원(max, limit)
    int enrolled; // 수강중인 인원
    string grade_system; // -> gradingSystem;

public:
    //created by Siwon
    // 생성자
    Subject(const string& subjectName, const string& professor, const string& gradingSystem)
        : subjectName(subjectName), professor(professor), gradingSystem(gradingSystem) {}

    // 학생: 일단 과목에 대한 성적 입력을 위해 만든 건데, 학생 클래스에 나중에 합쳐질 것 같습니다.
    void addStudent(const string& studentId, double grade = 0.0) {
        studentGrades[studentId] = grade;
    }

    // 과목 정보 출력: for문 부분은 GPT가 제안해준 겁니다.
    //!! from Subject
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

    // !! 강의 과목 조회; 과목명 반환: 이후에 과목 조회할때 필요함-> 교수가 강의중인 과목만 반환하도록 수정 필요
    string getSubjectName() const {
        return subjectName;
    }
    // !! 본인이 강의하는 과목 선택-> 수강 학생 확인(이름, id) 필요
    
    // 학생 점수 맵 반환: 학생 id와 점수를 매칭
    unordered_map<string, double>& getStudentGrades() {
        return studentGrades;
    }
    
    // 평가 제도 별 성적 평가계산식 필요 'calculateGrades'-> Subject 클래스로 종속
    
    
    //created by Dohyeon
    // 생성자
    Subject(string cn, int c, int cap, int e, string g)
        : classname(cn), credit(c), capacity(cap), enrolled(e), grade_system(g) {}

    // 성적 평가 기준 설정하는 함수
    void setEnrolled(int e) {
        enrolled = e;
        grade_system = determineGradeSystem(e);
    }

    // 성적 평가 제도 결정하는 함수
    string determineGradeSystem(int enrolled) {
        if (enrolled >= 15)
            return "일반비율";
        else if (enrolled >= 10)
            return "영어 A";
        else
            return "P/F";
    }

    // 각 멤버 변수 접근자 함수 (getter)
    /*
    string getName() const { return subjectName; }
    int getCredit() const { return credit; }
    int getCapacity() const { return capacity; }
    int getEnrolled() const { return enrolled; }
    string getGradeSystem() const { return grade_system; }
    */
    //! -> subjectName, credit, capacity, enrolled, grade_system,, etc를 반환하는 반환하는 함수''viewGrades()'
    //! -> student, professor, administrator가 함수 'viewGrades()' 사용 할 때, 재정의 필요 (본인 기능에 맞춘 정보만 조회 가능하도록)
    string viewGrades() {
    // int 타입 변수는 반환할 때 타입 변환 필요
    }
};

//created by Dohyeon
// 과목 수정하는 함수
void modifySubject(vector<Subject>& subjects) {
    vector<Subject> originalSubjects = subjects; // 원본 과목 리스트 저장
    int choice, new_enrolled;

    // 과목명 출력
    
    for (int i = 0; i < subjects.size(); i++) {
        cout << i + 1 << ". " << subjects[i].getName() << endl;
    }
    cout << "성적 평가를 지정할 과목을 선택하세요:" << endl;
    cin >> choice;

    // 수강 인원 수정
    cout << "'" << subjects[choice - 1].getName() << "'의 현재 수강 인원을 입력하세요: \n";
    cin >> new_enrolled;

    subjects[choice - 1].setEnrolled(new_enrolled);

    // 수정된 과목 출력
    cout << "\n수정된 내용을 아래와 같이 보여줍니다:\n";
    viewAllSubjects(subjects);

    // 저장 여부 묻기
    while (true) {
        cout << "수정된 내용을 저장하시겠습니까? (Y/N): ";
        char save_data;
        cin >> save_data;

        if (save_data == 'N' || save_data == 'n') {
            subjects = originalSubjects; // 원본 데이터 복원
            cout << "\n수정된 내용이 취소되었습니다. 원래 데이터는 다음과 같습니다:\n";
            break;
        } else if (save_data == 'Y' || save_data == 'y') {
            cout << "\n수정된 내용이 저장되었습니다. 현재 데이터는 다음과 같습니다:\n";
            break;
        } else {
            cout << "Y와 N 둘 중 하나를 입력해주세요" << endl;
        }
    }

    // 결과 출력
    viewAllSubjects(subjects);
}

// 과목 리스트 생성
vector<Subject> initializeSubjects() {
    vector<Subject> subjects;
    subjects.push_back(Subject("광고와 사회", 3, 30, 30, "일반비율"));
    subjects.push_back(Subject("디지털 미디어 전략(영어 A)", 3, 15, 13, "영어 A"));
    subjects.push_back(Subject("Cau세미나(2)", 3, 8, 6, "P/F"));
    return subjects;
}


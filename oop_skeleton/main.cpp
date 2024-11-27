//
//  skeleton.cpp
//  oop_skeleton
//
//  Created by Lousie Nayeong Koh on 11/16/24.
// "this is fourth commit_integrated with 'Dohyeon-Kim' on 11/21/24."


#include "userinfo.h"
#include "subject.h"

void displayGrades(StudentInfo* student, const string& semester) {

    cout << setw(6) << left << "�⵵"
        << setw(6) << left << "�б�"
        << setw(10) << left << "�̼�����"
        << setw(20) << left << "�����"
        << setw(6) << left << "����"
        << setw(6) << left << "����"
        << setw(6) << left << "����" << endl;
    cout << "------------------------------------------------------------" << endl;

    bool found = false;
    for (const auto& grade : student->grades) {
        if (semester == "��ü" || grade.semester == semester) {
            cout << setw(6) << left << grade.year
                << setw(6) << left << grade.semester
                << setw(10) << left << grade.courseType
                << setw(20) << left << grade.courseName
                << setw(6) << left << grade.credits
                << setw(6) << left << grade.grade
                << setw(6) << fixed << setprecision(1) << grade.gradePoint << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "�ش� �б⿡ ������ ������ �����ϴ�." << endl;
    }

    double gpa = student->calculateGPA(semester);
    cout << "------------------------------------------------------------" << endl;
    cout << "�� ���� ���: " << fixed << setprecision(1) << gpa << endl;
}


int main() {

    // 사용자 로그인 정보 로드
    string filename = "./users.txt";
    // !! 학생-> 과목-> 성적, 교수 텍스트 파일 로드 필요
    vector<UserInfo> users = loadUsers(filename);
    if (users.empty()) {
        cerr << "사용자 정보가 없습니다. 프로그램을 종료합니다." << endl;
        return 1;
    }

    cout << "************************************************************" << endl;
    cout << "광고홍보학과 성적 관리 시스템" << endl;
    cout << "************************************************************" << endl;

    // ����� �ź� ����
    cout << "로그인을 진행합니다." << endl;
    cout << "1. 학생" << endl;
    cout << "2. 교수" << endl;
    cout << "3. 관리자" << endl;

    int userType; // ����� �ź��� �Է¹��� ����
    cout << "로그인할 계정의 신분을 선택해 번호를 입력하세요. ";
    cin >> userType;

    // ���õ� ����� �źп� �´� ������ ���͸�
    string userTypeStr;
    switch (userType) {
    case 1:
        userTypeStr = "Student";
        break;
    case 2:
        userTypeStr = "Professor";
        break;
    case 3:
        userTypeStr = "Administrator";
        break;
    default:
        cout << "잘못된 선택입니다." << endl;
        return 1;
    }

    // 선택된 신분의 사용자들만 필터링
    vector<UserInfo> filteredUsers;
    for (const auto& user : users) {
        if (user.userType == userTypeStr) {
            filteredUsers.push_back(user);
        }
    }

    if (filteredUsers.empty()) {
        cout << userTypeStr << " 계정이 없습니다." << endl;
        return 1;
    }

    // 로그인 프로세스
    cout << "로그인할 정보를 입력하세요.\nID: ";
    string id, pw;
    cin >> id;
    cout << "PW: ";
    cin >> pw;

    UserInfo* loggedInUser = authenticateUser(id, pw, filteredUsers);

    if (loggedInUser) {
        cout << "로그인 성공: " << loggedInUser->name << " (" << loggedInUser->userType << ")\n";
        // 로그인 성공 후 추가 작업(예: 사용자 메뉴 표시 등)
        
        // ����� �α��� �� �л����� Ȯ�ε� ���
        StudentInfo* student = new StudentInfo("student1", "student123", "Alice", 1);

        // ���� ������(������ �������� �κ� �ʿ�)
        student->addGrade(Grade("2024", "3-1", "����", "������ ��ȸ", 3, "B+", 3.5));
        student->addGrade(Grade("2024", "3-1", "����", "������ �̵�� ����(����A)", 3, "A+", 4.5));
        student->addGrade(Grade("2024", "3-1", "��������", "cau���̳�(2)", 3, "P", -1.0)); // Pass ������ ���� ��� ����

        cout << "��ȸ�� �б⸦ �����ϼ���." << endl;
        cout << "1. 1-1" << endl;
        cout << "2. 1-2" << endl;
        cout << "3. 2-1" << endl;
        cout << "4. 2-2" << endl;
        cout << "5. 3-1" << endl;
        cout << "6. ��ü" << endl;

        int choice;
        cin >> choice;

        string semester;
        switch (choice) {
        case 1: semester = "1-1"; break;
        case 2: semester = "1-2"; break;
        case 3: semester = "2-1"; break;
        case 4: semester = "2-2"; break;
        case 5: semester = "3-1"; break;
        case 6: semester = "��ü"; break;
        default:
            cout << "�߸��� �����Դϴ�." << endl;
            return 1;
        }
        cout << "'" << semester << "'�б��� ������ ��ȸ�մϴ�." << endl;
        displayGrades(student, semester);

        delete student;
    }
    else {
        cout << "로그인 실패: ID 또는 비밀번호가 잘못되었습니다.\n";
    }

    
    // created by Dohyeon
    vector<Subject> subjects = initializeSubjects();
    cout << "========== 성적 관리 프로그램 ==========\n";
    viewAllSubjects(subjects);
    modifySubject(subjects);
    cout << "\n프로그램이 종료되었습니다.\n";

    return 0;
    
}


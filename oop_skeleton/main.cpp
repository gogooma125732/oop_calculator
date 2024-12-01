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

void viewAllSubjects(const vector<Subject>& subjects) {
    cout << "*************************************************************************************\n";
    cout << setw(25) << "과목명" << setw(15) << "학점" << setw(20) << "수강 정원"
         << setw(20) << "수강 인원" << setw(20) << "성적 평가" << endl;
    cout << "------------------------------------------------------------------------------------\n";

    for (int i = 0; i < subjects.size(); i++) {
        cout << setw(30) << subjects[i].getName()
             << setw(10) << subjects[i].getCredit()
             << setw(13) << subjects[i].getCapacity()
             << setw(15) << subjects[i].getEnrolled()
             << setw(23) << subjects[i].getGradeSystem() << endl;
    }
    cout << "*************************************************************************************\n";
}

void displaySubject(const string& filename, const string& id); // 과목 클래스 과목 정보 조회 기능
void reviseScore(const string& filename, const string& id_p, vector<vector<string>>& data, const vector<string>& columnNames); // 교수 클래스 성적 수정 기능

void displaySubject(const string& filename, const string& id) { // 사용자 id를 받아 과목 출력

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;
    bool found = false;
    vector<string> columnNames;

    // 첫 번째 행 한줄 에서 컬럼명 저장
    if (getline(file, line)) {
        stringstream ss(line);
        string value;

        // 쉼표로 데이터 분리 -> 컬럼명을 columnNames 벡터에 저장
        while (getline(ss, value, ',')) {
            columnNames.push_back(value);
        }
    }

    vector<vector<string>> data; // 데이터를 저장할 벡터

    // 나머지 데이터 행 처리
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> values;

        // 쉼표로 데이터 분리 -> 데이터를 values 벡터에 저장
        while (getline(ss, value, ',')) {
            values.push_back(value);
        }

        // ID의 확인 (입력받은 id가 5번째, 6번째 컬럼의 교수와 학생 아이디에 있는지 확인)
        if (!values.empty() && ((values[4] == id) || (values[5] == id))) {
            found = true;

            // ID에 따라 출력할 열 결정
            if (id[0] == '1') { // 학생의 경우, id가 1로 시작함
                cout << values[1] << "    " << values[2] << "    "; // 과목명과 교수명
                // 6~15열 출력 id열 제외
                for (int i = 6; i < values.size(); i++) {
                    cout << values[i] << "    ";
                }
                cout << endl;
            }
            else if (id[0] == '2') { // 교수의 경우, id가 2로 시작함
                cout << values[1] << "    " << values[3] << "    "; // 과목명과 학생명
                // 6~15열 출력 학생 id 포함
                for (int i = 5; i < values.size(); i++) {
                    cout << values[i] << "    ";
                }
                cout << endl;
            }
            else if (id[0] == '3'){ // 관리자 id: 특정 id를 정해야 할 거 같아요
                for (const auto& val : values) {
                    cout << val << " "; // 모든 열 출력
                }
                cout << endl;
            }
        }
        data.push_back(values); // 읽은 데이터를 저장
    }

    if (!found) {
        cout << "해당 ID에 대한 기록이 없습니다: " << id << endl;
    }

    file.close();
    reviseScore(filename, id, data, columnNames); // 임의로 호출, 교수일 경우만 호출할 수 있도록 해야 함
}

void reviseScore(const string& filename, const string& id_p, vector<vector<string>>& data, const vector<string>& columnNames) {
    string id_s;
    cout << "수정할 학생의 ID를 입력하세요: ";
    cin >> id_s;

    bool found = false;

    // 학생 ID의 확인 및 성적 수정
    for (auto& values : data) {
        if (!values.empty() && values[5] == id_s) { // 학생 ID 확인
            found = true;

            // 학생 정보 출력
            cout << "현재 정보: " << endl;
            cout << "과목: " << values[1] << ", 학생명: " << values[3] << ", 학기: " << values[6] << endl;

            // 성적 수정 요청
            cout << "중간 점수를 입력하세요 (현재: " << values[9] << "): ";
            string midtermScore;
            cin >> midtermScore;

            cout << "기말 점수를 입력하세요 (현재: " << values[10] << "): ";
            string finalScore;
            cin >> finalScore;

            cout << "과제 점수를 입력하세요 (현재: " << values[11] << "): ";
            string assignmentScore;
            cin >> assignmentScore;

            cout << "출결 점수를 입력하세요 (현재: " << values[12] << "): ";
            string attendanceScore;
            cin >> attendanceScore;

            // 점수 수정
            values[9] = midtermScore; // 중간 점수 수정
            values[10] = finalScore;   // 기말 점수 수정
            values[11] = assignmentScore; // 과제 점수 수정
            values[12] = attendanceScore; // 출결 점수 수정

            cout << "성적이 수정되었습니다." << endl;
            break; // 수정 후 반복 종료
        }
    }

    if (!found) {
        cout << "해당 ID에 대한 기록이 없습니다: " << id_s << endl;
        return;
    }

    // 수정된 데이터를 파일에 다시 저장
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    // 컬럼명 출력
    for (const auto& col : columnNames) {
        outFile << col << ",";
    }
    outFile << endl;

    // 수정된 데이터 저장
    for (const auto& values : data) {
        for (const auto& val : values) {
            outFile << val << ",";
        }
        outFile << endl;
    }

    outFile.close();
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
    
    string filename_s = "./Subject_Info.csv";
    string id;

    cout << "ID를 입력하세요 (예: 20001 또는 10001): ";
    cin >> id;

    displaySubject(filename_s, id);
    
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


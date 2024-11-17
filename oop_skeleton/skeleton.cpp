//
//  skeleton.cpp
//  oop_skeleton
//
//  Created by Lousie Nayeong Koh on 11/16/24.
//

#include "userinfo.h"


int main() {
    
    // 사용자 정보 로드
    string filename = "./users.txt";
    vector<UserInfo> users = loadUsers(filename);
    if (users.empty()) {
        cerr << "사용자 정보가 없습니다. 프로그램을 종료합니다." << endl;
        return 1;
    }
    
    cout << "************************************************************" << endl;
    cout << "광고홍보학과 성적 관리 시스템" << endl;
    cout << "************************************************************" << endl;
    
    // 사용자 신분 선택
    cout << "로그인을 진행합니다." << endl;
    cout << "1. 학생" << endl;
    cout << "2. 교수" << endl;
    cout << "3. 관리자" << endl;
    
    int userType; // 사용자 신분을 입력받을 변수
    cout << "로그인할 계정의 신분을 선택해 번호를 입력하세요. ";
    cin >> userType;
    
    // 선택된 사용자 신분에 맞는 정보만 필터링
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
    cout << "로그인 정보를 입력하세요.\nID: ";
    string id, pw;
    cin >> id;
    cout << "PW: ";
    cin >> pw;
    
    UserInfo* loggedInUser = authenticateUser(id, pw, filteredUsers);
    
    if (loggedInUser) {
        cout << "로그인 성공: " << loggedInUser->name << " (" << loggedInUser->userType << ")\n";
        // 로그인 성공 후 추가 작업 (예: 사용자 메뉴 표시 등)
    } else {
        cout << "로그인 실패: ID 또는 비밀번호가 잘못되었습니다.\n";
    }
    
    return 0;
}

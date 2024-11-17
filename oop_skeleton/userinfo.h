//
//  userinfo.h
//  oop_skeleton
//
//  Created by Louise Nayeong Koh on 11/17/24.
//

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
            users.push_back({name, id, pw, userType});
        } else {
            cerr << "잘못된 데이터 형식: " << line << endl;
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


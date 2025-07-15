#include "UserInfo.hpp"
#include <iostream>
using namespace std;
int main() {
    UserManager um;
    while(true) {
        string command;
        cin >> command;
        if( command == "adduser" ) {
            string type, name, parent;
            int id;
            cin >> type >> name >> id >> parent;
            if( type == "rongguo" ) {
                bool status = um.addUser(UserInfo(name, id), parent, "rongguo");
                if( status ) {
                    cout << "success" << endl;
                } else {
                    cout << "failed" << endl;
                }
            } else if( type == "ningguo" ) {
                bool status = um.addUser(UserInfo(name, id), parent, "ningguo");
                if( status ) {
                    cout << "success" << endl;
                } else {
                    cout << "failed" << endl;
                }
            }
        } else if( command == "print1" ) {
            string type;
            int target;
            cin >> type >> target;
            if( type == "rongguo" ) {
                cout << um.RongGuoMansion::printMagicNumber(target) << endl;
            } else if( type == "ningguo" ) {
                cout << um.NingGuoMansion::printMagicNumber(target) << endl;
            }
        } else if( command == "print2" ) {
            string type;
            cin >> type;
            if( type == "rongguo" ) {
                cout << um.RongGuoMansion::printMagicNumber() << endl;
            } else if( type == "ningguo" ) {
                cout << um.NingGuoMansion::printMagicNumber() << endl;
            }
        } else if( command == "lca" ) {
            string name1, name2;
            cin >> name1 >> name2;
            cout << um.NingGuoMansion::printLCA(name1, name2) << endl;
        }
    }

    return 0;
}


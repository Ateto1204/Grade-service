#include <iostream>
using namespace std;

bool add(double& course, double& score_sum, double& point_sum) {

    int score, point;

    cin >> score >> point;
    if(score == -1 && point == -1) return false;

    course += 1;
    score_sum += score * point;
    point_sum += point;

    return true;
}

signed main() {

    double score_sum, score, point_sum, point, course;
    score_sum = point_sum = course = 0;
    string cmd;

    cout << "~Final Grade Cal~" << endl;
    cout << endl;

    cout << "This's a program calculating final grade, " << endl;
    cout << "the following is the operation commend." << endl;
    cout << endl;

    cout << "===========================================================\n";
    cout << "Commend explanation: " << endl;
    cout << "[add (score) (point)] to add new element." << endl;
    cout << "[add.] to keep enter [(score) (point)] until enter [-1 -1]." << endl;
    cout << "[del (score) (point)] to delete existed element." << endl;
    cout << "[status] to look for calculation status." << endl;
    cout << "[end] to stop program." << endl;
    cout << "===========================================================\n";
    cout << endl;

    cout << "Enter cmd: ";
    while(cin >> cmd) {

        if(cmd == "end") break;

        if(cmd == "add") {
            add(course, score_sum, point_sum);

        } else if(cmd == "del") {

            cin >> score >> point;
            course -= 1;
            score_sum -= score * point;
            point_sum -= point;

        } else if(cmd == "status") {

            cout << "===========================================================\n";
            cout << "course amount: " << course << endl;
            cout << "totle point: " << point_sum << endl;
            cout << "avg: " << score_sum / point_sum << endl;
            cout << "===========================================================\n";

        } else if(cmd == "add.") {

            cout << "Keep entering your score and point until enter [-1 -1]: " << endl;
            while(add(course, score_sum, point_sum));
            cout << "Stop keeping entering." << endl;

        } else {

            cout << "cmd not existed..." << endl;

        }

        cout << "Enter cmd: ";
    }

    cout << "program finished." << endl;

    return 0;
}

#include <iostream>
#include <sstream>
#include <limits>
using namespace std;


struct Node {

    double score, point;
    struct Node *next;

};


bool calResult(const int course, const double score_sum, const double point_sum) {

    if(course > 0) {

        cout << "course amount: " << course << endl;
        cout << "total point: " << point_sum << endl;

        double avg;
        if(point_sum == 0) avg = 0;
        else avg = score_sum / point_sum;

        cout << "avg: " << avg << endl;

        return true;

    }

    return false;
}


bool travel_node(struct Node *head) {

    struct Node *ptr = head->next;
    bool isEmpty = true;


    while(ptr) {

        if(isEmpty) {
            cout << "-> Current grade list: " << endl;
        }
        isEmpty = false;

        cout << ptr->score << ' ' << ptr->point << endl;
        ptr = ptr->next;

    }

    return isEmpty;

}


void add_node(struct Node *head, const double score, const double point) {

    struct Node *cur = new Node;
    cur->score = score;
    cur->point = point;
    cur->next = NULL;

    if(head->next) {

        struct Node *pre = head->next;
        cur->next = pre;

    }

    head->next = cur;

}


bool del_node(struct Node *head, const double score, const double point) {

    struct Node *ptr, *pre;
    ptr = head->next;
    pre = head;

    while(ptr) {

        if(ptr->score == score && ptr->point == point) {

            pre->next = ptr->next;
            return true;
        }

        pre = ptr;
        ptr = ptr->next;
    }

    return false;

}


bool input(double &score, double &point, stringstream &ss) {

    string input;
    bool first = true;

    do {
        if(first) first = false;
        else {
            cout << "-> Invalid input, enter the score and point again" << endl;
            cout << "<Enter again> ";
        }

        getline(cin, input);

        if(input == "q") return false;

        ss.clear(), ss.str("");
        ss << input;

    } while(!(ss >> score >> point));

    return true;
}



void program_init(struct Node *head, double &score_sum, double &point_sum, int &course) {

    head->score = -1;
    head->point = -1;
    head->next = NULL;

    score_sum = point_sum = course = 0;

}



signed main() {

    struct Node *head = new Node;

    stringstream input_ss;
    string cmd_tmp, cmd, tmp;

    double score_sum, score, point_sum, point;
    int course;



    program_init(head, score_sum, point_sum, course);

    cout << "~Final Grade Cal~" << endl;
    cout << endl;

    cout << "This's a program calculating final grade, " << endl;
    cout << "the following is the operation commend." << endl;
    cout << endl;

    cout << "===========================================================\n";

    cout << endl;
    cout << "Commend explanation: " << endl;

    cout << endl;
    cout << "[add (score) (point)] to add new element." << endl;
    cout << "[add.] to keep enter [(score) (point)] until enter [-1 -1]." << endl;
    cout << "[del (score) (point)] to delete existed element." << endl;
    cout << "[status] to check current grade." << endl;
    cout << "[look] to check grade list." << endl;
    cout << "[end] to stop program." << endl;

    cout << endl;
//    cout << "p.s. score->分數; point->學分" << endl;
    cout << "===========================================================\n";
    cout << endl;

    cout << "<Enter cmd> ";
    while(getline(cin, cmd_tmp)) {

        if(cmd_tmp == "end") break;

        input_ss.clear(), input_ss.str("");

        for(int i=0; i < cmd_tmp.size(); i++) {

            if(cmd_tmp[i] >= 'A' && cmd_tmp[i] <= 'Z') cmd_tmp[i] += 'a' - 'A';
        }

        input_ss << cmd_tmp;

        if(input_ss >> cmd) {

            if(cmd == "add." || cmd_tmp == "add .") { // feature adding continuosly

                cout << "-> Keep entering your score and point until enter 'q': " << endl;
                while(input(score, point, input_ss)) {

                    if(score >= 0 && point >= 0 && score <= 100) {

                        add_node(head, score, point);

                        course += 1;
                        score_sum += score * point;
                        point_sum += point;

                    } else if(score > 100) {

                        cout << "-> The score can not higher than 100." << endl;
                    } else  {

                        cout << "-> You can not enter negative score or point." << endl;
                    }

                }
                cout << "-> Stop keeping entering." << endl;

            } else if(cmd == "add") {

                if(!(input_ss >> score >> point) || score < 0 || point < 0 || score > 100) {

                    do {

                        cout << "-> Add fail" << endl;
                        cout << "<Enter new score and point> ";
                        if(!input(score, point, input_ss)) {

                            cout << "-> Quit the command" << endl;
                            break;
                        }

                    } while(score < 0 || point < 0 || score > 100);
                }

                add_node(head, score, point);

                course += 1;
                score_sum += score * point;
                point_sum += point;

            } else if(cmd == "status") {

                if(!calResult(course, score_sum, point_sum)) {

                    cout << "-> No any grade to display" << endl;
                }

            } else if(cmd == "del") {

                if(!(input_ss >> score >> point)) {

                    cout << "-> Delete fail" << endl;
                    cout << "<Enter new score and point> ";

                    if(!input(score, point, input_ss)) {

                        cout << "-> Quit the command" << endl;
                        continue;
                    }

                }

                if(del_node(head, score, point)) {

                    cout << "-> Delete data success" << endl;

                    course -= 1;
                    score_sum -= score * point;
                    point_sum -= point;

                } else {

                    cout << "-> Data not existed" << endl;
                }

            } else if(cmd == "look") {

                if(travel_node(head)) {
                    cout << "-> Grade list was empty" << endl;
                }

            } else {

                cout << "-> Command does not existed" << endl;
            }
        }

        cout << "<Enter cmd> ";
    }

    cout << "-> Program finished" << endl;

    if(!calResult(course, score_sum, point_sum)) {

        cout << "-> No any grade to display" << endl;
    }

    system("pause");

    return 0;
}

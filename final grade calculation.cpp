#include <iostream>
#include <limits>
using namespace std;


struct Node {

    double score, point;
    struct Node *next;

};

void travel_node(struct Node *head) {

    struct Node *ptr = head->next;

    cout << "===========================================================\n";
    while(ptr) {

        cout << ptr->score << ' ' << ptr->point << endl;
        ptr = ptr->next;

    }
    cout << "===========================================================\n";
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

void input(double &score, double &point) {

    while(!(cin >> score >> point)) {
        cerr << "-> invalid input format" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool add(int &course, double &score_sum, double &point_sum, struct Node *head) {

    double score, point;

    input(score, point);
    if(score == -1 && point == -1) return false;

    add_node(head, score, point);

    course += 1;
    score_sum += score * point;
    point_sum += point;

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
    double score_sum, score, point_sum, point;
    int course;
    string cmd;

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
    cout << "p.s. score->分數; point->學分數" << endl;
    cout << "===========================================================\n";
    cout << endl;

    cout << "<Enter cmd> ";
    while(cin >> cmd) {

        if(cmd == "end") break;

        if(cmd == "add") { // feature adding

            add(course, score_sum, point_sum, head);

        } else if(cmd == "del") { // feature deleting

            input(score, point);

            if( del_node(head, score, point) ) {

                cout << "-> delete success." << endl;

                course -= 1;
                score_sum -= score * point;
                point_sum -= point;

            } else {

                cout << "-> data not existed." << endl;
            }

        } else if(cmd == "status") { // feature seeing grade result

            cout << "===========================================================\n";
            cout << "course amount: " << course << endl;
            cout << "totle point: " << point_sum << endl;
            cout << "avg: " << score_sum / point_sum << endl;
            cout << "===========================================================\n";

        } else if(cmd == "add.") { // feature adding continuosly

            cout << "Keep entering your score and point until enter [-1 -1]: " << endl;
            while(add(course, score_sum, point_sum, head));
            cout << "Stop keeping entering." << endl;

        } else if(cmd == "look") { // feature traveling

            travel_node(head);
        } else {

            cout << "cmd not existed..." << endl;
        }

        cout << "<Enter cmd> ";
    }

    cout << "program finished." << endl;

    system("pause");

    return 0;
}

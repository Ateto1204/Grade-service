/*
*
* @author Ateto
*/

#include <iostream>
#include <sstream>
#include <limits>


class Grade {

private:

    struct ListNode {

    double score, point;
    struct ListNode *next;

    };

    struct ListNode *head;
    int course;
    int pointSum;
    double scoreSum;

    Grade() {
        head = new ListNode();

        head->score = -1;
        head->point = -1;
        head->next = nullptr;

        course = 0;
        scoreSum = 0;
        pointSum = 0;
    }

public:

    static Grade& getGradeInstance() {
        static Grade grade;
        return grade;
    }

    bool travelNode() {

        struct ListNode *ptr = head->next;
        bool isEmpty = true;


        while(ptr) {

            if(isEmpty) {
                std::cout << "-> Current grade list: " << std::endl;
            }
            isEmpty = false;

            std::cout << ptr->score << ' ' << ptr->point << std::endl;
            ptr = ptr->next;

        }

        return isEmpty;

    }

    bool getAvg() {

        if(course > 0) {

            std::cout << "course amount: " << course << std::endl;
            std::cout << "total point: " << pointSum << std::endl;

            double avg;
            if(pointSum == 0) avg = 0;
            else avg = scoreSum / pointSum;

            std::cout << "avg: " << avg << std::endl;

            return true;

        }

        return false;
    }

    void addNode(const double score, const double point) {

        struct ListNode* node = new ListNode;
        node->score = score;
        node->point = point;
        node->next = NULL;

        struct ListNode* dummy = head;
        while(dummy->next != NULL) {
            dummy = dummy->next;
        }

        dummy->next = node;

    }

    bool delNode(const double score, const double point) {

        struct ListNode* dummy = head;

        while(dummy->next != NULL) {

            if(dummy->next->score == score && dummy->next->point == point) {
                dummy->next = dummy->next->next;
                return true;
            }

            dummy = dummy->next;
        }

        return false;

    }

    void modifyCourse(int val) {
        course += val;

    }

    void modifyScore(double val) {
        scoreSum += val;

    }

    void modifyPoint(int val) {
        pointSum += val;
    }

};

void initIntro() {

    using namespace std;
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
    cout << "[add.] to keep enter [(score) (point)] until enter 'q'." << endl;
    cout << "[del (score) (point)] to delete existed element." << endl;
    cout << "[cal] to check current grade." << endl;
    cout << "[log] to check grade list." << endl;
    cout << "[end] to stop program." << endl;

    cout << endl;
    cout << "p.s. score->分數; point->學分" << endl;
    cout << "===========================================================\n";
    cout << endl;
}


bool input(double &score, int &point, std::stringstream &ss) {

    std::string input;
    bool first = true;

    do {
        if(first) first = false;
        else {
            std::cout << "-> Invalid input, enter the score and point again" << std::endl;
            std::cout << "<Enter again> ";
        }

        getline(std::cin, input);

        if(input == "q") return false;

        ss.clear(), ss.str("");
        ss << input;

    } while(!(ss >> score >> point));

    return true;
}


signed main() {

    Grade& grade = Grade::getGradeInstance();

    std::stringstream input_ss;
    std::string cmd_tmp, cmd, tmp;

    double score;
    int point;

    initIntro();

    std::cout << "<Enter cmd> ";
    while(getline(std::cin, cmd_tmp)) {

        if(cmd_tmp == "end") break;

        input_ss.clear(), input_ss.str("");

        for(int i=0; i < cmd_tmp.size(); i++) {

            if(cmd_tmp[i] >= 'A' && cmd_tmp[i] <= 'Z') cmd_tmp[i] += 'a' - 'A';
        }

        input_ss << cmd_tmp;

        if(input_ss >> cmd) {

            if(cmd == "add." || cmd_tmp == "add .") { // feature adding continuosly

                std::cout << "-> Keep entering your score and point until enter 'q': " << std::endl;
                while(input(score, point, input_ss)) {

                    if(score >= 0 && point >= 0 && score <= 100) {

                        grade.addNode(score, point);

                        grade.modifyCourse(1);
                        grade.modifyScore(score * point);
                        grade.modifyPoint(point);

                    } else if(score > 100) {

                        std::cout << "-> The score can not higher than 100." << std::endl;
                    } else  {

                        std::cout << "-> You can not enter negative score or point." << std::endl;
                    }

                }
                std::cout << "-> Stop keeping entering." << std::endl;

            } else if(cmd == "add") {

                if(!(input_ss >> score >> point) || score < 0 || point < 0 || score > 100) {

                    do {

                        std::cout << "-> Add fail" << std::endl;
                        std::cout << "<Enter new score and point> ";
                        if(!input(score, point, input_ss)) {

                            std::cout << "-> Quit the command" << std::endl;
                            break;
                        }

                    } while(score < 0 || point < 0 || score > 100);
                }

                grade.addNode(score, point);

                grade.modifyCourse(1);
                grade.modifyScore(score * point);
                grade.modifyPoint(point);

            } else if(cmd == "cal") {

                if( !grade.getAvg() ) {

                    std::cout << "-> No any grade to display" << std::endl;
                }

            } else if(cmd == "del") {

                if(!(input_ss >> score >> point)) {

                    std::cout << "-> Delete fail" << std::endl;
                    std::cout << "<Enter new score and point> ";

                    if(!input(score, point, input_ss)) {

                        std::cout << "-> Quit the command" << std::endl;
                        continue;
                    }

                }

                if( grade.delNode(score, point) ) {

                    std::cout << "-> Delete data success" << std::endl;

                    grade.modifyCourse(-1);
                    grade.modifyScore( -score * point);
                    grade.modifyPoint( -point);

                } else {

                    std::cout << "-> Data not existed" << std::endl;
                }

            } else if(cmd == "log") {

                if( grade.travelNode() ) {
                    std::cout << "-> Grade list was empty" << std::endl;

                }

            } else {

                std::cout << "-> Command does not existed" << std::endl;
            }
        }

        std::cout << "<Enter cmd> ";
    }

    std::cout << "-> Program finished" << std::endl;


    if( !grade.getAvg() ) {
        std::cout << "-> No any grade to display" << std::endl;

    }

    system("pause");

    return 0;
}

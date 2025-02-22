#include <iostream>
using namespace std;

class Mentor;

class Student {
    private:
        int studentID;
        string studentName;
        int studentAge;
        string sportInterests[50];
        int sportInterestCount;
        Mentor* mentorAssigned; 
    public:
        Student(int id, string name, int age) : studentID(id), studentName(name), studentAge(age), sportInterestCount(0), mentorAssigned(nullptr) {}

        void registerForMentorship(Mentor* m){
            mentorAssigned = m;
        }

        void viewMentorDetails();

        void updateSportInterests(string s){
            sportInterests[sportInterestCount] = s;
            sportInterestCount++;
        }

        string getStudentName() {
            return studentName;
        }
};

class Mentor {
    private:
        string mentorID;
        string mentorName;
        string sportExpertise[50];
        int maxLearners;
        int learnerCount;
        Student* assignedLearners[50]; 
    public:
        Mentor(string id, string name, string expertise, int maxL) : mentorID(id), mentorName(name), maxLearners(maxL), learnerCount(0) {
            sportExpertise[0] = expertise;
        }

        void assignLearner(Student* s){
            if (learnerCount < maxLearners){
                assignedLearners[learnerCount] = s;
                learnerCount++;
                s->registerForMentorship(this);
            } else {
                cout << "Max Learners Assigned" << endl;
            }
        }

        void removeLearner(Student* s) {
            for (int i = 0; i < learnerCount; i++){
                if (assignedLearners[i] == s){
                    for (int j = i; j < learnerCount - 1; j++){
                        assignedLearners[j] = assignedLearners[j+1];
                    }
                    learnerCount--;
                    s->registerForMentorship(nullptr);
                    break;
                }
            }
        }

        void viewLearners(){
            cout << "---- Assigned Learners ----" << endl;
            for (int i = 0; i < learnerCount; i++){
                cout << "Learner " << i + 1 << ": " << assignedLearners[i]->getStudentName() << endl;
            }
        }

        void provideGuidance(){
            cout << "Guidance Provided" << endl;
        }

        string getMentorName() {
            return mentorName;
        }
};

void Student::viewMentorDetails() {
    if (mentorAssigned) {
        cout << "Mentor Assigned: " << mentorAssigned->getMentorName() << endl;
    } else {
        cout << "No Mentor Assigned" << endl;
    }
}

class Sports {
    private:
        int sportID;
        string sportName;
        string sportDescription;
        string requiredSkills[50];
        int requiredSkillCount;
    public:
        void addSkill(string s){
            if (requiredSkillCount < 50){
                requiredSkills[requiredSkillCount] = s;
                requiredSkillCount++;
            }
            else {
                cout << "Max Skill assigned" << endl;
            }
        }

        void removeSkill(string s){
            for (int i = 0; i < requiredSkillCount; i++){
                if (requiredSkills[i] == s){
                    for (int j = i; j < requiredSkillCount - 1; j++){
                        requiredSkills[j] = requiredSkills[j+1];
                    }
                    requiredSkillCount--;
                    break;
                }
            }
        }
};

class Skill {
    private:
        int skillID;
        string skillName;
        string skillDescription;
    public:
        void showSkillDetails(){
            cout << "Skill Name: " << skillName << endl;
            cout << "Skill Description: " << skillDescription << endl;
        }

        void updateSkillDescription(string newDescription){
            skillDescription = newDescription;
        }
};

int main(){
    Mentor mentor("M001", "Ali", "Tennis", 3);
    Student student1(1, "Saad", 20);
    Student student2(2, "Ahmed", 21);
    Student student3(3, "Sara", 22);
    Student student4(4, "Zara", 23);

    mentor.assignLearner(&student1);
    mentor.assignLearner(&student2);
    mentor.assignLearner(&student3);

    mentor.assignLearner(&student4); // Should print "Max Learners Assigned"
    mentor.viewLearners();

    mentor.removeLearner(&student2);
    mentor.viewLearners();

    mentor.assignLearner(&student4); // Should now assign Zara
    mentor.viewLearners();

    student1.viewMentorDetails(); // Should print mentor details

    return 0;
}


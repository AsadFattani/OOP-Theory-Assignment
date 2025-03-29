#include <iostream>
using namespace std;

unsigned long Hasher(const string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = (hash * 33) + c;
    }
    return hash;
}

class User {
    protected:
        string name;
        int ID;
        string permissions[3];
        int permissionCount;
        string email;
        unsigned long hashed_password;
    
    public:
        User(string name, int ID, string email, string password) 
            : name(name), ID(ID), email(email), permissionCount(0) {
            hashed_password = Hasher(password);
        }

        bool authenticate(const string& inputPassword) {
            return Hasher(inputPassword) == hashed_password;
        }

        virtual void display() {
            cout << "Name: " << name << endl;
            cout << "ID: " << ID << endl;
            cout << "Email: " << email << endl;
            cout << "Permissions: ";
            for (int i = 0; i < permissionCount; ++i) {
                cout << permissions[i] << (i < permissionCount - 1 ? ", " : "");
            }
            cout << endl;
        }

        bool accessLab(const string& labName) {
            for (int i = 0; i < permissionCount; ++i) {
                if (permissions[i] == labName) {
                    return true;
                }
            }
            return false;
        }

        virtual void performAction(const string& action) {
            if (action == "display") {
                display();
            } else if (action == "access lab") {
                string labName;
                cout << "Enter lab name: ";
                cin >> labName;
                if (accessLab(labName)) {
                    cout << "Access granted to lab: " << labName << endl;
                } else {
                    cout << "Access denied to lab: " << labName << endl;
                }
            } else {
                cout << "Invalid action for User." << endl;
            }
        }
};

class Student : public User {
    protected:
        int assignments[10] = {0};
        int assignmentCount = 0;

    public:
        Student(string name, int ID, string email, string password) 
            : User(name, ID, email, password) {
            permissions[permissionCount++] = "submit assignments";
        }

        void assignAssignment() {
            if (assignmentCount < 10) {
                assignments[assignmentCount++] = 0;
                cout << "Assignment " << assignmentCount << " assigned." << endl;
            } else {
                cout << "Maximum assignment limit reached." << endl;
            }
        }

        void submitAssignment(int assignmentIndex) {
            if (assignmentIndex >= 0 && assignmentIndex < assignmentCount) {
                assignments[assignmentIndex] = 1;
                cout << "Assignment " << (assignmentIndex + 1) << " submitted." << endl;
            } else {
                cout << "Invalid assignment index." << endl;
            }
        }

        void display() {
            cout << "Student Details:" << endl;
            User::display();
            cout << "Assignments: ";
            for (int i = 0; i < assignmentCount; i++) {
                cout << "Assignment " << (i + 1) << ": " 
                     << (assignments[i] == 1 ? "Submitted" : "Not Submitted") 
                     << (i < assignmentCount - 1 ? ", " : "");
            }
            cout << endl;
        }

        void performAction(const string& action) override {
            if (action == "assign assignment") {
                assignAssignment();
            } else if (action == "submit assignment") {
                int index;
                cout << "Enter assignment index: ";
                cin >> index;
                submitAssignment(index - 1);
            } else {
                User::performAction(action);
            }
        }
};

class TA : public Student {
    protected:
        string Students[10];
        int studentCount = 0;
        string projects[2];
        int projectCount = 0;

    public:
        TA(string name, int ID, string email, string password) 
            : Student(name, ID, email, password) {
            permissions[permissionCount++] = "view projects";
            permissions[permissionCount++] = "manage students";
        }

        void assignStudent(const string& studentName) {
            if (studentCount < 10) {
                Students[studentCount++] = studentName;
                cout << "Student " << studentName << " assigned to TA." << endl;
            } else {
                cout << "Cannot assign more students. Maximum limit of 10 reached." << endl;
            }
        }

        void startProject(const string& projectName) {
            if (projectCount < 2) {
                projects[projectCount++] = projectName;
                cout << "Project " << projectName << " started." << endl;
            } else {
                cout << "Cannot start a new project. Maximum limit of 2 reached." << endl;
            }
        }

        void viewProjects() {
            cout << "Current Projects: ";
            for (int i = 0; i < projectCount; ++i) {
                cout << projects[i] << (i < projectCount - 1 ? ", " : "");
            }
            cout << endl;
        }

        void display() {
            cout << "TA Details:" << endl;
            Student::display();
            cout << "Assigned Students: ";
            for (int i = 0; i < studentCount; ++i) {
                cout << Students[i] << (i < studentCount - 1 ? ", " : "");
            }
            cout << endl;
            viewProjects();
        }

        void performAction(const string& action) override {
            if (action == "assign student") {
                string studentName;
                cout << "Enter student name: ";
                cin >> studentName;
                assignStudent(studentName);
            } else if (action == "start project") {
                string projectName;
                cout << "Enter project name: ";
                cin >> projectName;
                startProject(projectName);
            } else if (action == "view projects") {
                viewProjects();
            } else {
                Student::performAction(action);
            }
        }
};

class Professor : public User {
    public:
        Professor(string name, int ID, string email, string password) 
            : User(name, ID, email, password) {
            permissions[permissionCount++] = "assign projects";
            permissions[permissionCount++] = "full lab access";
        }

        void assignProjectToTA(TA& ta, const string& projectName) {
            if (ta.accessLab("view projects")) {
                ta.startProject(projectName);
            } else {
                cout << "TA does not have permission to work on projects." << endl;
            }
        }

        void display() {
            cout << "Professor Details:" << endl;
            User::display();
        }

        void performAction(const string& action) override {
            if (action == "assign project to TA") {
                string projectName;
                cout << "Enter project name: ";
                cin >> projectName;
                TA* ta = nullptr; // Assume TA object is available or passed in some way
                // Example: ta = someTAObject;
                if (ta) {
                    assignProjectToTA(*ta, projectName);
                } else {
                    cout << "No TA available to assign the project." << endl;
                }
            } else {
                User::performAction(action);
            }
        }
};

void authenticateAndPerformAction(User* user, const string& action) {
    user->performAction(action);
}

int main() {
    Student student("Tyson", 101, "tyson@example.com", "password123");
    TA ta("Bodhi", 102, "bodhi@example.com", "password456");
    Professor professor("Dwight", 103, "dwight@example.com", "password789");

    cout << "\nTesting Student actions:" << endl;
    authenticateAndPerformAction(&student, "display");
    authenticateAndPerformAction(&student, "assign assignment");
    authenticateAndPerformAction(&student, "submit assignment");

    cout << "\nTesting TA actions:" << endl;
    authenticateAndPerformAction(&ta, "display");
    authenticateAndPerformAction(&ta, "assign student");
    authenticateAndPerformAction(&ta, "start project");
    authenticateAndPerformAction(&ta, "view projects");

    cout << "\nTesting Professor actions:" << endl;
    authenticateAndPerformAction(&professor, "display");
    authenticateAndPerformAction(&professor, "assign project to TA");

    cout << "\nTesting lab access:" << endl;
    authenticateAndPerformAction(&student, "access lab");
    authenticateAndPerformAction(&ta, "access lab");
    authenticateAndPerformAction(&professor, "access lab");

    return 0;
}











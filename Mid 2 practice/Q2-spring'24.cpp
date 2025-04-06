#include <iostream>
using namespace std;

class Employee {
    protected:
        string name;
        int empID;
        int salary;

    public:
        Employee(string name, int empID, int salary) :
         name(name), empID(empID), salary(salary) {}
};

class Analyst : virtual public Employee {
    protected:
        string specialization;
        bool isCertified;

    public:
        Analyst(string name, int empID, int salary, string spec, bool isCertified) :
         Employee(name, empID, salary), isCertified(isCertified) {
            while (spec != "Network" && spec != "Incident Response" && spec != "Threat Intelligence") {
                cout << "Invalid specialization. Enter again: ";
                cin >> spec;
            }
            specialization = spec;
        }

        void HasCertification() {
            if (isCertified) {
                int numberOfCertifications;
                cout << "Enter the number of certifications: ";
                cin >> numberOfCertifications;

                if (numberOfCertifications > 0) {
                    string certifications[10];
                    cout << "Enter the certification names: ";
                    for (int i = 0; i < numberOfCertifications && i < 10; i++) {
                        cin >> certifications[i];
                    }
                    cout << "Certifications:" << endl;
                    for (int i = 0; i < numberOfCertifications && i < 10; i++) {
                        cout << certifications[i] << endl;
                    }
                } else {
                    cout << "Not Certified" << endl;
                }
            } else {
                cout << "Not Certified" << endl;
            }
        }
};

class Engineer : virtual public Employee {
    protected:
        bool isExpert;
        bool isAssigned;
        string* list;
        int projectCount;

    public:
        Engineer(string name, int empID, int salary, bool isExpert) :
         Employee(name, empID, salary), isExpert(isExpert), isAssigned(false), projectCount(1) {
            list = new string[1];
            list[0] = "Project 1";
        }

        ~Engineer() {
            delete[] list;
        }

        bool AssignProject(string project) {
            if (isExpert) {
                isAssigned = true;
                cout << "Project assigned: " << project << endl;
                return true;
            } else {
                isAssigned = false;
                cout << "Engineer is not an expert. Project cannot be assigned." << endl;
                return false;
            }
        }

        void AddProjects() {
            if (isAssigned) {
                string newProject;
                cout << "Enter the project name to add: ";
                cin >> newProject;

                string* temp = new string[projectCount + 1];
                for (int i = 0; i < projectCount; i++) {
                    temp[i] = list[i];
                }
                temp[projectCount] = newProject;
                delete[] list;
                list = temp;
                projectCount++;

                cout << "Project added: " << newProject << endl;
            } else {
                cout << "No projects to add." << endl;
            }
        }
};

class LeadProfessional : public Analyst, public Engineer {
    public:
        LeadProfessional(string name, int empID, int salary, string spec, bool isCertified, bool isExpert) :
         Employee(name, empID, salary), Analyst(name, empID, salary, spec, isCertified), Engineer(name, empID, salary, isExpert) {}

        void show() {
            cout << "Name: " << name << endl;
            cout << "Employee ID: " << empID << endl;
            cout << "Salary: " << salary << endl;
            cout << "Specialization: " << specialization << endl;
            cout << "Is Certified: " << (isCertified ? "Yes" : "No") << endl;
            if (isCertified) {
                HasCertification();
            }
            cout << "Is Expert: " << (isExpert ? "Yes" : "No") << endl;
            cout << "Assigned Projects: ";
            for (int i = 0; i < projectCount; i++) {
                cout << list[i] << (i < projectCount - 1 ? ", " : "");
            }
            cout << endl;
        }
};






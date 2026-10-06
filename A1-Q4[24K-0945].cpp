#include <iostream>
using namespace std;

class Student {
    private:
        string name, stop;
        int id;
        bool feesPaid, present;

    public:
        Student() {
            cout << "Enter the Student's Name: ";
            cin >> name;
            cout << "Enter the Student's ID: ";
            cin >> id;
            cout << "Has the student paid their fees? (1 for Yes, 0 for No): ";
            cin >> feesPaid;
            cout << "Enter their assigned stop: ";
            cin >> stop;
            present = false; // Default attendance to false
        }

        ~Student() {
            cout << "Student record for " << name << " (ID: " << id << ") has been deleted." << endl;
        }

        void displayDetails() {
            cout << "Name: " << endl;
			cout << name << "\nID: " << endl;
			cout << id << endl;
			cout << "\nFees Paid: ";
            if (feesPaid) {
                cout << "Yes" << endl;
            } 
			else {
                cout << "No" << endl;
            }
            cout << "Stop: " << stop << "\nAttendance: ";
            if (present) {
                cout << "Present" << endl;
            } 
			else {
                cout << "Absent" << endl;
            }
        }

        void payFees() {
            feesPaid = true;
            cout << name << " has paid their semester fees." << endl;
        }

        void markAttendance() {
            if (feesPaid) {
                present = true;
                cout << name << " has tapped the card and their attendance has been marked." << endl;
            } 
			else {
                cout << name << " cannot mark their attendance as their fees is not yet paid." << endl;
            }
        }

        int getID() {
            return id;
        }
    };

    class TransportSystem {
    private:
        Student* students[10];
        int studentCount;

    public:
        TransportSystem() : studentCount(0) {}

        ~TransportSystem() {
            for (int i = 0; i < studentCount; i++) {
                delete students[i];
            }
            cout << "Transport system records have been cleared." << endl;
        }

        void registerStudent() {
            if (studentCount < 10) {
                students[studentCount++] = new Student();
            } 
			else {
                cout << "Maximum student limit has been reached." << endl;
            }
        }

        void displayStudents() {
            for (int i = 0; i < studentCount; i++) {
                students[i]->displayDetails();
            }
        }

        void processPayment() {
            int id;
            cout << "Enter the Student ID to process payment: ";
            cin >> id;
            for (int i = 0; i < studentCount; i++) {
                if (id == students[i]->getID()) {
                    students[i]->payFees();
                    return;
                }
            }
            cout << "Student ID is not found." << endl;
        }

        void recordAttendance() {
            int id;
            cout << "Enter the Student ID to mark attendance: ";
            cin >> id;
            for (int i = 0; i < studentCount; i++) {
                if (id == students[i]->getID()) {
                    students[i]->markAttendance();
                    return;
                }
            }
            cout << "Student Id is not found." << endl;
        }
    };

int main() {
    TransportSystem system;
    int choice;
    while (true) {
        cout << "\n1.Register Student \n2.Display Students \n3.Pay Fees \n4.Mark Attendance \n5.Exit \nChoose an option: ";
	    cin >> choice;
        switch (choice) {
        case 1:
            system.registerStudent();
            break;
        case 2:
            system.displayStudents();
            break;
        case 3:
            system.processPayment();
            break;
        case 4:
            system.recordAttendance();
            break;
        case 5:
            cout << "Exiting system..." << endl;
            return 0;
        default:
            cout << "Invalid choice, try again!" << endl;
        }
    }
     
	return 0;
}
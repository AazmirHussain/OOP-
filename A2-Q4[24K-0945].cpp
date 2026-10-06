#include <iostream>
#include <string>
using namespace std;
const int MAX_PERMISSIONS = 5, MAX_ASSIGNMENTS = 10, MAX_STUDENTS = 10, MAX_PROJECTS = 2;

int calculateHash(const string& password){
    int hash = 5381;
    for (char c : password){
        hash = hash * 33 + c;
    }
    return hash;
}

class User{
protected:
    string name, id, email, permissions[MAX_PERMISSIONS];
    int permissionCount, hashedPassword;
public:
    User(string n, string i, string p[], int pc, string e, string pass): name(n), id(i), permissionCount(pc), email(e){
        for (int i = 0; i < pc; i++) {
            permissions[i] = p[i];
        }
        hashedPassword = calculateHash(pass);
    }
    ~User(){
        cout << "Destructor for User base class has been run" << endl;
    }

    bool authenticate(string pass) {return calculateHash(pass) == hashedPassword;}
    virtual void display(){
        cout << "Name: " << name << endl << "ID: " << id << endl << "Email: " << email << endl << endl;
        cout << "Permissions: " << endl;
        for (int i = 0; i < permissionCount; i++){
            cout << permissions[i] << " ";
        }
        cout << endl;
    }

    bool hasPermission(string action){
        for (int i = 0; i < permissionCount; i++){
            if (permissions[i] == action){
                return true;
            }
        else{
            return false;
        }
    }
}

    void accessLab(){
        if (hasPermission("full_lab_access")){
            cout << name << " has full access to the lab" << endl;
        }
        else if (hasPermission("manage_students")){
            cout << name << " has TA-level access to the lab" << endl;
        }
        else{
            cout << name << " has student-level access to the lab" << endl;
        }
    }
};

class Student: public User{
protected:
    int assignments[MAX_ASSIGNMENTS], Count;
public:
    Student(string n, string i, string p[], int pc, string e, string pass) : User(n, i, p, pc, e, pass){
        Count = MAX_ASSIGNMENTS;
        for (int i = 0; i < Count; i++){
            assignments[i] = 0;
        }
    }
    ~Student(){
        cout << "Destructor for Student derived class has been called" << endl;
    }

    void display() override{
        User::display();
        cout << "Assignments: ";
        for (int i = 0; i < Count; i++){
            cout << assignments[i] << " ";
        }
        cout << endl;
    }

    void submitAssignment(int index){
        if (index >= 0 && index < Count) {
            assignments[index] = 1;
            cout << name << " submitted assignment " << index << endl;
        }
    }
};

class TA: public Student{
protected:
    string students[MAX_STUDENTS], projects[MAX_PROJECTS];
    int studentCount, projectCount;
public:
    TA(string n, string i, string p[], int pc, string e, string pass) : Student(n, i, p, pc, e, pass){
        studentCount = 0;
        projectCount = 0;
    }
    ~TA(){
        cout << "Destructor for TA Derived class has been run" << endl;
    }

    void display() override{
        User::display();
        cout << "Students managed: ";
        for (int i = 0; i < studentCount; i++){
            cout << students[i] << " ";
        }
        cout << endl;

        cout << "Projects: " << endl;
        for (int i = 0; i < projectCount; i++){
            cout << projects[i] << " ";
        }
        cout << endl;
    }

    void addStudent(string studentId){
        if (studentCount < MAX_STUDENTS){
            students[studentCount++] = studentId;
            cout << "Added student " << studentId << " to TA " << name << endl;
        }
        else{
            cout << "Cannot add more students to TA " << name << endl;
        }
    }

    void addProject(string projectName){
        if (projectCount < MAX_PROJECTS){
            projects[projectCount++] = projectName;
            cout << "Added project " << projectName << " to TA " << name << endl;
        }
        else{
            cout << "Cannot add more projects to TA " << name << endl;
        }
    }
};

class Professor: public User{
public:
    Professor(string n, string i, string p[], int pc, string e, string pass) : User(n, i, p, pc, e, pass){}
    ~Professor(){
        cout << "Destructor for Professor named derived class is called" << endl;
    }

    void display() override{
        User::display();
        cout << "Professor has full lab access" << endl;
    }
    void assignProject(TA& ta, string projectName){ta.addProject(projectName);}
};

void authenticateAndPerformAction(User* user, string action){
    if (action == "submit_assignment" && user->hasPermission("submit_assignment")){
        Student* student = dynamic_cast<Student*>(user);
        if (student){
            student->submitAssignment(0);
        }
    }

    else if (action == "view_projects" && user->hasPermission("view_projects")){
        cout << "Viewing projects" << endl;
    }
    else if (action == "manage_students" && user->hasPermission("manage_students")){
        TA* ta = dynamic_cast<TA*>(user);
        if (ta) {
            ta->addStudent("STU001");
        }
    }
    else if (action == "assign_projects" && user->hasPermission("assign_projects")){
        cout << "Assigning projects" << endl;
    }
    else if (action == "full_lab_access" && user->hasPermission("full_lab_access")){
        user->accessLab();
    }

    else{cout << "Action not permitted for this user" << endl;}
}

int main(){
    string studentPerms[] = {"submit_assignment"};
    Student student("John Doe", "STU001", studentPerms, 1, "john@uni.edu", "password123");
    string taPerms[] = {"view_projects", "manage_students"};
    string profPerms[] = {"assign_projects", "full_lab_access"};


    TA ta("Jane Smith", "TA001", taPerms, 2, "jane@uni.edu", "ta123");
    Professor prof("Dr. Brown", "PROF001", profPerms, 2, "brown@uni.edu", "prof123");

    cout << "Student Info:" << endl;
    student.display();
    cout << endl << "TA Info:" << endl;
    ta.display();
    cout << endl << "Professor Info:" << endl;
    prof.display();

    cout << endl << "Authenticating users:" << endl;
    if (student.authenticate("password123")){
        cout << "Student authenticated successfully" << endl;
    }
    if (ta.authenticate("ta123")){
        cout << "TA authenticated successfully" << endl;
    }
    if (prof.authenticate("prof123")){
        cout << "Professor authenticated successfully" << endl;
    }

    cout << endl << "Testing permissions:" << endl;
    authenticateAndPerformAction(&student, "submit_assignment");
    authenticateAndPerformAction(&ta, "manage_students");
    authenticateAndPerformAction(&prof, "full_lab_access");

    cout << endl << "Testing project assignment:" << endl;
    prof.assignProject(ta, "AI Research");

    return 0;
}
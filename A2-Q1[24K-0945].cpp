#include <iostream>
using namespace std;

class Person{
protected:
    string name;
    int id;
public:
    Person(string name, int id) : name(name), id(id){}
    virtual void displayDetails() = 0;

    void setid(int i){id = i;}
    void setname(string nam){name = nam;}
    string getname(){return name;}
    int getID(){return id;}

    virtual ~Person(){
        cout << "Destructor for Person class has been activated" << endl;
    }
};

class TransportUser: public Person{
protected:
    bool feesPaid;
public:
    TransportUser(string name, int id) : Person(name, id), feesPaid(false){}
    virtual void payFees() = 0;

    ~TransportUser(){
        cout << "Destructor has been activated for Transporter User class" << endl;
    }
};

class Student: public TransportUser{
private:
    string stop;
    bool present;
public:
    Student(string name, int id, string stop) : TransportUser(name, id), stop(stop), present(false){}

    void displayDetails() override{
        cout << "Name: " << name <<  endl << "ID: " << id << endl << "Stop: " << stop << endl;
        cout << "Fees Paid (Status): " << (feesPaid ? "Yes" : "No") << endl << "Attendance: " << (present ? "Present" : "Absent") << endl;
    }

    void payFees() override{ 
        if (feesPaid = true){
            cout << name << " has paid their semester fees." << endl; 
        }
        else{
            cout << name << "has not paid their semester fees." << endl;
        }
    }

    void markAttendance(){ 
        if (feesPaid){ 
            present = true; 
            cout << name << " has scanned their card to mark their attendance." << endl;
        } 
        else{
            cout << name << "'s attendance marking failed. As fees is not yet paid." << endl;
        }
    }

    ~Student(){
        cout << "Destructor for the Student class has been activated" << endl;
    }
};

class Teacher: public TransportUser{
public:
    Teacher(string name, int id): TransportUser(name, id){}

    void displayDetails() override{
        cout << "Name: " << name << endl << "ID: " << id << endl << "Fees Paid (Status): " << (feesPaid ? "Yes" : "No") << endl;
    }

    void payFees() override{ 
        if(feesPaid = true){
            cout << name << " has paid their monthly fees." << endl; 
        }
    }
    ~Teacher(){
        cout << "Destructor for the Teacher class has been activated" << endl;
    }
};

class TransportRoute{
private:
    string routeName;
public:
    TransportRoute(string route) : routeName(route){}
    ~TransportRoute(){
        cout << "Transport route base class destructor has been called" << endl;
    }

    bool operator==(const TransportRoute &other){ 
        return routeName == other.routeName; 
    }

    void setroutename(string r){routeName = r;}
    string getroute(){return routeName;}

    void displayRoute(){ 
        cout << "Route: " << routeName << endl; 
    }
};

class TransportSystem{
private:
    TransportUser* members[10];
    int memberCount;
public:
    TransportSystem() : memberCount(0){}
    ~TransportSystem() { 
        for (int i = 0; i < memberCount; i++){
            delete members[i];
        }
        cout << "Transport system records have been cleared." << endl;
    }

    void registerStudent(string name, int id, string stop){ 
        if (memberCount < 10){
            members[memberCount++] = new Student(name, id, stop);
        } 
        else{
            cout << "Maximum student limit has been reached." << endl;
        }
    }

    void registerTeacher(string name, int id){ 
        if (memberCount < 10){
            members[memberCount++] = new Teacher(name, id);
        } 
        else{
            cout << "Maximum teacher limit has been reached." << endl;
        }
    }

    void displayMembers(){ 
        for (int i = 0; i < memberCount; i++){
            members[i]->displayDetails();
        }
    }
};

int main(){
    TransportSystem system;
    system.registerStudent("Alice", 101, "Stop A");
    system.registerTeacher("Mr. Smith", 201);
    system.displayMembers();
    
    TransportRoute route1("Route 1"), route2("Route 2");
    if (route1 == route2){
        cout << "Routes are the same." << endl;
    }
    else{
        cout << "Routes are different." << endl;
    }
    
    return 0;
}
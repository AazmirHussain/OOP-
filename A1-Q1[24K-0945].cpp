#include <iostream>
using namespace std;

class Mentor; // Frwd Dec
class Student {
private:
    int StudentID, age;
    string name, sportsInterests[3], mentorAssigned;
public:
    Student(int a, int b, string c) {
        StudentID = a;
        age = b;
        name = c;
        mentorAssigned = "NULL";
    }

    ~Student() {
        cout << "Destructor called for Student " << name << endl;
        cout << "Student data has been deleted" << endl;
    }

    void sportsInterestsInput() { 
        cout << "Enter your 3 sports interests: " << endl;
        cout << "Your options are: \n1. Cricket \n2. Football \n3. Tennis \n4. Basketball \n5. Badminton" << endl;
        for (int i = 0; i < 3; i++) {
            cin >> sportsInterests[i];
        }

        string confirmation;
        cout << "Do you wish to update or change the sports interests? (YES/NO)" << endl;
        cin >> confirmation;

        if (confirmation == "YES" || confirmation == "Yes" || confirmation == "yes") {
            updateSportsInterests();
        }
    }

    void updateSportsInterests() {
        cout << "Re-enter the sports you are interested in: " << endl;
        for (int i = 0; i < 3; i++) {
            cin >> sportsInterests[i];
        }
        cout << "Your sports interests have been updated." << endl;
    }

    void registerForMentorship(Mentor &m);
    void viewMentorDetails();
};

class Mentor {
private:
    int mentorID, maxLearners, assignedCount;
    string name, sportsExpertise[3];
    Student* assignedLearners[3];
public:
    Mentor(int id, string n, int maL) {
        mentorID = id;
        name = n;
        maxLearners = maL;
        assignedCount = 0;
    }

    ~Mentor() {
        cout << "Destructor called for Mentor: " << name << endl;
        cout << "Mentor data has been deleted" << endl;
    }

    void addSportsExpertise() {
        cout << "Enter up to 3 sports expertise: " << endl;
        cout << "Your options are: \n1. Cricket \n2. Football \n3. Tennis \n4. Basketball \n5. Badminton" << endl;
        for (int i = 0; i < 3; i++) {
            cin >> sportsExpertise[i];
        }
    }

    bool assignLearner(Student &s) {
        if (assignedCount < maxLearners) {
            assignedLearners[assignedCount] = &s;
            assignedCount++;
            cout << "Student assigned successfully to " << name << endl;
            return true;
        } 
        else {
            cout << "Mentor has reached maximum number of students." << endl;
            cout << "To add another student kindly remove an existing student." << endl;
            return false;
        }
    }

    void removeLearner(Student &s) {
        for (int i = 0; i < assignedCount; i++) {
            if (assignedLearners[i] == &s) {
                for (int j = i; j < assignedCount - 1; j++) {
                    assignedLearners[j] = assignedLearners[j + 1];
                }
                assignedCount--;
                cout << "The student has been removed successfully." << endl;
                cout << "Space for new student has been emptied." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void viewLearners() {
        cout << "Mentor " << name << " has the following students: " << endl;
        for (int i = 0; i < assignedCount; i++) {
            cout << "Student ID: " << assignedLearners[i] << endl;
        }
    }

    void provideGuidance() {
        cout << "Mentor " << name << " is providing guidance to assigned students." << endl;
    }

    string getName() {
        return name;
    }
};

void Student::registerForMentorship(Mentor &m) {
    if (m.assignLearner(*this)) {
        mentorAssigned = m.getName();
    }
}

void Student::viewMentorDetails() {
    if (mentorAssigned == "NULL") {
        cout << "No mentor assigned yet." << endl;
    } 
    else {
        cout << "Mentor assigned: " << mentorAssigned << endl;
    }
}

class Sport {
private:
    int sportID;
    string name, description, requiredSkills[3];
public:
    Sport(int id, string naam, string desc) {
        sportID = id;
        name = naam;
        description = desc;
    }

    ~Sport() {
        cout << "Destructor called for Sport: " << name << endl;
        cout << "Sports Data has been deleted" << endl;
    }

    void addSkill(string skill) {
        for (int i = 0; i < 3; i++) {
            if (requiredSkills[i].empty()) {
                requiredSkills[i] = skill;
                cout << "Skill added successfully!" << endl;
                return;
            }
        }
        cout << "The skill list is full." << endl;
    }

    void removeSkill(string skill) {
        for (int i = 0; i < 3; i++) {
            if (requiredSkills[i] == skill) {
                requiredSkills[i] = "";
                cout << "Skill removed successfully!" << endl;
                return;
            }
        }
        cout << "Skill not found." << endl;
    }

    void displaySportDetails() {
        cout << "Sport: " << name << endl;
        cout << "Description: " << description << endl;
    }
};

class Skill {
private:
    int skillID;
    string skillName, description;
public:
    Skill(int id, string name, string desc) {
        skillID = id;
        skillName = name;
        description = desc;
    }

    ~Skill() {
        cout << "Destructor called for Skill: " << skillName << endl;
        cout << "Skill data has been deleted" << endl;
    }

    void showSkillDetails() {
        cout << "Skill: " << skillName << endl;
        cout << "Description: " << description << endl;
    }

    void updateSkillDescription(string newDescription) {
        description = newDescription;
        cout << "Skill description updated successfully!" << endl;
    }
};

void sportsdetails(){
    cout << endl << "1. Cricket: is a sport played with bat and bowl where the team batting first bats first and then the other ";
    cout << "team bats. The team team with the most score wins" << endl;
    cout << endl << "2. Football: is a sport where 2 teams each with 11 players play to kick the ball in the opposing teams net.";
    cout << " The team which puts the ball most times in the opposing teams net within 90 mins wins the match." << endl;
    cout << endl << "3. Tennis: 2 individuals smash the ball to the other side aand try that the opponent can't do so.";
    cout << " The individual with more points wins the match." << endl;
    cout << endl << "4. Badminton: 2 teams play with the intention of landing the smoll round substance on the other teams side";
    cout << " within a rectangular bounday. The team that does this more often wins the match" << endl;
    cout << endl << "5. Basketball: 2 teams with limited players play a game of netting the ball on the opposite half.";
    cout << " The Team that does this more often within an hour wins the game." << endl << endl;
}

int main() {
    Student s1(101, 20, "Saad");
    Mentor m1(1, "Ali", 3);

    sportsdetails();
    cout << endl;
    m1.addSportsExpertise();
    s1.sportsInterestsInput();
    s1.registerForMentorship(m1);
    cout << endl;
    s1.viewMentorDetails();
    cout << endl;
    m1.viewLearners();
    cout << endl;
    m1.provideGuidance();


    Student s2(200, 18, "Hamza");
    Mentor m2(2, "Qasim", 2);

    sportsdetails();
    cout << endl;
    m2.addSportsExpertise();
    s2.sportsInterestsInput();
    s2.registerForMentorship(m2);
    cout << endl;
    s2.viewMentorDetails();
    cout << endl;
    m2.viewLearners();
    cout << endl;
    m2.provideGuidance();

    return 0;
}
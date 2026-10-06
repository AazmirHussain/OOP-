#include <iostream>
#include <string>
using namespace std;

class Visitor;
class HauntedHouse;

class Ghost{
protected:
    string name, workerName;
    int scareLevel;
public:
    Ghost(const string& name, const string& workerName): name(name), workerName(workerName), 
    scareLevel((name.length() + workerName.length()) % 10 + 1){}

    virtual ~Ghost(){
        cout << "Ghost class Destructor has been called" << endl;
    }

    virtual void haunt(Visitor& visitor) const = 0;

    int getScareLevel() const {return scareLevel;}
    string getName() const {return name;}
    string getWorkerName() const {return workerName;}

    friend ostream& operator<<(ostream& os, const Ghost& ghost){
        os << ghost.name << " (played by " << ghost.workerName << ") - Scare Level: " << ghost.scareLevel;
        return os;
    }

    Ghost* operator+(const Ghost& other){
        string newName = "Combined " + this->name + "-" + other.name;
        string newWorker = this->workerName + " & " + other.workerName;
        int newScare = this->scareLevel + other.scareLevel;
        
        Ghost* result = new Pumpkaboo(newName, newWorker);
        result->scareLevel = newScare;
        return result;
    }
};

class Visitor{
    string name;
    int bravery;
public:
    Visitor(const string& name, int bravery) : name(name), bravery(bravery){}
    ~Visitor(){
        cout << "Visitor class destructor has been called" << endl;
    }

    string getName() const {return name;}
    int getBravery() const {return bravery;}

    string getBraveryLevel() const{
        if (bravery <= 4){ 
            return "Cowardly";
        }
        else if (bravery <= 7){
            return "Average";
        }
        else{
            return "Fearless";
        }
    }

    friend ostream& operator<<(ostream& os, const Visitor& visitor){
        os << visitor.name << " (" << visitor.getBraveryLevel() << ": " << visitor.bravery << ")";
        return os;
    }
};

class Pumpkaboo: public Ghost{
public:
    Pumpkaboo(const string& name, const string& workerName) : Ghost(name, workerName){}
    ~Pumpkaboo(){
        cout << "Pumpkaboo class destructor has been called" << endl;
    }

    void haunt(Visitor& visitor) const override{
        cout << name << " moves objects around " << visitor.getName() << "!" << endl;
    }
};

class Gastly: public Ghost{
public:
    Gastly(const string& name, const string& workerName) : Ghost(name, workerName){}
    ~Gastly(){
        cout << "Gastly class destructor has been called" << endl;
    }

    void haunt(Visitor& visitor) const override{
        cout << name << " SCREAMS loudly at " << visitor.getName() << "!" << endl;
    }
};

class Darkrai: public Ghost{
public:
    Darkrai(const string& name, const string& workerName) : Ghost(name, workerName){}
    ~Darkrai() {
        cout << "Darkrai class destructor has been called" << endl;
    }

    void haunt(Visitor& visitor) const override{
        cout << name << " whispers creepy things to " << visitor.getName() << endl;
    }
};

class Haunter: public Darkrai, public Pumpkaboo{
    int scareLevel;
public:
    Haunter(const string& name, const string& workerName): Darkrai(name, workerName), 
    Pumpkaboo(name, workerName){
       scareLevel = (Darkrai::getScareLevel() + Pumpkaboo::getScareLevel()) / 2;
    }

    ~Haunter(){
        cout << "Haunter class destructor has been called" << endl;
    }

    void haunt(Visitor& visitor) const override{
        Darkrai::haunt(visitor);
        Pumpkaboo::haunt(visitor);
    }

    int getScareLevel() const {return scareLevel;}
    string getName() const {return Darkrai::getName();}
    string getWorkerName() const {return Darkrai::getWorkerName();}

    friend ostream& operator<<(ostream& os, const Haunter& ghost){
        os << ghost.getName() << " (Haunter played by " << ghost.getWorkerName() << ") - Scare Level: " 
        << ghost.getScareLevel();
        return os;
    }
};

class HauntedHouse{
    string name;
    static const int MAX_GHOSTS = 10;
    Ghost* ghosts[MAX_GHOSTS];
    int ghostCount = 0;
public:
    HauntedHouse(const string& name) : name(name){}
    ~HauntedHouse() {
        cout << "Haunted House destructor has been called" << endl;
    }

    void addGhost(Ghost* ghost){
        if (ghostCount < MAX_GHOSTS){
            ghosts[ghostCount++] = ghost;
        }
    }

    void simulateVisit(Visitor visitors[], int visitorCount){
        cout << endl << name << " is now scaring visitors!" << endl;

        for (int i = 0; i < visitorCount; i++){
            cout << endl << visitors[i].getName() << " (" << visitors[i].getBraveryLevel() 
                 << ") enters..." << endl;
            
            for (int j = 0; j < ghostCount; j++){
                cout << "  " << ghosts[j]->getName() << " appears! ";
                
                if (visitors[i].getBravery() - ghosts[j]->getScareLevel() >= 3){
                    cout << visitors[i].getName() << " laughs at " << ghosts[j]->getName() << "!" << endl;
                } 
                else if (ghosts[j]->getScareLevel() - visitors[i].getBravery() >= 3){
                    cout << visitors[i].getName() << " screams and runs away from " << ghosts[j]->getName() << "!" << endl;
                }
                else{
                    cout << visitors[i].getName() << " gets a shaky voice." << endl;
                }
                
                ghosts[j]->haunt(visitors[i]);
            }
        }
    }

    friend ostream& operator<<(ostream& os, const HauntedHouse& house){
        os << "Haunted House: " << house.name << endl << "Ghosts:" << endl;

        for (int i = 0; i < house.ghostCount; i++){
            os << "  " << *(house.ghosts[i]) << endl;
        }

        return os;
    }
};

void visit(Visitor visitors[], int visitorCount, HauntedHouse& house){
    house.simulateVisit(visitors, visitorCount);
}

int main(){
    HauntedHouse house1("Creepy Manor");
    house1.addGhost(new Pumpkaboo("Pesky Pumpkaboo", "Rock"));
    house1.addGhost(new Gastly("Screaming Gastly", "Blue"));
    
    HauntedHouse house2("Shadow Keep");
    house2.addGhost(new Darkrai("Whispering Darkrai", "Ash"));
    house2.addGhost(new Pumpkaboo("Dark Haunter", "Diana"));

    Visitor visitors[] ={
        Visitor("Timid Mendy", 2),
        Visitor("Average Pedri", 5),
        Visitor("Brave Bruno", 9)
    };

    int visitorCount = sizeof(visitors)/sizeof(visitors[0]);
    visit(visitors, visitorCount, house1);
    visit(visitors, visitorCount, house2);

    Ghost* g1 = new Pumpkaboo("Test Ghost 1", "Worker 1");
    Ghost* g2 = new Gastly("Test Ghost 2", "Worker 2");

    Ghost* combined = *g1 + *g2;
    
    cout << endl << "Combined ghost:" << endl << *combined << endl;

    delete combined;
    return 0;
}
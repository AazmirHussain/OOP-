#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Vehicle{
protected:
    string vehicleID;
    double speed, capacity, energyEfficiency;
    static int totalActiveDeliveries;
public:
    Vehicle(string id, double s, double c, double e): vehicleID(id), speed(s), capacity(c), energyEfficiency(e){
        totalActiveDeliveries++;
    }
    virtual ~Vehicle(){
        totalActiveDeliveries--;
        cout << "Vehicle base class Destructor has been called" << endl;
    }

    virtual string calculateRoute(double distance){
        return "Standard route for " + to_string(distance) + " km";
    }

    virtual double estimateDeliveryTime(double distance){return distance / speed;}
    virtual void move(){cout << "Vehicle " << vehicleID << " is moving" << endl;}
    virtual void command(string c){cout << "Vehicle " << vehicleID << " is executing command: " << c << endl;}

    virtual void command(string c, string ID){
        cout << "Vehicle " << vehicleID << " is executing delivery command for package: " << ID << endl;
    }

    virtual void command(string c, string ID, string urge){
        cout << "Vehicle " << vehicleID << " is executing delivery command for package: " << ID 
        << " with urgency: " << urge << endl;
    }

    static int getTotalActiveDeliveries(){return totalActiveDeliveries;}
    string getID() {return vehicleID;}
    double getSpeed() {return speed;}
    double getCapacity() {return capacity;}
    double getEnergyEfficiency() const {return energyEfficiency;}

    friend int compareEfficiency(const Vehicle& v1, const Vehicle& v2);

    bool operator==(const Vehicle& other){
        double Score1 = 0.4 * speed + 0.3 * capacity + 0.3 * energyEfficiency;
        double Score2 = 0.4 * other.speed + 0.3 * other.capacity + 0.3 * other.energyEfficiency;
        return abs(Score1 - Score2) < 0.01;
    }
};
int Vehicle::totalActiveDeliveries = 0;

int compareEfficiency(const Vehicle& v1, const Vehicle& v2){
    double score1 = 0.4 * v1.speed + 0.3 * v1.capacity + 0.3 * v1.energyEfficiency;
    double score2 = 0.4 * v2.speed + 0.3 * v2.capacity + 0.3 * v2.energyEfficiency;
    
    if (score1 > score2){
        return 1;
    }
    else if (score2 > score1){
        return -1;
    }
    else{
        return 0;
    }
}

class RamzanDrone: public Vehicle{
private:
    double altitudeLimit;
public:
    RamzanDrone(string id, double s, double c, double eff, double alt): Vehicle(id, s, c, eff), altitudeLimit(alt){}
    ~RamzanDrone(){
        cout << "Destructor for Ramzan Drone derived class has been called" << endl;
    }

    string calculateRoute(double distance) override{
        return "Aerial route for " + to_string(distance) + " km at altitude up to " + to_string(altitudeLimit) + " meters";
    }
    void move() override{cout << "Drone " << vehicleID << " is flying at optimal altitude" << endl;}

    void command(string c, string ID, string urge) override{
        if (urge == "urgent"){
            cout << "Drone " << vehicleID << " activating HIGH-SPEED mode for Iftar delivery of package: " << ID << endl;
            speed *= 1.5;
        } 
        else {
            Vehicle::command(c, ID, urge);
        }
    }
};

class RamzanTimeShip: public Vehicle{
private:
    string historicalEra;
public:
    RamzanTimeShip(string id, double s, double c, double eff, string era): Vehicle(id, s, c, eff), historicalEra(era){}
    ~RamzanTimeShip(){
        cout << "Destructor for RamzanTimeShip derived class has been called" << endl;
    }

    string calculateRoute(double distance) override{
        return "Temporal route for " + to_string(distance) + " km with historical consistency check for " + historicalEra;
    }

    void move() override{
        cout << "TimeShip " << vehicleID << " verifies historical consistency before jump" << endl;
    }

    void command(string c, string ID, string urge) override{
        if (urge == "urgent"){
            cout << "TimeShip " << vehicleID << " validating historical sensitivity for package: " << ID << endl;
        } 
        else {
            Vehicle::command(c, ID, urge);
        }
    }
};

class RamzanHyperPod: public Vehicle{
private:
    string tunnelNetwork;
public:
    RamzanHyperPod(string id, double s, double c, double eff, string net): Vehicle(id, s, c, eff), tunnelNetwork(net){}
    ~RamzanHyperPod(){
        cout << "Ramzan Hyper Pod derived class destructor has been called" << endl;
    }

    string calculateRoute(double distance) override {
        return "Underground route for " + to_string(distance) + " km via " + tunnelNetwork + " network";
    }

    void move() override{cout << "HyperPod " << vehicleID << " navigates underground tunnels" << endl;}
    void command(string cm, string ID) override {
        cout << "HyperPod " << vehicleID << " preparing bulk delivery of package: " << ID << endl;
    }
};

int main() {
    RamzanDrone drone("DRONE-001", 120, 5, 0.9, 500);
    RamzanTimeShip timeship("TIMESHIP-001", 300, 20, 0.7, "21st Century");
    RamzanHyperPod hyperpod("POD-001", 250, 100, 0.8, "Hyperloop-X");

    Vehicle* vehicles[] = {&drone, &timeship, &hyperpod};
    for (Vehicle* v : vehicles){ // 1
        v->move();
        cout << v->calculateRoute(50) << endl;
        cout << "Estimated delivery time: " << v->estimateDeliveryTime(50) << " hours" << endl;
        cout << endl;
    }

    drone.command("Deliver", "PKG-IFTAR-002", "urgent"); // 2
    timeship.command("Deliver", "PKG-HIST-001", "urgent");
    hyperpod.command("Deliver", "PKG-BULK-005");
    cout << endl;

    int result = compareEfficiency(drone, hyperpod); // 3
    if (result == 1){
        cout << drone.getID() << " is more efficient than " << hyperpod.getID() << endl;
    } 
    else if (result == -1){
        cout << hyperpod.getID() << " is more efficient than " << drone.getID() << endl;
    } 
    else{
        cout << "Both are equally efficient" << endl;
    }

    cout << endl;
    if (drone == hyperpod){ // 4
        cout << drone.getID() << " and " << hyperpod.getID() << " are equally suitable" << endl;
    } 
    else{
        cout << drone.getID() << " and " << hyperpod.getID() << " have different suitability" << endl;
    }

    cout << endl << "Total active deliveries: " << Vehicle::getTotalActiveDeliveries() << endl;
    return 0;
}
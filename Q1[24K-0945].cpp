#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class IdentitynotFound{ //Exception 1
public:
    string message;
    IdentitynotFound(const string& Identity, const string& identifier){
        message = Identity + " with ID " + identifier + " not found";
        cout << message << endl;
    }
};

class NoPayment{ //Exception2
public:
    string message;
    NoPayment(){
        message = "Payment required before booking";
        cout << message << endl;
    }
};

class BookingClosed{ //Exception 3
public:
    string message;
    BookingClosed(){
        message = "Seats Unavailable";
        cout << message << endl;
    }
};

class IDnotFound{ //Exxception 4
public:
    string message;
    IDnotFound(){
        message = "Seat role mismatched";
        cout << message << endl;
    }
};

class AlreadyBooked{ //Exception 5
public:
    string message;
    AlreadyBooked(){
        message = "User already booked a seat this month";
        cout << message << endl;
    }
};

const int BUS = 0, COASTER = 1;
const int FACULTY = 0, STUDENT = 1;
const int LTV = 0, HTV = 1;

class User;
class Driver;
class Route;
class Vehicle;
class Booking;
class Transporter;

class Person{
protected:
    string id, name, contact;
    
public:
    Person(const string& id, const string& n, const string& c): id(id), name(n), contact(c){}
    virtual ~Person(){
        cout << "Person class destructor called" << endl;
    }

    string getId() const {return id;}
    string getName() const {return name;}
    string getContact() const {return contact;}
};

class User : public Person{
private:
    bool hasPaid;
    int role;
    time_t lastBookingDate;
    
public:
    User(const string& id, const string& na, const string& c, int r): Person(id, na, c), role(r), hasPaid(false), lastBookingDate(0){}
    ~User(){
        cout << "Destructor for User class called" << endl;
    }

    void makePayment() {hasPaid = true;}
    bool hasMadePayment() const { return hasPaid;}
    int getRole() const {return role;}
    time_t getLastBookingDate() const {return lastBookingDate;}
    void setLastBookingDate(time_t date) {lastBookingDate = date;}
};

class Driver : public Person{
private:
    int license;
    Vehicle* assignedVehicle;
    
public:
    Driver(const string& id, const string& n, const string& c, int li): Person(id, n, c), license(li), assignedVehicle(nullptr){}
    ~Driver(){
        cout << "Destructor for Driver class called" << endl;
    }

    int getLicense() const{return license;}
    Vehicle* getAssignedVehicle() const {return assignedVehicle;}
    void assignVehicle(Vehicle* vehicle);
    void removeVehicle();
};

class Route{
private:
    string id, start, end;
    float distance, LongDistance;
    bool isLongDistance;
    
public:
    Route(const string& id, const string& s, const string& e, float d, float long_dist = 30.0f): id(id), start(s), end(e), distance(d), LongDistance(long_dist){
        isLongDistance = (distance > LongDistance);
    }
    ~Route(){
        cout << "Destructor for Route class called" << endl;
    }

    string getId() const {return id;}
    string getStartLocation() const {return start;}
    string getEndLocation() const {return end;}
    float getDistance() const {return distance;}
    bool isLongRoute() const {return isLongDistance;}
};

class Seat{
private:
    int number, role;
    bool isBooked;
    User* bookedBy;
    
public:
    Seat(){}
    Seat(int n, int r): number(n), role(r), isBooked(false), bookedBy(nullptr){}
    ~Seat(){
        cout << "Destructor for Seat class called" << endl;
    }

    int getNumber() const {return number;}
    int getRole() const {return role;}
    bool getIsBooked() const {return isBooked;}
    User* getBookedBy() const {return bookedBy;}

    void book(User* user){
        if(isBooked) throw BookingClosed();
        if(user->getRole() != role) throw IDnotFound();
        isBooked = true;
        bookedBy = user;
    }

    void unbook(){
        isBooked = false;
        bookedBy = nullptr;
    }
};

class Vehicle{
protected:
    string id;
    int type, count;
    bool isAC;
    Driver* driver;
    Route* route;
    Transporter* transporter;
    Seat* seats;
    
public:
    Vehicle(const string& id, int t, bool ac, Transporter* transporter, int cap): id(id), type(t), isAC(ac), transporter(transporter), driver(nullptr), route(nullptr), count(cap){
        seats = new Seat[cap];
    }
    virtual ~Vehicle(){
        delete[] seats;
        cout << "Destructor for Vehicle class called" << endl;
    }

    string getId() const {return id;}
    int getType() const {return type;}
    bool isAirConditioned() const {return isAC;}
    Driver* getDriver() const {return driver;}
    Route* getRoute() const {return route;}
    Transporter* getTransporter() const {return transporter;}
    Seat* getSeats() const {return seats;}
    int getCount() const {return count;}

    void assignDriver(Driver* newDriver){
        if(driver) driver->removeVehicle();
        driver = newDriver;
        if(newDriver) newDriver->assignVehicle(this);
    }

    void assignRoute(Route* newRoute){
        route = newRoute;
    }

    virtual void initializeSeats() = 0;
    virtual float calculateFare() const = 0;

    Seat* FindSeat(int role){
        for(int i = 0; i < count; i++){
            if(!seats[i].getIsBooked() && seats[i].getRole() == role){
                return &seats[i];
            }
        }
        return nullptr;
    }
};

class Bus: public Vehicle{
public:
    Bus(const string& id, bool ac, Transporter* transporter): Vehicle(id, BUS, ac, transporter, 52){
        initializeSeats();
    }
    ~Bus(){
        cout << "Destructor for Bus class called" << endl;
    }

    void initializeSeats() override{
        for(int i = 0; i < 52; i++){
            int role = (i < 10) ? FACULTY : STUDENT;
            seats[i] = Seat(i + 1, role);
        }
    }

    float calculateFare() const override{
        float baseFare = 1500.0f;
        if(isAC) baseFare += 2000.0f;
        if(route && route->isLongRoute()) baseFare += 500.0f;
        return baseFare;
    }
};

class Coaster: public Vehicle{
public:
    Coaster(const string& id, bool ac, Transporter* transporter): Vehicle(id, COASTER, ac, transporter, 32){
        initializeSeats();
    }
    ~Coaster(){
        cout << "Destructor for Coaster class called" << endl;
    }

    void initializeSeats() override{
        for(int i = 0; i < 32; i++){
            int role = (i < 5) ? FACULTY : STUDENT;
            seats[i] = Seat(i+1, role);
        }
    }

    float calculateFare() const override{
        float baseFare = 1000.0f;
        if(isAC) baseFare += 2000.0f;
        if(route && route->isLongRoute()) baseFare += 500.0f;
        return baseFare;
    }
};

class Booking{
private:
    string id;
    User* user;
    Vehicle* vehicle;
    Seat* seat;
    
public:
    Booking(const string& id, User* user, Vehicle* vehicle, Seat* seat): id(id), user(user), vehicle(vehicle), seat(seat){}
    ~Booking(){
        cout << "Destructor for Booking class called" << endl;
    }

    string getId() const {return id;}
    User* getUser() const {return user;}
    Vehicle* getVehicle() const {return vehicle;}
    Seat* getSeat() const {return seat;}
};

class Transporter{
private:
    string name;
    Vehicle** vehicles;
    int VehCount, VehCap;
    
public:
    Transporter(const string& n, int cap): name(n), VehCount(0), VehCap(cap){
        vehicles = new Vehicle*[cap];
    }
    ~Transporter(){
        delete[] vehicles;
        cout << "Destructor for Transporter class called" << endl;
    }
    string getName() const {return name;}
    
    void addVehicle(Vehicle* vehicle){
        if(VehCount < VehCap){
            vehicles[VehCount++] = vehicle;
        }
    }

    Vehicle* findVehicle(const string& vehicleId){
        for(int i = 0; i < VehCount; i++){
            if(vehicles[i]->getId() == vehicleId){
                return vehicles[i];
            }
        }
        throw IdentitynotFound("Vehicle", vehicleId);
    }
};

class TransportManager{
private:
    User** users;    
    Driver** drivers;
    Route** routes;
    Booking** bookings;

    int driverCount, driverCapacity, userCount, userCapacity;
    int routeCount, routeCapacity, bookingCount, bookingCapacity;
    
    void expandUsers(){
        userCapacity *= 2;
        User** newUsers = new User*[userCapacity];
        for(int i = 0; i < userCount; i++){
            newUsers[i] = users[i];
        }
        delete[] users;
        users = newUsers;
    }

public:
    Transporter* transporters[2];

    TransportManager(): userCount(0), userCapacity(10), driverCount(0), driverCapacity(10), 
                       routeCount(0), routeCapacity(10), bookingCount(0), bookingCapacity(10){
        users = new User*[userCapacity];
        drivers = new Driver*[driverCapacity];
        routes = new Route*[routeCapacity];
        bookings = new Booking*[bookingCapacity];
        
        transporters[0] = new Transporter("Nadeem Transporter", 50);
        transporters[1] = new Transporter("Zulfiqar Transporter", 50);
    }

    ~TransportManager(){
        for(int i = 0; i < userCount; i++) delete users[i];
        for(int i = 0; i < driverCount; i++) delete drivers[i];
        for(int i = 0; i < routeCount; i++) delete routes[i];
        for(int i = 0; i < bookingCount; i++) delete bookings[i];
        
        delete[] users;
        delete[] drivers;
        delete[] routes;
        delete[] bookings;
        
        delete transporters[0];
        delete transporters[1];
    }

    User* registerUser(const string& id, const string& n, const string& c, int r){
        if(userCount >= userCapacity) expandUsers();
        users[userCount] = new User(id, n, c, r);
        return users[userCount++];
    }

    User* findUser(const string& Id){
        for(int i = 0; i < userCount; i++){
            if(users[i]->getId() == Id){
                return users[i];
            }
        }
        throw IdentitynotFound("User", Id);
    }
};

void Driver::assignVehicle(Vehicle* vehicle){
    assignedVehicle = vehicle;
}

void Driver::removeVehicle(){
    assignedVehicle = nullptr;
}

int main(){
    TransportManager manager;
    
    try {
        User* facultyUser = manager.registerUser("F001", "Dr. Smith", "111222111", FACULTY);
        User* studentUser = manager.registerUser("S001", "Ali Khan", "444333444", STUDENT);
        
        facultyUser->makePayment();
        studentUser->makePayment();
        
        Bus* bus = new Bus("B001", true, manager.transporters[0]);
        manager.transporters[0]->addVehicle(bus);
        Route* route = new Route("R001", "Main Campus", "Gulshan", 35.0f);
        
        bus->assignRoute(route);
        
        Driver* driver = new Driver("D001", "Nadeem Ahmed", "3331234567", HTV);
        bus->assignDriver(driver);
        
        Seat* facultySeat = bus->FindSeat(FACULTY);
        if(facultySeat) {
            facultySeat->book(facultyUser);
            Booking* facultyBooking = new Booking("BK001", facultyUser, bus, facultySeat);
            cout << "Faculty booking successful! Seat: " << facultySeat->getNumber() << endl;
        }
        
        Seat* studentSeat = bus->FindSeat(STUDENT);
        if(studentSeat) {
            studentSeat->book(studentUser);
            Booking* studentBooking = new Booking("BK002", studentUser, bus, studentSeat);
            cout << "Student booking successful! Seat: " << studentSeat->getNumber() << endl;
        }
        
        cout << "Bus fare for faculty: Rs. " << bus->calculateFare() << endl;
        
        Coaster* coaster = new Coaster("C001", false, manager.transporters[1]);
        manager.transporters[1]->addVehicle(coaster);
        
        User* unpaidUser = manager.registerUser("S002", "Sara Ahmed", "5551234567", STUDENT);
        try {
            Seat* testSeat = coaster->FindSeat(STUDENT);
            if(testSeat) {
                testSeat->book(unpaidUser);
            }
        } 
        catch(NoPayment& e){
            cout << "Caught expected payment exception: " << e.message << endl;
        }
        
        try {
            Seat* wrongRoleSeat = bus->FindSeat(FACULTY);
            if(wrongRoleSeat){
                wrongRoleSeat->book(studentUser);  // Should throw IDnotFound exception
            }
        } 
        catch(IDnotFound& e){
            cout << "Caught expected role mismatch: " << e.message << endl;
        }
        
    } 
    catch(exception& e){
        cout << "Unexpected error: " << e.what() << endl;
    }
    
    return 0;
}
#include <iostream>
using namespace std;

class User {
    private:
        int age;
		long long int phone_NO, ID;
        string license;

    public:
            User(int age, int phone, int ID, string type) {
            this->age = age;
            this->ID = ID;
            this->phone_NO = phone;
            this->license = type;
        }

        void update() {
            int disp;
            cout << "What do you wish to update?\n";
            cout << "1. Age\n2. Phone Number\n3. ID\n4. License type\n5. Exit\n";
            cin >> disp;
        
            switch (disp) {
                case 1:
                    cout << "Enter the new age: ";
                    cin >> age;
                    break;
                case 2:
                    cout << "Enter the new Phone Number: ";
                    cin >> phone_NO;
                    break;
                case 3:
                    cout << "Enter the new ID: ";
                    cin >> ID;
                    break;
                case 4:
                    cout << "Enter your license type: ";
                    cin >> license;
                    break;
                case 5:
                    return;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
        }

            string getLicense() { 
                return license; 
            }
            
        ~User(){
        	return;
		}
};

class Vehicle {
    public:
        string model, eligibility;
        double rental_price;

        Vehicle(string model, double price, string eligibility) {
            this->model = model;
            this->rental_price = price;
            this->eligibility = eligibility;
        }

        void display() {
            cout << "Model: " << model << ", Price per day: $" << rental_price << endl; 
                 cout << "Eligibility: " << eligibility << endl;
        }
        
        ~Vehicle(){
        	return;
		}
};

class RentalSystem {
    private:
        Vehicle* vehicles[10];
        int vehicleCount;

    public:
        RentalSystem() : vehicleCount(0) {}

        void addVehicle(string model, double price, string eligibility) {
            if (vehicleCount < 10) {
                vehicles[vehicleCount++] = new Vehicle(model, price, eligibility);
            } 
            else {
                cout << "Vehicle storage is full!" << endl;
            }
        }

        void displayVehicles() {
            cout << "Available Vehicles:\n";
            for (int i = 0; i < vehicleCount; i++) {
                vehicles[i]->display();
                cout << endl;
            }
        }

        void rentVehicle(User &user) {
            string userLicense = user.getLicense(), chosenModel;
            cout << "Enter the model of the vehicle you want to rent: ";
            cin >> chosenModel;

            for (int i = 0; i < vehicleCount; i++) {
                if (vehicles[i]->model == chosenModel) {
                    if (vehicles[i]->eligibility == userLicense || vehicles[i]->eligibility == "All") {
                        cout << "Rental successful! You have rented " << vehicles[i]->model << " for $" << vehicles[i]->rental_price << " per day." << endl;
                        return;
                    } 
                    else {
                        cout << "You are not eligible to rent this vehicle." << endl;
                        return;
                    }
                }
            }

            cout << "Vehicle not found." << endl;
        }
        
        ~RentalSystem(){
        	for(int i = 0; i < vehicleCount; i++){
            	delete vehicles[i];
            }
		}
};

int main() {
    RentalSystem system;
    int age;
	long long int phone, ID;
    string license;

    system.addVehicle("Bus", 350, "Full");
    system.addVehicle("Motorcycle", 100, "Intermediate"); 
    system.addVehicle("Scooter", 80, "Learner");
    system.addVehicle("Tractor", 300, "Full");
    system.addVehicle("Car", 150, "Intermediate");
    system.addVehicle("Mini_Car", 130, "Learner");

    cout << "Registering User..." << endl;
    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter your phone number: ";
    cin >> phone;
    cout << "Enter your ID: ";
    cin >> ID;
    cout << "Enter your license type (Learner, Intermediate, Full): ";
    cin >> license;
    
    User user(age, phone, ID, license);
    
    int choice;
    while (true) {
        cout << "\n1. Update User Details\n2. View Available Vehicles\n3. Rent a Vehicle\n4. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            user.update();
            break;
        case 2:
            system.displayVehicles();
            break;
        case 3:
            system.rentVehicle(user);
            break;
        case 4:
            cout << "Exiting system..." << endl;
            return 0;
        default:
            cout << "Invalid choice, try again!" << endl;
        }
    }
  
    return 0;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Abstraction -> Base class for all vehicles
class Vehicle {
protected:
    string licensePlate;
    string type;
    string brand;
    string owner;
    bool isValet;
public:
    Vehicle(const string& licensePlate, const string& type, const string& brand, const string& owner, bool isValet = false)
        : licensePlate(licensePlate), type(type), brand(brand), owner(owner), isValet(isValet) {}

    // Getter licensePlate
    string getLicensePlate() const {
        return licensePlate;
    }

    // Setter licensePlate
    void setLicensePlate(const string& licensePlate) {
        this->licensePlate = licensePlate;
    }

    // Getter type
    string getType() const {
        return type;
    }

    // Getter brand
    string getBrand() const {
        return brand;
    }

    // Setter brand
    void setBrand(const string& brand) {
        this->brand = brand;
    }

    // Getter owner
    string getOwner() const {
        return owner;
    }

    // Setter owner
    void setOwner(const string& owner) {
        this->owner = owner;
    }

    // Getter isValet
    bool getIsValet() const {
        return isValet;
    }

    // Setter isValet
    void setIsValet(bool isValet) {
        this->isValet = isValet;
    }

    // Deskripsi Kendaraan
    virtual void displayInfo() const {
        cout << "Vehicle Type: " << type << ", Brand: " << brand << ", License Plate: " << licensePlate << ", Owner: " << owner;
        if (isValet) {
            cout << " (Valet Parking)";
        }
        cout << endl;
    }

    virtual ~Vehicle() = default;
};

// Inheritance dari Vehicle -> Car
class Car : public Vehicle {
public:
    Car(const string& licensePlate, const string& brand, const string& owner, bool isValet = false)
        : Vehicle(licensePlate, "Car", brand, owner, isValet) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
    }
};

// Inheritance dari Vehicle -> Bike
class Bike : public Vehicle {
public:
    Bike(const string& licensePlate, const string& brand, const string& owner, bool isValet = false)
        : Vehicle(licensePlate, "Bike", brand, owner, isValet) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
    }
};

// ParkingLot class
class ParkingLot {
private:
    int carCapacity;
    int bikeCapacity;
    int valetCapacity;
    vector<Vehicle*> cars;
    vector<Vehicle*> bikes;
    vector<Vehicle*> valet;

public:
    ParkingLot(int carCapacity, int bikeCapacity, int valetCapacity) 
        : carCapacity(carCapacity), bikeCapacity(bikeCapacity), valetCapacity(valetCapacity) {}

    // Parkir kendaraan
    bool parkVehicle(Vehicle* vehicle, bool isValet) {
        if (isValet) {
            if (valet.size() < valetCapacity) {
                valet.push_back(vehicle);
                return true;
            }
        } else {
            if (vehicle->getType() == "Car") {
                if (cars.size() < carCapacity) {
                    cars.push_back(vehicle);
                    return true;
                }
            } else if (vehicle->getType() == "Bike") {
                if (bikes.size() < bikeCapacity) {
                    bikes.push_back(vehicle);
                    return true;
                }
            }
        }
        return false;
    }

    // Menghapus kendaraan
    bool removeVehicle(const string& licensePlate) {
        for (auto it = cars.begin(); it != cars.end(); ++it) {
            if ((*it)->getLicensePlate() == licensePlate) {
                delete *it;
                cars.erase(it);
                return true;
            }
        }
        for (auto it = bikes.begin(); it != bikes.end(); ++it) {
            if ((*it)->getLicensePlate() == licensePlate) {
                delete *it;
                bikes.erase(it);
                return true;
            }
        }
        for (auto it = valet.begin(); it != valet.end(); ++it) {
            if ((*it)->getLicensePlate() == licensePlate) {
                delete *it; 
                valet.erase(it);
                return true;
            }
        }
        return false;
    }

    // Kendaraan yg terparkir
    void displayParkedVehicles() const {
        cout << "-----------------------------------" << endl;
        cout << "          Parked Cars:" << endl;
        cout << "-----------------------------------" << endl;
        if (cars.empty()) {
            cout << "No cars parked." << endl;
        } else {
            for (const auto& car : cars) {
                car->displayInfo();
            }
        }

        cout << "\n-----------------------------------" << endl;
        cout << "          Parked Bikes:" << endl;
        cout << "-----------------------------------" << endl;
        if (bikes.empty()) {
            cout << "No bikes parked." << endl;
        } else {
            for (const auto& bike : bikes) {
                bike->displayInfo();
            }
        }

        cout << "\n-----------------------------------" << endl;
        cout << "          Valet Parked Vehicles:" << endl;
        cout << "-----------------------------------" << endl;
        if (valet.empty()) {
            cout << "No valet vehicles parked." << endl;
        } else {
            for (const auto& v : valet) {
                v->displayInfo();
            }
        }
    }

    // Kapasitas parkir
    void displayCapacity() const {
        cout << "\n-----------------------------------" << endl;
        cout << "       Parking Lot Capacity" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Car Capacity: " << carCapacity - cars.size() << " out of " << carCapacity << endl;
        cout << "Bike Capacity: " << bikeCapacity - bikes.size() << " out of " << bikeCapacity << endl;
        cout << "Valet Capacity: " << valetCapacity - valet.size() << " out of " << valetCapacity << endl;
    }

    // Destructor to free allocated memory
    ~ParkingLot() {
        for (auto car : cars) {
            delete car;
        }
        for (auto bike : bikes) {
            delete bike;
        }
        for (auto v : valet) {
            delete v;
        }
    }

    // Fitur Tambahan
    // Cari kendaraan berdasarkan plat nomor
    Vehicle* searchVehicle(const string& licensePlate, bool& isValet) const {
        for (const auto& car : cars) {
            if (car->getLicensePlate() == licensePlate) {
                isValet = false;
                return car;
            }
        }
        for (const auto& bike : bikes) {
            if (bike->getLicensePlate() == licensePlate) {
                isValet = false;
                return bike;
            }
        }
        for (const auto& v : valet) {
            if (v->getLicensePlate() == licensePlate) {
                isValet = true;
                return v;
            }
        }
        return nullptr; 
    }

    // Method to calculate parking fee
    double calculateParkingFee(Vehicle* vehicle, bool isValet) const {
        double fee = 0.0;
        cout << "Enter parking duration in hours for vehicle with license plate " << vehicle->getLicensePlate() << ": ";
        int duration;
        cin >> duration;

        if (vehicle->getType() == "Car") {
            fee = 10000; 
            if (duration > 1) {
                fee += 4000 * (duration - 1); 
            }
            if (isValet) {
                fee += 100000; 
            }
        } else if (vehicle->getType() == "Bike") {
            fee = 5000; 
            if (duration > 1) {
                fee += 2000 * (duration - 1); 
            }
            if (isValet) {
                fee += 50000; 
            }
        }
        return fee;
    }

    // Method to update vehicle information
    bool updateVehicle(const string& licensePlate, const string& newLicensePlate, const string& brand, const string& owner) {
        for (auto& car : cars) {
            if (car->getLicensePlate() == licensePlate) {
                car->setLicensePlate(newLicensePlate);
                car->setBrand(brand);
                car->setOwner(owner);
                return true;
            }
        }
        for (auto& bike : bikes) {
            if (bike->getLicensePlate() == licensePlate) {
                bike->setLicensePlate(newLicensePlate);
                bike->setBrand(brand);
                bike->setOwner(owner);
                return true;
            }
        }
        for (auto& v : valet) {
            if (v->getLicensePlate() == licensePlate) {
                v->setLicensePlate(newLicensePlate);
                v->setBrand(brand);
                v->setOwner(owner);
                return true;
            }
        }
        return false;
    }
};

int main() {
    int carCapacity = 50;
    int bikeCapacity = 200;
    int valetCapacity = 30;

    ParkingLot parkingLot(carCapacity, bikeCapacity, valetCapacity);

    while (true) {
        cout << "\n===================================" << endl;
        cout << "           PARKING LOT MENU" << endl;
        cout << "===================================" << endl;
        cout << "1. Park Vehicle" << endl;
        cout << "2. Remove Vehicle" << endl;
        cout << "3. Display All Parked Vehicles" << endl;
        cout << "4. Display Capacity" << endl;
        cout << "5. Search Vehicle" << endl;
        cout << "6. Calculate Parking Fee" << endl;
        cout << "7. Update Vehicle Information" << endl;
        cout << "8. Exit" << endl;
        cout << "===================================" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch(choice) {
            case 1: {
                cout << "Select vehicle type (1 for Car, 2 for Bike): ";
                int typeChoice;
                cin >> typeChoice;

                string type;
                if (typeChoice == 1) {
                    type = "Car";
                } else if (typeChoice == 2) {
                    type = "Bike";
                } else {
                    cout << "Invalid vehicle type!" << endl;
                    continue;
                }

                cout << "Enter license plate: ";
                string licensePlate;
                cin.ignore();
                getline(cin, licensePlate);

                cout << "Enter vehicle brand : ";
                string brand;
                getline(cin, brand);

                cout << "Enter owner name: ";
                string owner;
                getline(cin, owner);

                cout << "\nParking Rates:" << endl;
                cout << "Car - First hour: 10,000 IDR, Additional hour: 4,000 IDR" << endl;
                cout << "Bike - First hour: 5,000 IDR, Additional hour: 2,000 IDR" << endl;

                if (typeChoice == 1) {
                    cout << "Do you want valet parking? (1 for Yes, 2 for No): (Additional valet charge for car: 100,000 IDR): ";
                } else if (typeChoice == 2) {
                    cout << "Do you want valet parking? (1 for Yes, 2 for No): (Additional valet charge for bike: 50,000 IDR): ";
                }

                int valetChoice;
                cin >> valetChoice;
                bool isValet = (valetChoice == 1);

                Vehicle* vehicle;
                if (type == "Car") {
                    vehicle = new Car(licensePlate, brand, owner, isValet);
                } else {
                    vehicle = new Bike(licensePlate, brand, owner, isValet);
                }

                if (parkingLot.parkVehicle(vehicle, isValet)) {
                    cout << "Vehicle parked successfully." << endl;
                } else {
                    cout << "Parking lot is full for " << type << "s." << endl;
                    delete vehicle;
                }
                break;
            }
            case 2: {
                cout << "Enter license plate of vehicle to remove: ";
                cin.ignore();
                string licensePlate;
                getline(cin, licensePlate);

                if (parkingLot.removeVehicle(licensePlate)) {
                    cout << "Vehicle removed successfully." << endl;
                } else {
                    cout << "Vehicle not found." << endl;
                }
                break;
            }
            case 3: {
                parkingLot.displayParkedVehicles();
                break;
            }
            case 4: {
                parkingLot.displayCapacity();
                break;
            }
            case 5: {
                cout << "\n===================================" << endl;
                cout << "         SEARCH VEHICLE" << endl;
                cout << "===================================" << endl;
                cout << "Enter license plate of vehicle to search: ";
                cin.ignore(); 
                string licensePlate;
                getline(cin, licensePlate);

                bool isValet;
                Vehicle* foundVehicle = parkingLot.searchVehicle(licensePlate, isValet);
                if (foundVehicle != nullptr) {
                    cout << "-----------------------------------" << endl;
                    cout << "           VEHICLE FOUND" << endl;
                    cout << "-----------------------------------" << endl;
                    foundVehicle->displayInfo();
                } else {
                    cout << "-----------------------------------" << endl;
                    cout << "         VEHICLE NOT FOUND" << endl;
                    cout << "-----------------------------------" << endl;
                }
                break;
            }
            case 6: {
                cout << "\n===================================" << endl;
                cout << "       CALCULATE PARKING FEE" << endl;
                cout << "===================================" << endl;
                cout << "Enter license plate of vehicle to calculate parking fee: ";
                cin.ignore(); 
                string licensePlate;
                getline(cin, licensePlate);

                bool isValet;
                Vehicle* vehicle = parkingLot.searchVehicle(licensePlate, isValet);
                if (vehicle != nullptr) {
                    double fee = parkingLot.calculateParkingFee(vehicle, isValet);
                    cout << "-----------------------------------" << endl;
                    cout << " PARKING FEE CALCULATED" << endl;
                    cout << "-----------------------------------" << endl;
                    cout << "Parking fee for vehicle with license plate " << licensePlate << " is: " << fee << " IDR" << endl;
                } else {
                    cout << "-----------------------------------" << endl;
                    cout << "         VEHICLE NOT FOUND" << endl;
                    cout << "-----------------------------------" << endl;
                }
                break;
            }
            case 7: {
                cout << "Enter license plate of vehicle to update: ";
                cin.ignore(); 
                string licensePlate;
                getline(cin, licensePlate);

                cout << "Enter new license plate: ";
                string newLicensePlate;
                getline(cin, newLicensePlate);

                cout << "Enter new vehicle brand: ";
                string brand;
                getline(cin, brand);

                cout << "Enter new owner name: ";
                string owner;
                getline(cin, owner);

                if (parkingLot.updateVehicle(licensePlate, newLicensePlate, brand, owner)) {
                    cout << "Vehicle information updated successfully." << endl;
                } else {
                    cout << "Vehicle not found." << endl;
                }
                break;
            }
            case 8: {
                cout << "Exiting the program. Goodbye!" << endl;
                return 0; 
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
    return 0;
}

#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <chrono>

namespace Parking {
    class ParkingSpace {
    public:
        ParkingSpace(int number, bool available) : number(number), available(available) {}
        void leaveCar() { available = true; } 
        int getNumber() const { return number; }
        bool isAvailable() const { return available; }
        void occupy() { available = false; }
        void vacate() { available = true; }
        void park() { available = false; }

    private:
        int number;
        bool available;
    };

    class Ticket {
    public:
        Ticket(const std::string &licensePlate, const std::string &spaceLabel, double ticketAmount)
            : licensePlate(licensePlate), spaceLabel(spaceLabel), ticketAmount(ticketAmount) {
            entryTime = std::chrono::system_clock::now();
        }

        void printInfo() const {
            std::cout << " __________\n";
            std::cout << "|      PARKING TICKET      |\n";
            std::cout << "|__________|\n";
            std::cout << "| Car Number: " << std::setw(10) << licensePlate << "   |\n";
            std::cout << "| Space Label:" << std::setw(10) << spaceLabel << "   |\n";
            std::cout << "| Ticket Amount:" << std::setw(10) << ticketAmount << " |\n";
            printEntryTime();
            std::cout << "|__________|\n";
        }

        std::chrono::time_point<std::chrono::system_clock> getEntryTime() const {
            return entryTime;
        }

    private:
        std::string licensePlate;
        std::string spaceLabel;
        double ticketAmount;
        std::chrono::time_point<std::chrono::system_clock> entryTime;

        void printEntryTime() const {
            auto entryTimePoint = std::chrono::system_clock::to_time_t(entryTime);
            std::cout << "| Entry Time: " << std::put_time(std::localtime(&entryTimePoint), "%Y-%m-%d %H:%M:%S") << " |\n";
        }
    };

    class ParkingLot {
    public:
        ParkingLot(int capacity) : capacity(capacity) {
            for (int i = 1; i <= capacity; i++) {
                spaces.push_back(ParkingSpace(i, true));
            }
        }

        std::string parkCar() {
            int totalSpaces = spaces.size();
            int halfSpaces = totalSpaces / 2;

            // Try to park in the upper basement first
            for (int i = 0; i < halfSpaces; i++) {
                if (spaces[i].isAvailable()) {
                    spaces[i].park();
                    return "UB" + std::to_string(i + 1);
                }
            }

            // If the upper basement is full, try to park in the lower basement
            for (int i = halfSpaces; i < totalSpaces; i++) {
                if (spaces[i].isAvailable()) {
                    spaces[i].park();
                    return "LB" + std::to_string(i - halfSpaces + 1);
                }
            }

            // If both basements are full, return an empty string
            return "";
        }

        bool leaveCar(const std::string& spaceLabel) {
    if (spaceLabel.length() < 3) {
        return false;  // Invalid label
    }

    std::string basement = spaceLabel.substr(0, 2);
    int spaceNumber = std::stoi(spaceLabel.substr(2));

    if (basement == "LB") {
        spaceNumber += spaces.size() / 2;
    }

    if ((basement == "UB" || basement == "LB") && spaceNumber > 0 && spaceNumber <= spaces.size() && !spaces[spaceNumber - 1].isAvailable()) {
        spaces[spaceNumber - 1].leaveCar();  // Call leaveCar on the ParkingSpace
        return true;
    }

    return false; 
}


        void displayParkingStatus() {
            std::cout << "Parking Lot Status:" << std::endl;
            int totalSpaces = spaces.size();
            int halfSpaces = totalSpaces / 2;
            std::cout << "Upper Basement:" << std::endl;
            displayParallelSpaces(0, halfSpaces, "UB");
            std::cout << "Lower Basement:" << std::endl;
            displayParallelSpaces(halfSpaces, totalSpaces, "LB");
        }

        void displayParallelSpaces(int start, int end, const std::string& basementLabel) {
            int range = end - start;
            int rowSize = range / 2;
            for (int i = 0; i < rowSize; i++) {
                displaySpaceStatus(start + i, basementLabel + std::to_string(i + 1));
                std::cout << " | ";
                displaySpaceStatus(start + rowSize + i, basementLabel + std::to_string(rowSize + i + 1));
                std::cout << std::endl;
            }
            // If there is an extra space, display it on a new line
            if (range % 2 != 0) {
                displaySpaceStatus(end - 1, basementLabel + std::to_string(range));
                std::cout << std::endl;
            }
        }

        void displaySpaceStatus(int i, const std::string& label) {
            std::cout << label << ": ";
            if (spaces[i].isAvailable()) {
                std::cout << "[ A ]";  // 'A' for Available
            } else {
                std::cout << "[ O ]";  // 'O' for Occupied
            }
        }

        static ParkingLot createParkingLot(int capacity) {
            return ParkingLot(capacity);
        }

    private:
        int capacity;
        std::vector<ParkingSpace> spaces;
    };
}

class Vehicle {
public:
    Vehicle(const std::string &licensePlate) : licensePlate(licensePlate) {}

    virtual void printInfo() const = 0;

protected:
    std::string licensePlate;
};

class Car : public Vehicle {
public:
    Car(const std::string &licensePlate) : Vehicle(licensePlate) {}

    void printInfo() const override {
        std::cout << "Car with License Plate: " << licensePlate << std::endl;
    }
};

#endif







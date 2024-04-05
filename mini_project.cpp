#include <iostream>
#include "Parking_System.cpp"
#include "Ticketing_System.cpp"

int main() {
    try {

        std::ofstream clearFile("tickets.txt", std::ofstream::out | std::ofstream::trunc);
            clearFile.close();

            
        int capacity;
        std::cout << "Enter the capacity of the parking lot: ";
        std::cin >> capacity;
        Parking::ParkingLot parkingLot = Parking::ParkingLot::createParkingLot(capacity);

        while (true) {
            std::cout << "1. Park a car" << std::endl;
            std::cout << "2. Leave a car" << std::endl;
            std::cout << "3. Display parking status" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::string spaceLabel = parkingLot.parkCar();
                    if (!spaceLabel.empty()) {
                        // Take user input for the license plate
                        std::string licensePlate;

                        std::cout << "Enter the license plate number for the car: ";
                        std::cin >> licensePlate;
                        std::cout << "Car parked successfully in space: " << spaceLabel << std::endl;

                        Parking::TicketManager::generateTicket(licensePlate, spaceLabel, 50.0);
                    } else {
                        std::cout << "Parking lot is full. Cannot park a car." << std::endl;
                    }
                    break;
                }
                case 2: {
                    std::cout << "Enter the space label to leave: ";
                    std::string spaceLabel;
                    std::cin >> spaceLabel;
                    if (parkingLot.leaveCar(spaceLabel)!=true) {
                        std::cout << "Space is either empty or does not exist." << std::endl;
                    } else {
                        std::cout << "Car left the parking lot." << std::endl;

                    }
                    break;
                }
                case 3:
                    parkingLot.displayParkingStatus();
                    break;
                case 4:
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}




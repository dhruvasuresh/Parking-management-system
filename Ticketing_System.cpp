#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Parking_System.cpp"
using namespace std;
namespace Parking {

    class TicketManager {
    public:
        static void generateTicket(const string &licensePlate, const string &spaceLabel, double ticketAmount) {
            Ticket ticket(licensePlate, spaceLabel, ticketAmount);
            ticket.printInfo();

            ofstream outFile("tickets.txt", ios::app);
            if (outFile.is_open()) {
                outFile << "Ticket Information:\n";
                outFile << "License Plate: " << licensePlate << "\n";
                outFile << "Space Label: " << spaceLabel << "\n";
                outFile << "Ticket Amount: " << ticketAmount << "\n";
                saveEntryTime(outFile, ticket);
                outFile << "------------------------\n";
                outFile.close();
                cout << "Ticket information saved to tickets.txt.\n";
            } else {
                cerr << "Unable to open tickets.txt for writing.\n";
            }
        }

    private:
        static void saveEntryTime(ofstream &outFile, const Ticket &ticket) {
            auto entryTimePoint = chrono::system_clock::to_time_t(ticket.getEntryTime());
            outFile << "Entry Time: " << put_time(localtime(&entryTimePoint), "%Y-%m-%d %H:%M:%S") << "\n";
        }
    };
}





#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
using namespace std;
#include <fstream>

class FileLogger {
public:
    static void log(const string &msg) {
        
        ofstream out("log.txt", ios::app);  // append mode

        if (!out) {
            cout << "Error opening log file!\n";
            return;
        }

        out << msg << "\n";

        out.close();
    }
};


struct vehicle {
    int Registration_number;
    string owner_name;
    string vehicle_type;
    int model_year;
     string company; 
};


class vechicleSystem {

private:
    vector<vehicle> vechicles;
    map<int, vehicle> vechicle_map;
    set<string> vechicle_types;
    unordered_map<string, int> company_count;

public:

 
    void register_vechicle() {
        vehicle v;

        cout << "Enter Registration Number: ";
        cin >> v.Registration_number;

        if (vechicle_map.find(v.Registration_number) != vechicle_map.end()) {
            cout << "Vehicle already exists!\n";
            return;
        }

        cout << "Enter Owner Name: ";
        cin >> v.owner_name;

        cout << "Enter Vehicle Type: ";
        cin >> v.vehicle_type;

        cout << "Enter Model Year: ";
        cin >> v.model_year;
        cout << "Enter Company Name: ";
cin >> v.company;

        vechicles.push_back(v);
        vechicle_map[v.Registration_number] = v;
        vechicle_types.insert(v.vehicle_type);
     company_count[v.company] =company_count[v.company] + 1;

        cout << "Vehicle Registered Successfully!\n";
        FileLogger::log("Registered Vehicle: " + to_string(v.Registration_number));

    }

    void search_vehicle() {

        int reg;
        cout << "Enter Registration Number: ";
        cin >> reg;

        auto it = vechicle_map.find(reg);

        if (it != vechicle_map.end()) {
            vehicle v = it->second;

            cout << "\nVehicle Found:\n";
            cout << "Reg No      : " << v.Registration_number << endl;
            cout << "Owner Name  : " << v.owner_name << endl;
            cout << "Type        : " << v.vehicle_type << endl;
            cout << "Model Year  : " << v.model_year << endl;
        }
        else {
            cout << "Vehicle Not Found!\n";
        }
        FileLogger::log("Searched Vehicle: " + to_string(reg));

    }

    void searchByOwner() {
        string owner;
        cout << "Enter Owner Name: ";
        cin >> owner;

        bool found = false;

        for (auto &v : vechicles) {
            if (v.owner_name == owner) {
                cout << "\nVehicle Found:\n";
                cout << "Reg No      : " << v.Registration_number << endl;
                cout << "Owner Name  : " << v.owner_name << endl;
                cout << "Type        : " << v.vehicle_type << endl;
                cout << "Model Year  : " << v.model_year << endl;
                found = true;
            }
        }

        if (!found)
            cout << "No vehicle found for owner: " << owner << endl;
            FileLogger::log("Search by owner: " + owner);

    }


    void update_vehicle_owner() {
        int reg;
        cout << "Enter Registration Number: ";
        cin >> reg;

        auto it = vechicle_map.find(reg);
        if (it == vechicle_map.end()) {
            cout << "Vehicle Not Found!\n";
            return;
        }

        string newOwner;
        cout << "Enter New Owner Name: ";
        cin >> newOwner;

        it->second.owner_name = newOwner;

        for (auto &v : vechicles) {
            if (v.Registration_number == reg) {
                v.owner_name = newOwner;
            }
        }

        cout << "Owner Updated Successfully!\n";
        FileLogger::log("Updated owner of: " + to_string(reg));

    }

    void deleteVehicle() {
        int reg;
        cout << "Enter Registration Number to Delete: ";
        cin >> reg;

        auto it = vechicle_map.find(reg);
        if (it == vechicle_map.end()) {
            cout << "Vehicle Not Found!\n";
            return;
        }

        vehicle v = it->second;
        vechicle_map.erase(reg);

        vechicles.erase(
            remove_if(vechicles.begin(), vechicles.end(),
                [&](auto &x) { return x.Registration_number == reg; }),
            vechicles.end()
        );
         company_count[v.company] = company_count[v.company] -1;
        if (company_count[v.vehicle_type] == 0)
            company_count.erase(v.vehicle_type);

        cout << "Vehicle Deleted Successfully!\n";
        FileLogger::log("Deleted Vehicle: " + to_string(reg));

    }


    void listAllVehicles() {

        if (vechicles.empty()) {
            cout << "No vehicles registered.\n";
            return;
        }

        sort(vechicles.begin(), vechicles.end(),
            [](auto &a, auto &b) {
                return a.model_year < b.model_year;
            });

        cout << "\n----------------------------------------------------------------\n";
        cout << setw(15) << "RegNo"
             << setw(15) << "Owner"
             << setw(15) << "Type"
             << setw(15) << "Year" << "\n";
        cout << "----------------------------------------------------------------\n";

        for (auto &v : vechicles) {
            cout << setw(15) << v.Registration_number
                << setw(15) << v.owner_name
                << setw(15) << v.vehicle_type
                << setw(15) << v.model_year << "\n";
        }
        cout << "----------------------------------------------------------------\n";
        for (auto &v : vechicles) {
    FileLogger::log("RegNo=" + to_string(v.Registration_number) +
                    ", Owner=" + v.owner_name +
                    ", Type=" + v.vehicle_type +
                    ", Company=" + v.company +
                    ", Year=" + to_string(v.model_year));
}

    }
};


int main() {
vechicleSystem vs;
int choice;

while (true) {

    cout << "\n========= VEHICLE MANAGEMENT SYSTEM =========\n";
    cout << "Choice 1: Register Vehicle\n";
    cout << "Choice 2: Search by Registration Number\n";
    cout << "Choice 3: Search by Owner Name\n";
    cout << "Choice 4: Update Owner Name\n";
    cout << "Choice 5: Delete Vehicle\n";
    cout << "Choice 6: List All Vehicles\n";
    cout << "Choice 7: Exit\n";
    cout << "----------------------------------------------\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {

    case 1:
        vs.register_vechicle();
        break;

    case 2:
        vs.search_vehicle();
        break;

    case 3:
        vs.searchByOwner();
        break;

    case 4:
        vs.update_vehicle_owner();
        break;

    case 5:
        vs.deleteVehicle();
        break;

    case 6:
        vs.listAllVehicles();
        break;

    case 7:
    FileLogger::log("User selected choice: " + to_string(choice));

            cout << "\nExiting program...\n";
            return 0;


    default:
        cout << "\nInvalid choice! Try again.\n";
    }
}

return 0;

}

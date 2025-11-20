#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
using namespace std;

// ----------------------------
// STRUCT (YOUR ORIGINAL STRUCT)
// ----------------------------
struct vehicle {
    int Registration_number;
    string owner_name;
    string vehicle_type;
    int model_year;
     string company; 
};

// ----------------------------
// VEHICLE SYSTEM CLASS
// ----------------------------
class vechicleSystem {

private:
    vector<vehicle> vechicles;
    map<int, vehicle> vechicle_map;
    set<string> vechicle_types;
    unordered_map<string, int> company_count;

public:

    // ----------------------------
    // REGISTER VEHICLE
    // ----------------------------
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
    }

    // ----------------------------
    // SEARCH BY REG NUMBER
    // ----------------------------
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
    }

    // ----------------------------
    // SEARCH BY OWNER NAME
    // ----------------------------
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
    }

    // ----------------------------
    // UPDATE OWNER NAME
    // ----------------------------
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
    }

    // ----------------------------
    // DELETE VEHICLE
    // ----------------------------
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
    }

    // ----------------------------
    // LIST ALL VEHICLES
    // ----------------------------
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
    }
};

// ----------------------------
// MAIN
// ----------------------------
int main() {

    vechicleSystem vs;

    vs.register_vechicle();
    vs.listAllVehicles();
    vs.search_vehicle();
    vs.searchByOwner();
    vs.update_vehicle_owner();
    vs.deleteVehicle();
    vs.listAllVehicles();

    return 0;
}

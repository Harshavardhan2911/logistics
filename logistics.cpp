#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// --- Inventory Class ---
class Inventory {
public:
    int ItemId;
    string ItemName;
    string Category;
    int Quantity;
    string Location;
    time_t LastUpdated;

    Inventory(int id = 0, string name = "", string cat = "", int qty = 0, string loc = "")
        : ItemId(id), ItemName(name), Category(cat), Quantity(qty), Location(loc), LastUpdated(time(nullptr)) {}

    void display() const {
        cout << "Item ID: " << ItemId << endl;
        cout << "Name: " << ItemName << endl;
        cout << "Category: " << Category << endl;
        cout << "Quantity: " << Quantity << endl;
        cout << "Location: " << Location << endl;
        cout << "Last Updated: " << formatDate(LastUpdated) << endl;
        cout << "-------------------------" << endl;
    }

private:
    string formatDate(time_t time) const {
        tm t;
#ifdef _MSC_VER
        localtime_s(&t, &time);
#else
        localtime_r(&time, &t);
#endif
        stringstream ss;
        ss << put_time(&t, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

// --- InventoryManager Class ---
class InventoryManager {
private:
    vector<Inventory> inventories;
    int nextItemId = 1;

public:
    void addInventory() {
        string name, category, location;
        int quantity;

        cout << "Enter Item Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Enter Quantity: ";
        cin >> quantity;
        if (cin.fail()) {
            cerr << "Invalid quantity input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter Location: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, location);

        inventories.emplace_back(nextItemId++, name, category, quantity, location);
        cout << "Inventory item added successfully with ID: " << inventories.back().ItemId << endl;
    }

    void viewInventory() const {
        if (inventories.empty()) {
            cout << "Inventory is empty." << endl;
            return;
        }
        cout << "--- Inventory List ---" << endl;
        for (const auto& item : inventories) {
            item.display();
        }
    }

    void searchInventory() const {
        int itemId;
        cout << "Enter Item ID to search: ";
        cin >> itemId;
        if (cin.fail()) {
            cerr << "Invalid ID input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (const auto& item : inventories) {
            if (item.ItemId == itemId) {
                cout << "--- Item Found ---" << endl;
                item.display();
                return;
            }
        }
        cout << "Inventory item with ID " << itemId << " not found." << endl;
    }

    void editInventory() {
        int itemId;
        cout << "Enter Item ID to edit: ";
        cin >> itemId;
        if (cin.fail()) {
            cerr << "Invalid ID input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (auto& item : inventories) {
            if (item.ItemId == itemId) {
                cout << "--- Editing Item ID: " << itemId << " ---" << endl;
                cout << "Enter new Item Name (" << item.ItemName << "): ";
                string name;
                getline(cin, name);
                if (!name.empty()) item.ItemName = name;

                cout << "Enter new Category (" << item.Category << "): ";
                string category;
                getline(cin, category);
                if (!category.empty()) item.Category = category;

                cout << "Enter new Quantity (" << item.Quantity << "): ";
                int quantity;
                cin >> quantity;
                if (!cin.fail()) item.Quantity = quantity;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter new Location (" << item.Location << "): ";
                string location;
                getline(cin, location);
                if (!location.empty()) item.Location = location;

                item.LastUpdated = time(nullptr);
                cout << "Inventory item with ID " << itemId << " updated." << endl;
                return;
            }
        }
        cout << "Inventory item with ID " << itemId << " not found." << endl;
    }

    void deleteInventory() {
        int itemId;
        cout << "Enter Item ID to delete: ";
        cin >> itemId;
        if (cin.fail()) {
            cerr << "Invalid ID input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        auto it = remove_if(inventories.begin(), inventories.end(),
                                [itemId](const Inventory& inv){ return inv.ItemId == itemId; });
        if (it != inventories.end()) {
            inventories.erase(it, inventories.end());
            cout << "Inventory item with ID " << itemId << " deleted." << endl;
        } else {
            cout << "Inventory item with ID " << itemId << " not found." << endl;
        }
    }

    void inventorySubMenu() {
        int choice;
        do {
            cout << "\n--- Inventory Management ---" << endl;
            cout << "1. Add Item" << endl;
            cout << "2. View Items" << endl;
            cout << "3. Search Item" << endl;
            cout << "4. Edit Item" << endl;
            cout << "5. Delete Item" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cerr << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1:
                    addInventory();
                    break;
                case 2:
                    viewInventory();
                    break;
                case 3:
                    searchInventory();
                    break;
                case 4:
                    editInventory();
                    break;
                case 5:
                    deleteInventory();
                    break;
                case 0:
                    cout << "Returning to Main Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }
};

// --- Maintenance Class ---
class Maintenance {
public:
    int ScheduleId;
    int EquipmentId;
    string Description;
    time_t ScheduledDate;
    string CompletionStatus;

    Maintenance(int scheduleId = 0, int equipmentId = 0, string description = "", time_t scheduledDate = 0, string completionStatus = "")
        : ScheduleId(scheduleId), EquipmentId(equipmentId), Description(description), ScheduledDate(scheduledDate), CompletionStatus(completionStatus) {}

    void display() const {
        cout << "Schedule ID: " << ScheduleId << endl;
        cout << "Equipment ID: " << EquipmentId << endl;
        cout << "Description: " << Description << endl;
        cout << "Scheduled Date: " << formatDate(ScheduledDate) << endl;
        cout << "Completion Status: " << CompletionStatus << endl;
        cout << "-------------------------" << endl;
    }

private:
    string formatDate(time_t time) const {
        tm t;
#ifdef _MSC_VER
        localtime_s(&t, &time);
#else
        localtime_r(&time, &t);
#endif
        stringstream ss;
        ss << put_time(&t, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

// --- MaintenanceRepository Class ---
class MaintenanceRepository {
private:
    vector<Maintenance> maintenances;
    int nextScheduleId = 1;

public:
    bool scheduleMaintenance(Maintenance b) {
        b.ScheduleId = nextScheduleId++;
        maintenances.push_back(b);
        return true;
    }

    bool updateSchedule(Maintenance b) {
        for (auto& m : maintenances) {
            if (m.ScheduleId == b.ScheduleId) {
                m.EquipmentId = b.EquipmentId;
                m.Description = b.Description;
                m.ScheduledDate = b.ScheduledDate;
                m.CompletionStatus = b.CompletionStatus;
                return true;
            }
        }
        return false;
    }

    bool removeMaintenance(int scheduleId) {
        auto it = remove_if(maintenances.begin(), maintenances.end(),
                            [scheduleId](const Maintenance& m){ return m.ScheduleId == scheduleId; });
        if (it != maintenances.end()) {
            maintenances.erase(it, maintenances.end());
            return true;
        }
        return false;
    }

    Maintenance* viewSchedule(int id) {
        for (auto& m : maintenances) {
            if (m.ScheduleId == id) {
                return &m;
            }
        }
        return nullptr;
    }

    vector<Maintenance> viewAll() const {
        return maintenances;
    }

    void maintenanceSubMenu() {
        int choice;
        do {
            cout << "\n--- Maintenance Management ---" << endl;
            cout << "1. Schedule Maintenance" << endl;
            cout << "2. View All Schedules" << endl;
            cout << "3. View Schedule Details" << endl;
            cout << "4. Update Schedule" << endl;
            cout << "5. Remove Schedule" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cerr << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1: {
                    int equipmentId;
                    string description, completionStatus;
                    time_t scheduledDate = time(nullptr); // Default to now

                    cout << "Enter Equipment ID: ";
                    cin >> equipmentId;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter Description: ";
                    getline(cin, description);
                    cout << "Enter Completion Status: ";
                    getline(cin, completionStatus);

                    Maintenance newMaintenance(0, equipmentId, description, scheduledDate, completionStatus);
                    if (scheduleMaintenance(newMaintenance)) {
                        cout << "Maintenance scheduled successfully." << endl;
                    } else {
                        cout << "Failed to schedule maintenance." << endl;
                    }
                    break;
                }
                case 2:
                    for (const auto& m : viewAll()) {
                        m.display();
                    }
                    break;
                case 3: {
                    int scheduleId;
                    cout << "Enter Schedule ID to view: ";
                    cin >> scheduleId;
                    if (auto maintenance = viewSchedule(scheduleId)) {
                        maintenance->display();
                    } else {
                        cout << "Schedule with ID " << scheduleId << " not found." << endl;
                    }
                    break;
                }
                case 4: {
                    int scheduleId, equipmentId;
                    string description, completionStatus;
                    time_t scheduledDate = time(nullptr);

                    cout << "Enter Schedule ID to update: ";
                    cin >> scheduleId;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter new Equipment ID: ";
                    cin >> equipmentId;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter new Description: ";
                    getline(cin, description);
                    cout << "Enter new Completion Status: ";
                    getline(cin, completionStatus);

                    Maintenance updatedMaintenance(scheduleId, equipmentId, description, scheduledDate, completionStatus);
                    if (updateSchedule(updatedMaintenance)) {
                        cout << "Schedule updated successfully." << endl;
                    } else {
                        cout << "Failed to update schedule." << endl;
                    }
                    break;
                }
                case 5: {
                    int scheduleId;
                    cout << "Enter Schedule ID to remove: ";
                    cin >> scheduleId;
                    if (removeMaintenance(scheduleId)) {
                        cout << "Schedule removed successfully." << endl;
                    } else {
                        cout << "Schedule with ID " << scheduleId << " not found." << endl;
                    }
                    break;
                }
                case 0:
                    cout << "Returning to Main Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }
};

// --- Report Class ---
class Report {
public:
    int ReportId;
    string ReportType;
    time_t GeneratedOn;
    string Details;

    Report(int reportId = 0, string reportType = "", time_t generatedOn = 0, string details = "")
        : ReportId(reportId), ReportType(reportType), GeneratedOn(generatedOn), Details(details) {}

    void display() const {
        cout << "Report ID: " << ReportId << endl;
        cout << "Report Type: " << ReportType << endl;
        cout << "Generated On: " << formatDate(GeneratedOn) << endl;
        cout << "Details: " << Details << endl;
        cout << "-------------------------" << endl;
    }

private:
    string formatDate(time_t time) const {
        tm t;
#ifdef _MSC_VER
        localtime_s(&t, &time);
#else
        localtime_r(&time, &t);
#endif
        stringstream ss;
        ss << put_time(&t, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

// --- ReportRepository Class ---
class ReportRepository {
private:
    vector<Report> reports;
    int nextReportId = 1;

public:
    bool generateReport(Report a) {
        a.ReportId = nextReportId++;
        reports.push_back(a);
        return true;
    }

    Report* downloadReport(int id) {
        for (auto& r : reports) {
            if (r.ReportId == id) {
                return &r;
            }
        }
        return nullptr;
    }

    vector<Report> viewReports() const {
        return reports;
    }

    void reportSubMenu() {
        int choice;
        do {
            cout << "\n--- Report Management ---" << endl;
            cout << "1. Generate Report" << endl;
            cout << "2. View All Reports" << endl;
            cout << "3. Download Report" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cerr << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1: {
                    string reportType, details;
                    time_t generatedOn = time(nullptr);

                    cout << "Enter Report Type: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, reportType);
                    cout << "Enter Report Details: ";
                    getline(cin, details);

                    Report newReport(0, reportType, generatedOn, details);
                    if (generateReport(newReport)) {
                        cout << "Report generated successfully." << endl;
                    } else {
                        cout << "Failed to generate report." << endl;
                    }
                    break;
                }
                case 2:
                    for (const auto& r : viewReports()) {
                        r.display();
                    }
                    break;
                case 3: {
                    int reportId;
                    cout << "Enter Report ID to download: ";
                    cin >> reportId;
                    if (auto report = downloadReport(reportId)) {
                        report->display();
                    } else {
                        cout << "Report with ID " << reportId << " not found." << endl;
                    }
                    break;
                }
                case 0:
                    cout << "Returning to Main Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }
};

// --- Shipment Class ---
class Shipment {
public:
    int ShipmentId;
    int ItemId;
    string Origin;
    string Destination;
    string Status;
    time_t ExpectedDelivery;
    Inventory* InventoryPtr = nullptr; // Simulate ForeignKey

    Shipment(int shipmentId = 0, int itemId = 0, string origin = "", string destination = "", string status = "", time_t expectedDelivery = 0)
        : ShipmentId(shipmentId), ItemId(itemId), Origin(origin), Destination(destination), Status(status), ExpectedDelivery(expectedDelivery) {}

    void display() const {
        cout << "Shipment ID: " << ShipmentId << endl;
        cout << "Item ID: " << ItemId << endl;
        cout << "Origin: " << Origin << endl;
        cout << "Destination: " << Destination << endl;
        cout << "Status: " << Status << endl;
        cout << "Expected Delivery: " << formatDate(ExpectedDelivery) << endl;
        cout << "-------------------------" << endl;
    }

private:
    string formatDate(time_t time) const {
        tm t;
#ifdef _MSC_VER
        localtime_s(&t, &time);
#else
        localtime_r(&time, &t);
#endif
        stringstream ss;
        ss << put_time(&t, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

// --- ShipmentRepository Class ---
class ShipmentRepository {
private:
    vector<Shipment> shipments;
    int nextShipmentId = 1;

public:
    bool receiveShipment(Shipment shipment) {
        shipment.ShipmentId = nextShipmentId++;
        shipments.push_back(shipment);
        return true;
    }

    bool removeShipment(int shipmentId) {
        auto it = remove_if(shipments.begin(), shipments.end(),
                            [shipmentId](const Shipment& s){ return s.ShipmentId == shipmentId; });
        if (it != shipments.end()) {
            shipments.erase(it, shipments.end());
            return true;
        }
        return false;
    }

    bool dispatchShipment(Shipment shipment) {
        for (auto& s : shipments) {
            if (s.ShipmentId == shipment.ShipmentId) {
                s.ItemId = shipment.ItemId;
                s.Origin = shipment.Origin;
                s.Destination = shipment.Destination;
                s.Status = shipment.Status;
                s.ExpectedDelivery = shipment.ExpectedDelivery;
                return true;
            }
        }
        return false;
    }

    Shipment* trackShipment(int id) {
        for (auto& s : shipments) {
            if (s.ShipmentId == id) {
                return &s;
            }
        }
        return nullptr;
    }

    vector<Shipment> viewShipment() const {
        return shipments;
    }

    void shipmentSubMenu() {
        int choice;
        do {
            cout << "\n--- Shipment Management ---" << endl;
            cout << "1. Receive Shipment" << endl;
            cout << "2. View All Shipments" << endl;
            cout << "3. Track Shipment" << endl;
            cout << "4. Dispatch Shipment" << endl;
            cout << "5. Remove Shipment" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cerr << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1: {
                    int itemId;
                    string origin, destination, status;
                    time_t expectedDelivery = time(nullptr) + (7 * 24 * 3600); // Default to a week from now

                    cout << "Enter Item ID: ";
                    cin >> itemId;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter Origin: ";
                    getline(cin, origin);
                    cout << "Enter Destination: ";
                    getline(cin, destination);
                    cout << "Enter Status: ";
                    getline(cin, status);

                    Shipment newShipment(0, itemId, origin, destination, status, expectedDelivery);
                    if (receiveShipment(newShipment)) {
                        cout << "Shipment received successfully." << endl;
                    } else {
                        cout << "Failed to receive shipment." << endl;
                    }
                    break;
                }
                case 2:
                    for (const auto& s : viewShipment()) {
                        s.display();
                    }
                    break;
                case 3: {
                    int shipmentId;
                    cout << "Enter Shipment ID to track: ";
                    cin >> shipmentId;
                    if (auto shipment = trackShipment(shipmentId)) {
                        shipment->display();
                    } else {
                        cout << "Shipment with ID " << shipmentId << " not found." << endl;
                    }
                    break;
                }
                case 4: {
                    int shipmentId, itemId;
                    string origin, destination, status;
                    time_t expectedDelivery = time(nullptr) + (7 * 24 * 3600);

                    cout << "Enter Shipment ID to dispatch: ";
                    cin >> shipmentId;
                    cout << "Enter Item ID: ";
                    cin >> itemId;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter Origin: ";
                    getline(cin, origin);
                    cout << "Enter Destination: ";
                    getline(cin, destination);
                    cout << "Enter Status: ";
                    getline(cin, status);

                    Shipment updatedShipment(shipmentId, itemId, origin, destination, status, expectedDelivery);
                    if (dispatchShipment(updatedShipment)) {
                        cout << "Shipment dispatched successfully." << endl;
                    } else {
                        cout << "Failed to dispatch shipment." << endl;
                    }
                    break;
                }
                case 5: {
                    int shipmentId;
                    cout << "Enter Shipment ID to remove: ";
                    cin >> shipmentId;
                    if (removeShipment(shipmentId)) {
                        cout << "Shipment removed successfully." << endl;
                    } else {
                        cout << "Shipment with ID " << shipmentId << " not found." << endl;
                    }
                    break;
                }
                case 0:
                    cout << "Returning to Main Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }
};

// --- Space Class ---
class Space {
public:
    int SpaceId;
    int TotalCapacity;
    int UsedCapacity;
    string Zone;

    Space(int spaceId = 0, int totalCapacity = 0, int usedCapacity = 0, string zone = "")
        : SpaceId(spaceId), TotalCapacity(totalCapacity), UsedCapacity(usedCapacity), Zone(zone) {}

    int getAvailableCapacity() const {
        return TotalCapacity - UsedCapacity;
    }

    void display() const {
        cout << "Space ID: " << SpaceId << endl;
        cout << "Total Capacity: " << TotalCapacity << endl;
        cout << "Used Capacity: " << UsedCapacity << endl;
        cout << "Available Capacity: " << getAvailableCapacity() << endl;
        cout << "Zone: " << Zone << endl;
        cout << "-------------------------" << endl;
    }
};

// --- SpaceRepository Class ---
class SpaceRepository {
private:
    vector<Space> spaces;
    int nextSpaceId = 1;

public:
    bool allocateSpace(Space space) {
        space.SpaceId = nextSpaceId++;
        spaces.push_back(space);
        return true;
    }

    bool freeSpace(int spaceId) {
        auto it = remove_if(spaces.begin(), spaces.end(),
                            [spaceId](const Space& sp){ return sp.SpaceId == spaceId; });
        if (it != spaces.end()) {
            spaces.erase(it, spaces.end());
            return true;
        }
        return false;
    }

    bool updateSpace(Space space) {
        for (auto& sp : spaces) {
            if (sp.SpaceId == space.SpaceId) {
                sp.TotalCapacity = space.TotalCapacity;
                sp.UsedCapacity = space.UsedCapacity;
                sp.Zone = space.Zone;
                return true;
            }
        }
        return false;
    }

    Space* searchSpace(int id) {
        for (auto& sp : spaces) {
            if (sp.SpaceId == id) {
                return &sp;
            }
        }
        return nullptr;
    }

    vector<Space> viewSpaceUsage() const {
        return spaces;
    }

    void spaceSubMenu() {
        int choice;
        do {
            cout << "\n--- Space Management ---" << endl;
            cout << "1. Allocate Space" << endl;
            cout << "2. View Space Usage" << endl;
            cout << "3. Search Space" << endl;
            cout << "4. Update Space" << endl;
            cout << "5. Free Space" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cerr << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1: {
                    int totalCapacity, usedCapacity;
                    string zone;
                    cout << "Enter Total Capacity: ";
                    cin >> totalCapacity;
                    cout << "Enter Used Capacity: ";
                    cin >> usedCapacity;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter Zone: ";
                    getline(cin, zone);
                    Space newSpace(0, totalCapacity, usedCapacity, zone);
                    if (allocateSpace(newSpace)) {
                        cout << "Space allocated successfully." << endl;
                    } else {
                        cout << "Failed to allocate space." << endl;
                    }
                    break;
                }
                case 2:
                    for (const auto& sp : viewSpaceUsage()) {
                        sp.display();
                    }
                    break;
                case 3: {
                    int spaceId;
                    cout << "Enter Space ID to search: ";
                    cin >> spaceId;
                    if (auto space = searchSpace(spaceId)) {
                        space->display();
                    } else {
                        cout << "Space with ID " << spaceId << " not found." << endl;
                    }
                    break;
                }
                case 4: {
                    int spaceId, totalCapacity, usedCapacity;
                    string zone;
                    cout << "Enter Space ID to update: ";
                    cin >> spaceId;
                    cout << "Enter new Total Capacity: ";
                    cin >> totalCapacity;
                    cout << "Enter new Used Capacity: ";
                    cin >> usedCapacity;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter new Zone: ";
                    getline(cin, zone);
                    Space updatedSpace(spaceId, totalCapacity, usedCapacity, zone);
                    if (updateSpace(updatedSpace)) {
                        cout << "Space updated successfully." << endl;
                    } else {
                        cout << "Failed to update space." << endl;
                    }
                    break;
                }
                case 5: {
                    int spaceId;
                    cout << "Enter Space ID to free: ";
                    cin >> spaceId;
                    if (freeSpace(spaceId)) {
                        cout << "Space freed successfully." << endl;
                    } else {
                        cout << "Space with ID " << spaceId << " not found." << endl;
                    }
                    break;
                }
                case 0:
                    cout << "Returning to Main Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }
};

int main() {
    InventoryManager inventoryManager;
    MaintenanceRepository maintenanceRepo;
    ReportRepository reportRepo;
    ShipmentRepository shipmentRepo;
    SpaceRepository spaceRepo;
    int choice;

    do {
        cout << "\n--- Logistics Warehouse CLI ---" << endl;
        cout << "1. Inventory Management" << endl;
        cout << "2. Maintenance Management" << endl;
        cout << "3. Report Management" << endl;
        cout << "4. Shipment Management" << endl;
        cout << "5. Space Management" << endl;
        cout << "0. Exit Application" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cerr << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                inventoryManager.inventorySubMenu();
                break;
            case 2:
                maintenanceRepo.maintenanceSubMenu();
                break;
            case 3:
                reportRepo.reportSubMenu();
                break;
            case 4:
                shipmentRepo.shipmentSubMenu();
                break;
            case 5:
                spaceRepo.spaceSubMenu();
                break;
            case 0:
                cout << "Exiting application." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}


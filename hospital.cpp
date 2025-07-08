#include <bits/stdc++.h>
using namespace std;

constexpr int SIZE_OF_SPECIALIZATION = 21;
constexpr int SIZE_OF_QUEUE = 5;

class Patient {
public:
    string name;
    string status; // "Urgent" or "Regular"

    Patient(string _name, string _status) : name(_name), status(_status) {}
};

class SpecializationQueue {
private:
    deque<Patient> patients;

public:
    bool addPatient(const string& name, bool isUrgent) {
        if (patients.size() >= SIZE_OF_QUEUE)
            return false;

        string status = isUrgent ? "Urgent" : "Regular";
        Patient newPatient(name, status);

        if (isUrgent)
            patients.emplace_front(newPatient);
        else
            patients.emplace_back(newPatient);

        return true;
    }

    bool hasPatients() const {
        return !patients.empty();
    }

    void printPatients(int specializationId) const {
        if (patients.empty())
            return;

        cout << "There are " << patients.size()
             << " patient(s) in specialization " << specializationId << ":\n";
        for (const auto& p : patients)
            cout << p.name << " - " << p.status << "\n";
    }

    void getNextPatient() {
        if (patients.empty()) {
            cout << "No patients at the moment. Have a rest, doctor.\n\n";
            return;
        }

        cout << patients.front().name << ", please go with the doctor.\n\n";
        patients.pop_front();
    }
};

class HospitalSystem {
private:
    vector<SpecializationQueue> specializations;

public:
    HospitalSystem() : specializations(SIZE_OF_SPECIALIZATION) {}

    void addPatient() {
        int spec;
        string name;
        bool isUrgent;

        cout << "Enter Specialization (0-20), Name, and Status (1 = urgent, 0 = regular): ";
        cin >> spec >> name >> isUrgent;

        if (spec < 0 || spec >= SIZE_OF_SPECIALIZATION) {
            cout << "Invalid specialization!\n\n";
            return;
        }

        bool success = specializations[spec].addPatient(name, isUrgent);
        if (!success)
            cout << "Sorry, the queue is full.\n\n";
    }

    void printAllPatients() const {
        bool empty = true;
        for (int i = 0; i < SIZE_OF_SPECIALIZATION; ++i) {
            if (specializations[i].hasPatients()) {
                specializations[i].printPatients(i);
                empty = false;
            }
        }
        if (empty)
            cout << "No patients.\n";
        cout << "\n";
    }

    void getNextPatient() {
        int spec;
        cout << "Enter Specialization (0-20): ";
        cin >> spec;

        if (spec < 0 || spec >= SIZE_OF_SPECIALIZATION) {
            cout << "Invalid specialization!\n\n";
            return;
        }

        specializations[spec].getNextPatient();
    }

    void run() {
        while (true) {
            cout << "Enter Your Choice:\n";
            cout << "1) Add new patient\n";
            cout << "2) Print all patients\n";
            cout << "3) Get next patient\n";
            cout << "4) Exit\n";

            int choice;
            cin >> choice;

            if (choice == 1)
                addPatient();
            else if (choice == 2)
                printAllPatients();
            else if (choice == 3)
                getNextPatient();
            else if (choice == 4) {
                cout << "Thanks, see you soon!\n";
                break;
            } else
                cout << "Invalid choice, try again.\n";
        }
    }
};

int main() {
    HospitalSystem hospital;
    hospital.run();
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Company {
    string name;
    string owner;
    string phone;
    string address;
    string activity;
};

class Directory {
private:
    vector<Company> companies;
    string filename = "companies.txt";

    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;

        Company c;
        while (getline(file, c.name) &&
               getline(file, c.owner) &&
               getline(file, c.phone) &&
               getline(file, c.address) &&
               getline(file, c.activity)) {
            companies.push_back(c);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        for (auto& c : companies) {
            file << c.name << endl;
            file << c.owner << endl;
            file << c.phone << endl;
            file << c.address << endl;
            file << c.activity << endl;
        }
        file.close();
    }

public:
    Directory() {
        loadFromFile();
    }

    ~Directory() {
        saveToFile();
    }

    void addCompany() {
        Company c;
        cout << "Назва фірми: ";
        getline(cin, c.name);
        cout << "Власник: ";
        getline(cin, c.owner);
        cout << "Телефон: ";
        getline(cin, c.phone);
        cout << "Адреса: ";
        getline(cin, c.address);
        cout << "Рід діяльності: ";
        getline(cin, c.activity);
        
        companies.push_back(c);
        cout << "Додано!\n";
    }

    void searchByName() {
        string name;
        cout << "Введіть назву: ";
        getline(cin, name);
        
        for (auto& c : companies) {
            if (c.name.find(name) != string::npos) {
                printCompany(c);
            }
        }
    }

    void searchByOwner() {
        string owner;
        cout << "Введіть власника: ";
        getline(cin, owner);
        
        for (auto& c : companies) {
            if (c.owner.find(owner) != string::npos) {
                printCompany(c);
            }
        }
    }

    void searchByPhone() {
        string phone;
        cout << "Введіть телефон: ";
        getline(cin, phone);
        
        for (auto& c : companies) {
            if (c.phone.find(phone) != string::npos) {
                printCompany(c);
            }
        }
    }

    void searchByActivity() {
        string activity;
        cout << "Введіть рід діяльності: ";
        getline(cin, activity);
        
        for (auto& c : companies) {
            if (c.activity.find(activity) != string::npos) {
                printCompany(c);
            }
        }
    }

    void showAll() {
        if (companies.empty()) {
            cout << "Довідник порожній\n";
            return;
        }

        for (auto& c : companies) {
            printCompany(c);
        }
    }

    void printCompany(const Company& c) {
        cout << "------------------------\n";
        cout << "Фірма: " << c.name << endl;
        cout << "Власник: " << c.owner << endl;
        cout << "Телефон: " << c.phone << endl;
        cout << "Адреса: " << c.address << endl;
        cout << "Діяльність: " << c.activity << endl;
    }
};

int main() {
    Directory dir;
    int choice;

    while (true) {
        cout << "\n1. Додати\n2. Пошук за назвою\n3. Пошук за власником\n";
        cout << "4. Пошук за телефоном\n5. Пошук за діяльністю\n6. Всі записи\n7. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: dir.addCompany(); break;
            case 2: dir.searchByName(); break;
            case 3: dir.searchByOwner(); break;
            case 4: dir.searchByPhone(); break;
            case 5: dir.searchByActivity(); break;
            case 6: dir.showAll(); break;
            case 7: return 0;
            default: cout << "Невірний вибір!\n";
        }
    }
}
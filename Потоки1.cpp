#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Student {
private:
    string name;
    int age;
    string group;
    double averageGrade;

public:
    Student(string n = "", int a = 0, string g = "", double avg = 0.0)
        : name(n), age(a), group(g), averageGrade(avg) {}

    // Методы для доступа к полям
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGroup() const { return group; }
    double getAverageGrade() const { return averageGrade; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setGroup(string g) { group = g; }
    void setAverageGrade(double avg) { averageGrade = avg; }

    // Вывод информации о студенте
    void display() const {
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Группа: " << group << endl;
        cout << "Средний балл: " << averageGrade << endl;
        cout << "------------------------" << endl;
    }

    // Сохранение в файл
    void saveToFile(ofstream& file) const {
        file << name << endl;
        file << age << endl;
        file << group << endl;
        file << averageGrade << endl;
    }

    // Загрузка из файла
    void loadFromFile(ifstream& file) {
        getline(file, name);
        string ageStr, gradeStr;
        getline(file, ageStr);
        getline(file, group);
        getline(file, gradeStr);
        
        age = stoi(ageStr);
        averageGrade = stod(gradeStr);
    }
};

class StudentManager {
private:
    vector<Student> students;
    string filename = "students.txt";

public:
    // Добавление студента
    void addStudent() {
        string name, group;
        int age;
        double grade;

        cout << "Введите имя: ";
        getline(cin, name);
        cout << "Введите возраст: ";
        cin >> age;
        cin.ignore();
        cout << "Введите группу: ";
        getline(cin, group);
        cout << "Введите средний балл: ";
        cin >> grade;
        cin.ignore();

        students.push_back(Student(name, age, group, grade));
        cout << "Студент добавлен!" << endl;
    }

    // Сохранение всех студентов в файл
    void saveAllToFile() {
        ofstream file(filename);
        if (!file) {
            cout << "Ошибка открытия файла!" << endl;
            return;
        }

        file << students.size() << endl; // Сохраняем количество
        for (const auto& student : students) {
            student.saveToFile(file);
        }
        file.close();
        cout << "Данные сохранены в файл!" << endl;
    }

    // Загрузка всех студентов из файла
    void loadAllFromFile() {
        ifstream file(filename);
        if (!file) {
            cout << "Файл не найден!" << endl;
            return;
        }

        students.clear();
        int count;
        file >> count;
        file.ignore(); // Пропускаем перевод строки

        for (int i = 0; i < count; i++) {
            Student student;
            student.loadFromFile(file);
            students.push_back(student);
        }
        file.close();
        cout << "Данные загружены из файла!" << endl;
    }

    // Показать всех студентов
    void displayAll() {
        if (students.empty()) {
            cout << "Список студентов пуст!" << endl;
            return;
        }

        cout << "\n=== СПИСОК СТУДЕНТОВ ===" << endl;
        for (const auto& student : students) {
            student.display();
        }
    }
};

void studentMenu() {
    StudentManager manager;
    int choice;

    while (true) {
        cout << "\n=== УПРАВЛЕНИЕ СТУДЕНТАМИ ===" << endl;
        cout << "1. Добавить студента" << endl;
        cout << "2. Сохранить в файл" << endl;
        cout << "3. Загрузить из файла" << endl;
        cout << "4. Показать всех" << endl;
        cout << "5. Назад" << endl;
        cout << "Выберите: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.saveAllToFile(); break;
            case 3: manager.loadAllFromFile(); break;
            case 4: manager.displayAll(); break;
            case 5: return;
            default: cout << "Неверный выбор!" << endl;
        }
    }
}
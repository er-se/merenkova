#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

// Функция для проверки корректности ввода целого числа
// Возвращает введённое пользователем целое число, запрашивая его до тех пор, пока ввод не станет корректным
int get_valid_int(const string& prompt) {
    int value;
    while (true) {
        cout << prompt; // Вывод сообщения с запросом ввода
        cin >> value; // Считывание значения
        if (cin.fail()) { // Проверка, корректен ли ввод
            cout << "Invalid input. Please enter a valid integer.\n"; // Сообщение об ошибке
            cin.clear(); // Сброс флага ошибки ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        }
        else {
            return value; // Возврат корректного значения
        }
    }
}

// Функция для проверки корректности ввода числа с плавающей точкой
// Возвращает введённое пользователем число с плавающей точкой
double get_valid_double(const string& prompt) {
    double value;
    while (true) {
        cout << prompt; // Вывод сообщения с запросом ввода
        cin >> value; // Считывание значения
        if (cin.fail()) { // Проверка, корректен ли ввод
            cout << "Invalid input. Please enter a valid number.\n"; // Сообщение об ошибке
            cin.clear(); // Сброс флага ошибки ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        }
        else {
            return value; // Возврат корректного значения
        }
    }
}

// Функция для проверки корректности ввода булевого значения (0 или 1)
// Возвращает введённое пользователем булевое значение
bool get_valid_bool(const string& prompt) {
    int value;
    while (true) {
        cout << prompt; // Вывод сообщения с запросом ввода
        cin >> value; // Считывание значения
        if (cin.fail() || (value != 0 && value != 1)) { // Проверка корректности ввода
            cout << "Invalid input. Please enter 1 (yes) or 0 (no).\n"; // Сообщение об ошибке
            cin.clear(); // Сброс флага ошибки ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        }
        else {
            return value; // Возврат корректного значения
        }
    }
}

// Класс для описания трубы (Pipe)
class Pipe {
public:
    string name; // Имя трубы
    double length; // Длина трубы
    double diameter; // Диаметр трубы
    bool in_repair; // Флаг состояния ремонта трубы (в ремонте или нет)

    // Конструктор по умолчанию, инициализирующий все поля значениями по умолчанию
    Pipe() : name(""), length(0), diameter(0), in_repair(false) {}

    // Метод для ввода данных о трубе с консоли
    void input() {
        cout << "Enter pipe name: "; // Запрос имени трубы
        cin >> name; // Считывание имени
        length = get_valid_double("Enter pipe length: "); // Запрос длины трубы
        diameter = get_valid_double("Enter pipe diameter: "); // Запрос диаметра трубы
        in_repair = get_valid_bool("Is the pipe under repair? (1 - yes, 0 - no): "); // Запрос состояния ремонта
    }

    // Метод для отображения информации о трубе
    void display() const {
        cout << "Pipe \"" << name << "\", length: " << length
            << ", diameter: " << diameter
            << ", status: " << (in_repair ? "under repair" : "not under repair") << endl; // Вывод данных о трубе
    }

    // Метод для изменения состояния ремонта трубы
    void edit_repair_status() {
        cout << "Current repair status: " << (in_repair ? "under repair" : "not under repair") << endl; // Текущее состояние
        in_repair = get_valid_bool("Change status (1 - under repair, 0 - not under repair): "); // Ввод нового состояния
    }
};

// Класс для описания компрессорной станции
class CompressorStation {
public:
    string name; // Имя станции
    int num_shops; // Общее количество цехов на станции
    int working_shops; // Количество рабочих цехов
    double efficiency; // Эффективность станции
    // Конструктор по умолчанию, инициализирующий все поля значениями по умолчанию
    CompressorStation() : name(""), num_shops(0), working_shops(0), efficiency(0) {}

    // Метод для ввода данных о компрессорной станции
    void input() {
        cout << "Enter station name: "; // Запрос имени станции
        cin >> name; // Считывание имени
        num_shops = get_valid_int("Enter number of shops: "); // Запрос общего количества цехов
        while (true) {
            working_shops = get_valid_int("Enter number of working shops: "); // Запрос количества рабочих цехов
            if (working_shops <= num_shops) break; // Проверка, что количество рабочих цехов не превышает общее количество
            cout << "Number of working shops cannot exceed the total number of shops.\n"; // Ошибка
        }
        efficiency = get_valid_double("Enter station efficiency: "); // Запрос эффективности станции
    }

    // Метод для отображения информации о станции
    void display() const {
        cout << "Station \"" << name << "\", number of shops: " << num_shops
            << ", working shops: " << working_shops
            << ", efficiency: " << efficiency << endl; // Вывод данных о станции
    }

    // Метод для изменения количества рабочих цехов
    void edit_working_shops() {
        cout << "Current number of working shops: " << working_shops << endl; // Текущее количество рабочих цехов
        while (true) {
            int new_working_shops = get_valid_int("Enter new number of working shops: "); // Запрос нового значения
            if (new_working_shops <= num_shops) { // Проверка корректности
                working_shops = new_working_shops; // Установка нового значения
                break;
            }
            else {
                cout << "Number of working shops cannot exceed the total number of shops.\n"; // Ошибка
            }
        }
    }
};
// Функция для сохранения данных в файл
// Сохраняет список труб и компрессорных станций в файл с заданным именем
void save_to_file(const vector<Pipe>& pipes, const vector<CompressorStation>& stations, const string& filename) {
    ofstream file(filename); // Открытие файла для записи
    if (file.is_open()) { // Проверка, удалось ли открыть файл
        file << pipes.size() << endl; // Сохранение количества труб
        for (const auto& pipe : pipes) { // Сохранение данных о каждой трубе
            file << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.in_repair << endl;
        }
        file << stations.size() << endl; // Сохранение количества компрессорных станций
        for (const auto& station : stations) { // Сохранение данных о каждой станции
            file << station.name << " " << station.num_shops << " " << station.working_shops << " " << station.efficiency << endl;
        }
        file.close(); // Закрытие файла
        cout << "Data saved to file " << filename << endl; // Уведомление о завершении сохранения
    }
    else {
        cout << "Error opening file!" << endl; // Сообщение об ошибке открытия файла
    }
}
// Функция для загрузки данных из файла
// Загружает список труб и компрессорных станций из файла с заданным именем
void load_from_file(vector<Pipe>& pipes, vector<CompressorStation>& stations, const string& filename) {
    ifstream file(filename); // Открытие файла для чтения
    if (file.is_open()) { // Проверка, удалось ли открыть файл
        pipes.clear(); // Очистка текущего списка труб
        stations.clear(); // Очистка текущего списка станций
        size_t pipe_count, station_count; // Количество труб и станций в файле
        file >> pipe_count; // Чтение количества труб
        for (size_t i = 0; i < pipe_count; ++i) { // Цикл для чтения данных каждой трубы
            Pipe pipe;
            file >> pipe.name >> pipe.length >> pipe.diameter >> pipe.in_repair; // Чтение свойств трубы
            pipes.push_back(pipe); // Добавление трубы в список
        }
        file >> station_count; // Чтение количества станций
        for (size_t i = 0; i < station_count; ++i) { // Цикл для чтения данных каждой станции
            CompressorStation station;
            file >> station.name >> station.num_shops >> station.working_shops >> station.efficiency; // Чтение свойств станции
            stations.push_back(station); // Добавление станции в список
        }
        file.close(); // Закрытие файла
        cout << "Data loaded from file " << filename << endl; // Уведомление о завершении загрузки
    }
    else {
        cout << "Error opening file!" << endl; // Сообщение об ошибке открытия файла
    }
}

// Функция отображения меню
// Выводит список доступных действий для пользователя
void display_menu() {
    cout << "1. Add a pipe\n"; // Добавить новую трубу
    cout << "2. Add a compressor station\n"; // Добавить новую компрессорную станцию
    cout << "3. View all objects\n"; // Просмотреть все созданные объекты
    cout << "4. Edit a pipe\n"; // Изменить состояние трубы
    cout << "5. Edit a compressor station\n"; // Изменить свойства станции
    cout << "6. Save data\n"; // Сохранить данные в файл
    cout << "7. Load data\n"; // Загрузить данные из файла
    cout << "0. Exit\n"; // Выйти из программы
}

// Главная функция программы
int main() {
    vector<Pipe> pipes; // Вектор для хранения объектов класса Pipe (труб)
    vector<CompressorStation> stations; // Вектор для хранения объектов класса CompressorStation (станций)
    string filename = "data.txt"; // Имя файла по умолчанию для сохранения и загрузки данных
    int choice; // Переменная для хранения выбора пользователя

    while (true) { // Бесконечный цикл программы, пока пользователь не выберет выход
        display_menu(); // Вывод меню на экран
        choice = get_valid_int("Enter your choice: "); // Получение выбора пользователя

        if (choice == 0) { // Если выбор 0, завершить программу
            break;
        }
        switch (choice) { // Обработка выбора пользователя
        case 1: { // Добавление новой трубы
            Pipe pipe; // Создание объекта трубы
            pipe.input(); // Ввод данных трубы
            pipes.push_back(pipe); // Добавление трубы в список
            break;
        }
        case 2: { // Добавление новой компрессорной станции
            CompressorStation station; // Создание объекта станции
            station.input(); // Ввод данных станции
            stations.push_back(station); // Добавление станции в список
            break;
        }
        case 3: { // Просмотр всех объектов
            cout << "Pipes:\n"; // Заголовок для труб
            for (const auto& pipe : pipes) { // Перебор всех труб в списке
                pipe.display(); // Вывод информации о трубе
            }
            cout << "Compressor Stations:\n"; // Заголовок для станций
            for (const auto& station : stations) { // Перебор всех станций в списке
                station.display(); // Вывод информации о станции
            }
            break;
        }
        case 4: { // Редактирование состояния трубы
            if (pipes.empty()) { // Проверка, есть ли трубы в списке
                cout << "No pipes to edit.\n"; // Сообщение об отсутствии труб
            }
            else {
                size_t index = get_valid_int("Enter pipe index to edit (0 - " + to_string(pipes.size() - 1) + "): "); // Запрос индекса
                if (index < pipes.size()) { // Проверка корректности индекса
                    pipes[index].edit_repair_status(); // Изменение состояния ремонта трубы
                }
                else {
                    cout << "Invalid index!" << endl; // Сообщение об ошибке
                }
            }
            break;
        }
        case 5: { // Редактирование станции
            if (stations.empty()) { // Проверка, есть ли станции в списке
                cout << "No compressor stations to edit.\n"; // Сообщение об отсутствии станций
            }
            else {
                size_t index = get_valid_int("Enter station index to edit (0 - " + to_string(stations.size() - 1) + "): "); // Запрос индекса
                if (index < stations.size()) { // Проверка корректности индекса
                    stations[index].edit_working_shops(); // Изменение данных станции
                }
                else {
                    cout << "Invalid index!" << endl; // Сообщение об ошибке
                }
            }
            break;
        }
        case 6: { // Сохранение данных в файл
            save_to_file(pipes, stations, filename); // Вызов функции сохранения
            break;
        }
        case 7: { // Загрузка данных из файла
            load_from_file(pipes, stations, filename); // Вызов функции загрузки
            break;
        }
        default: // Обработка некорректного выбора
            cout << "Invalid choice!" << endl; // Сообщение об ошибке
            break;
        }
    }

    return 0; // Завершение программы
}
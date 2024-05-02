    #include <iostream>
    #include <cmath>

    #include "Lab3Example.h"
    using namespace std;

    class Cube {
    private:
        double side;
        string color;

    public:
        // Конструктор за замовчуванням
        Cube() {
            side = 1.0;
            color = "white";
        }

        // Конструктор з параметрами
        Cube(double s, string c) {
            side = s;
            color = c;
        }

        // Функція-член обчислення площі поверхні
        double surfaceArea() {
            return 6 * side * side;
        }

        // Функція-член обчислення об'єму
        double volume() {
            return side * side * side;
        }

        // Функція-член обчислення довжини діагоналі
        double diagonalLength() {
            return sqrt(3) * side;
        }

        // Функція-член обчислення об'єму вписаної сфери
        double inscribedSphereVolume() {
            return (4.0 / 3.0) * 3.14 * pow(side / 2.0, 3);
        }

        // Функція-член встановлення значення сторони та кольору
        void setSide(double s) {
            if (s > 0) {
                side = s;
            }
            else {
                cout << "Error: Side length must be positive." << endl;
            }
        }

        void setColor(string c) {
            color = c;
        }

        // Функції-члени, що повертають значення полів
        double getSide() {
            return side;
        }

        string getColor() {
            return color;
        }

        // Функція-член для друку
        void print() {
            cout << "Cube:" << endl;
            cout << "  Side length: " << side << endl;
            cout << "  Color: " << color << endl;
            cout << "  Surface Area: " << surfaceArea() << endl;
            cout << "  Volume: " << volume() << endl;
            cout << "  Diagonal Length: " << diagonalLength() << endl;
            cout << "  Inscribed Sphere Volume: " << inscribedSphereVolume() << endl;
        }
    };

    class Multiset {
    private:
        unsigned int* set; // вказівник на масив
        unsigned int beg; // початок діапазону
        unsigned int end; // кінець діапазону
        int size; // розмір масиву
        int state; // код стану

    public:
        // Конструктори
        Multiset() : beg(0), end(100), size(100), state(0) {
            set = new unsigned int[size](); // ініціалізуємо масив нулями
        }

        Multiset(unsigned int end) : beg(0), end(end), size(end), state(0) {
            set = new unsigned int[size]();
        }

        Multiset(unsigned int beg, unsigned int end) : beg(beg), end(end), size(end - beg), state(0) {
            set = new unsigned int[size]();
        }

        Multiset(unsigned int beg, unsigned int end, unsigned int value) : beg(beg), end(end), size(end - beg), state(0) {
            set = new unsigned int[size]();
            for (int i = 0; i < size; ++i) {
                set[i] = value;
            }
        }

        // Конструктор копіювання
        Multiset(const Multiset& other) : beg(other.beg), end(other.end), size(other.size), state(other.state) {
            set = new unsigned int[size]();
            for (int i = 0; i < size; ++i) {
                set[i] = other.set[i];
            }
        }

        // Оператор присвоєння
        Multiset& operator=(const Multiset& other) {
            if (this != &other) {
                delete[] set;
                beg = other.beg;
                end = other.end;
                size = other.size;
                state = other.state;
                set = new unsigned int[size]();
                for (int i = 0; i < size; ++i) {
                    set[i] = other.set[i];
                }
            }
            return *this;
        }

        // Деструктор
        ~Multiset() {
            delete[] set;
        }

        // Функції-члени
        void setValue(unsigned int index, unsigned int value = 0) {
            if (index >= size) {
                state = -1; // помилка: виходить за межі множини
                return;
            }
            set[index] = value;
        }

        int getCount(unsigned int value) const {
            int count = 0;
            for (int i = 0; i < size; ++i) {
                if (set[i] == value) {
                    count++;
                }
            }
            return count;
        }

        // Функції-члени для арифметичних операцій
        Multiset Union(const Multiset& other) const {
            unsigned int newEnd = max(end, other.end);
            Multiset result(0, newEnd);
            for (int i = 0; i < size; ++i) {
                result.setValue(i, set[i]);
            }
            for (int i = 0; i < other.size; ++i) {
                result.setValue(i, other.set[i]);
            }
            return result;
        }

        Multiset Intersection(const Multiset& other) const {
            unsigned int newBeg = max(beg, other.beg);
            unsigned int newEnd = min(end, other.end);
            Multiset result(newBeg, newEnd);
            for (int i = 0; i < size && i < other.size; ++i) {
                result.setValue(i, set[i] & other.set[i]); // бітове І
            }
            return result;
        }

        Multiset Difference(const Multiset& other) const {
            unsigned int newBeg = max(beg, other.beg);
            unsigned int newEnd = max(end, other.end);
            Multiset result(newBeg, newEnd);
            for (int i = 0; i < size; ++i) {
                result.setValue(i, set[i] & ~other.set[i]); // бітове І не
            }
            return result;
        }

        // Функції порівняння
        bool operator>(const Multiset& other) const {
            return size > other.size;
        }

        bool operator<(const Multiset& other) const {
            return size < other.size;
        }

        bool operator==(const Multiset& other) const {
            if (size != other.size) {
                return false;
            }
            for (int i = 0; i < size; ++i) {
                if (set[i] != other.set[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Multiset& other) const {
            return !(*this == other);
        }

        // Функція друку
        void print() const {
            cout << "{ ";
            for (int i = 0; i < size; ++i) {
                cout << set[i] << " ";
            }
            cout << "}" << endl;
        }

        // Перевірка на помилку
        int getState() const {
            return state;
        }

        // Підрахунок числа об'єктів даного типу
        static int countObjects;
    };

    int Multiset::countObjects = 0;

    int main()
    {
        cout << " Lab #3  !\n";
        int task;
        cout << "Enter task: " << endl;
        cin >> task;
        switch(task)
        {
        case 1: {
            Cube cube1;
            cout << "Cube 1:" << endl;
            cube1.print();

            // Створення об'єкту класу Cube за допомогою конструктора з параметрами
            Cube cube2(2.5, "blue");
            cout << "\nCube 2:" << endl;
            cube2.print();

            // Встановлення нових значень сторони та кольору для cube1
            cube1.setSide(3.0);
            cube1.setColor("red");
            cout << "\nUpdated Cube 1:" << endl;
            cube1.print();
            break;
        }
        case 2: {
            // Тестування функцій класу Multiset
            Multiset set1; // конструктор без параметрів
            Multiset set2(50); // конструктор з одним параметром
            Multiset set3(10, 30); // конструктор з двома параметрами
            Multiset set4(1, 5, 3); // конструктор з трьома параметрами

            // Вивід множин
            cout << "Set 1: ";
            set1.print();
            cout << "Set 2: ";
            set2.print();
            cout << "Set 3: ";
            set3.print();
            cout << "Set 4: ";
            set4.print();

            // Копіювання множин
            Multiset set5 = set1; // конструктор копіювання
            cout << "Set 5 (copy of Set 1): ";
            set5.print();

            // Перевірка порівняння
            cout << "Is Set 1 > Set 2? " << (set1 > set2) << endl;
            cout << "Is Set 3 < Set 4? " << (set3 < set4) << endl;
            cout << "Is Set 3 == Set 4? " << (set3 == set4) << endl;
            cout << "Is Set 1 != Set 5? " << (set1 != set5) << endl;

            // Арифметичні операції
            Multiset unionSet = set1.Union(set2);
            Multiset intersectSet = set3.Intersection(set4);
            Multiset diffSet = set4.Difference(set3);

            cout << "Union of Set 1 and Set 2: ";
            unionSet.print();
            cout << "Intersection of Set 3 and Set 4: ";
            intersectSet.print();
            cout << "Difference of Set 4 and Set 3: ";
            diffSet.print();
            break;
        }default: {
            cout << "Invalid task number!" << endl;
            break;
        }
        }




    }


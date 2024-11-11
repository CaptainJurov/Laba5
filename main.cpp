#include <iostream>
#include <iterator>
#include <stack>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
struct Машина {
    int id;
    Машина(const Машина& машина): id(машина.id) {} 
    Машина() {id = rand()%2024;}
    Машина(int йд):id(йд) {}
    bool operator==(const Машина& right) {return right.id==id;}
    bool operator!=(const Машина& right) {return !(*this==right);}
    friend std::ostream& operator<<(std::ostream& os, const Машина& машина) {
        os << "ID: " << машина.id;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Машина& машина) {
        int йд;
        is >> йд;
        if (йд==0) {
            машина.id = rand()%2024;
        }
        else {
            машина.id = йд;
        }
        return is;
    }
};
class Стоянка {
private:
    std::stack<Машина> Машины;
    std::map<int, int> counts; 
public:
    Стоянка() {}
    void вставить(Машина машина) {
        Машины.push(машина);
        std::cout << "Автомобиль " << машина.id << " прибыл." << std::endl;
    }
    void вставить(std::vector<Машина> vec) {
        for (auto i: vec) {
            Машины.push(Машина(i));
        }
    }
    auto GS() {
        return Машины;
    }
    void достать(Машина машина) {
        int count = 0;
        while (!Машины.empty() and Машины.top() != машина) {
            Машина removed_car = Машины.top();
            Машины.pop();
            count++;
            std::cout << "Автомобиль " << removed_car.id << " был удален со стоянки." << std::endl;
        }

        if (!Машины.empty()) {
            Машины.pop();
            std::cout << "Автомобиль " << машина.id << " уехал со стоянки." << std::endl;
            counts[машина.id] += машина.id;
            std::cout << "Автомобиль " << машина.id << " был удален со стоянки " << counts[машина.id] << " раз." << std::endl;
        }
        else {
            std::cout << "Автомобиль " << машина.id << " не найден на стоянке." << std::endl;
        }
    }

    void show() {
        std::cout << "Машины на стоянке:\n";
        if (Машины.empty()) {
            std::cout << "пусто" << std::endl;
        } else {
            std::stack<Машина> temp = Машины;
            while (!temp.empty()) {
                std::cout << temp.top().id << " ";
                temp.pop();
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Стоянка гараж;

    std::vector<Машина> vec;
    std::cout<<"Вводи id машин для заполнения стэка:\n";
    std::copy(
        std::istream_iterator<Машина>(std::cin),
        std::istream_iterator<Машина>(),
        std::back_inserter(vec)
    );
    гараж.вставить(vec);
    
    for (;;) {
        int id;
        std::cout << "Введите <номер машины>: ";
        std::cin >> id;
        гараж.достать(Машина(id));
        гараж.show();
    }

    return 0;
}
#include <iostream>
#include <iterator>
#include <stack>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
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
        is >> машина.id;
        return is;
    }
};
class Стоянка {
private:
    std::forward_list<Машина> Машины;
public:
    Стоянка() {}
    void вставить(Машина машина) {
        Машины.push_front(машина);
        std::cout << "Автомобиль " << машина.id << " прибыл." << std::endl;
    }
    void вставить(std::vector<Машина>& vec) {
        for (auto i=vec.begin(); i!=vec.end();i++) {
            std::cout << *i;
            вставить(Машина(*i));
        }
    }
    auto GS() {
        return Машины;
    }
    void достать(Машина машина) {
        std::forward_list<Машина> temp;
        auto iter = Машины.begin();
        while (!Машины.empty() and (*iter) != машина) {
            iter++;
        }
        if (!Машины.empty()) {
            temp.splice_after(temp.before_begin(), Машины, Машины.cbegin(), iter); //
            std::copy(temp.begin(), temp.end(), std::ostream_iterator<Машина>(std::cout, " Временно выехал со стоянки\n"));
            std::cout << "Автомобиль " << машина.id << " успешно уехал со стоянки." << std::endl;
            Машины.erase_after(iter);
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
            std::forward_list<Машина> temp = Машины;
            while (!temp.empty()) {
                std::cout << (*temp.begin()).id << " ";
                temp.pop_front();
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Стоянка гараж;

    std::cout<<"Вводи id машин для заполнения стэка:\n";
    for (;;) {
        Машина машина;
        int inp;
        std::cin >> inp;
        if (inp == 0) {break;}
        гараж.вставить(Машина(inp));
        std::cout<<"Next:\n";
    }
    for (;;) {
        int id;
        std::cout << "Введите <номер машины>: ";
        std::cin >> id;
        гараж.достать(Машина(id));
        гараж.show();
    }

    return 0;
}
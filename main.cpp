#include <iostream>
#include <iterator>
#include <algorithm>
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
    auto GS() {
        return Машины;
    }
    void достать(Машина& машина) {
        if (Машины.empty()) {
            std::cout<<"Стоянка пуста!\n";
            return;
        }
        std::forward_list<Машина> temp;
        auto iter = Машины.begin();
        while (iter!=Машины.end() and (*iter) != машина) {
            iter++;
            if (iter==Машины.end()) {
                std::cout << "Автомобиль " << машина << " не найден на стоянке." << std::endl;
                return;
            }
        }
        temp.splice_after(temp.before_begin(), Машины, Машины.before_begin(), iter);
        std::copy(temp.begin(), temp.end(), std::ostream_iterator<Машина>(std::cout, " Временно выехал со стоянки\n"));
        std::cout << "Автомобиль " << Машины.front() << " успешно уехал со стоянки." << std::endl;
        Машины.pop_front();
        Машины.splice_after(Машины.before_begin(), temp);
        std::copy(temp.begin(), temp.end(), std::front_inserter(Машины));
    }

    void show() {
        std::cout << "------\nМашины на стоянке:\n";
        if (Машины.empty()) {
            std::cout << "пусто" << std::endl;
        } else {
            std::copy(Машины.begin(), Машины.end(), std::ostream_iterator<Машина>(std::cout, "\n"));
            std::cout<<"------\n";
        }
    }
};

int main() {
    Стоянка гараж;
    for (;;) {
        Машина машина;
        int inp;
        std::cout<<"Вводи <Номер>:\n";
        std::cin >> inp;
        if (inp == 0) {break;}
        гараж.вставить(Машина(inp));
    }
    гараж.show();
    for (;;) {
        int id;
        std::cout << "Введите <номер машины>: ";
        std::cin >> id;
        if (id==0) {break;}
        Машина prim(id);
        гараж.достать(prim);
        гараж.show();
    }
    return 0;
}
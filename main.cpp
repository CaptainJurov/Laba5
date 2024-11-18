#include <iostream>
#include <iterator>
#include <algorithm>
#include <forward_list>
#include "colors.h"
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
        std::cout << Colors::green << "Автомобиль " << машина.id << " прибыл." << Colors::reset << std::endl;
    }
    auto GS() {
        return Машины;
    }
    void достать(Машина& машина) {
        if (Машины.empty()) {
            std::cout<<Colors::red<<Colors::bold<<"Стоянка пуста!\n"<<Colors::reset;
            return;
        }
        std::forward_list<Машина> temp;
        auto iter = Машины.begin();
        while (iter!=Машины.end() and (*iter) != машина) {
            iter++;
            if (iter==Машины.end()) {
                std::cout << Colors::red << "Автомобиль " << Colors::ital << машина << Colors::конец_ital << " не найден на стоянке."<< Colors::reset << std::endl;
                return;
            }
        }
        std::cout<<Colors::скучный;
        temp.splice_after(temp.before_begin(), Машины, Машины.before_begin(), iter);
        std::copy(temp.begin(), temp.end(), std::ostream_iterator<Машина>(std::cout, " Временно выехал со стоянки\n"));
        std::cout << Colors::green << "Автомобиль " << Машины.front() << " успешно уехал со стоянки." << std::endl;
        Машины.pop_front();
        Машины.splice_after(Машины.before_begin(), temp);
        std::copy(temp.begin(), temp.end(), std::front_inserter(Машины));
        std::cout<<Colors::reset;
    }
    
    void show() {
        std::cout << Colors::недозелёный <<"Машины на стоянке:\n"<<Colors::ital;
        if (Машины.empty()) {
            std::cout << Colors::red <<"пусто"<<std::endl;
        } else {
            std::copy(Машины.begin(), Машины.end(), std::ostream_iterator<Машина>(std::cout, "\n"));
        }
        std::cout<<Colors::reset;
    }
};

int main() {   
    Стоянка * гараж = new Стоянка;
    for (;;) {
        Машина машина;
        int inp;
        std::cout<<Colors::clear;
        гараж->show();
        std::cout << Colors::зачёрк <<"\nВводи <Номер>: ";
        std::cin >> inp;
        std::cout<<Colors::reset;
        if (inp == 0) {std::cout<<Colors::clear;break;}
        гараж->вставить(Машина(inp));
    }
    гараж->show();
    for (;;) {
        int id;
        std::cout << Colors::зачёрк << "\nВводи <номер машины>: ";
        std::cin >> id;
        std::cout<<Colors::reset<<Colors::clear<<"\n";
        if (id==0) {break;}
        Машина prim(id);
        гараж->достать(prim);
        гараж->show();
    }
    delete гараж;
    return 0;
}
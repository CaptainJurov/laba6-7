#include <iostream>
#include <istream>
#include <ostream>
#include <stack>
#include <string>
#include "colors.h"
const char glas[] = "aAeEiIoOuUyY";
bool match(char s) {
    for (auto i: glas) {
        if (s==i) {return true;}
    }
    return false;
} 
struct Источник {
    std::stack<char> Input;
    Источник () {}
    virtual void str_to_stack(std::string& str) {
        for (auto i: str) {
            Input.push(i);
        }
    }
    std::string get_str() {
        std::string temp;
        std::stack<char> temps = Input;
        while (!temps.empty()) {
            temp.push_back(temps.top());
            temps.pop();
        }
        return temp;
    }
    Источник reverse() {
        Источник result;
        std::stack<char> temps = Input;
        while (!temps.empty()) {
            result.Input.push(temps.top());
            temps.pop();
        }
        return result;
    }
};

struct Второй: Источник {
    Второй(): Источник() {}
    void str_to_stack(std::string& str) override {
        for (auto i: str) {
            if (match(i)) {
                Input.push(i);
            }
        }
    }
    void transfer(Источник& gl) {
        std::string first;
        std::string second;
        while (!gl.Input.empty()) {
            if (match(gl.Input.top())) {
                second.push_back(gl.Input.top());
            }
            else {first.push_back(gl.Input.top());}
            gl.Input.pop();
        }
        gl.str_to_stack(first);
        str_to_stack(second);
    }
};

class Коробка {
private:
    Источник Первый;
    Второй Приёмник;
public:
    Источник& get_First() {
        return Первый;
    }
    Второй& get_Second() {
        return Приёмник;
    }
    friend std::istream& operator>>(std::istream& is, Коробка& источник) {
        std::string temp;
        std::getline(is, temp);
        источник.get_First().str_to_stack(temp);
        источник.get_Second().transfer(источник.get_First());
        return is;
    }
};

int main() {
    std::cout<<Colors::clear;
    for (;;) {
        std::cout<<Colors::зачёрк<<"Вводи текс: ";
        Коробка хз;
        std::cin>>хз;
        std::cout << Colors::reset;
        std::cout << "Первый стак: " << Colors::green << Colors::bold << хз.get_First().get_str() << std::endl << Colors::reset;
        std::cout << "Второй стак(с гласными): " << Colors::blue << Colors::bold << хз.get_Second().get_str() << std::endl << std::endl << Colors::reset;
        std::cout << "Первый стак(reverse): " << Colors::green << Colors::bold << хз.get_First().reverse().get_str() << std::endl << Colors::reset;
        std::cout << "Второй стак(с гласными(reverse)): " << Colors::blue << Colors::bold << хз.get_Second().reverse().get_str() << std::endl << std::endl << Colors::reset;
    }
    return 0;
}
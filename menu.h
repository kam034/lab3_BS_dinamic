#ifndef PROG3A_MENU_H
#define PROG3A_MENU_H


#include <limits>
//#include "..\Library\BS\include\BinarySignal.h"
#include "BinarySignal.h"


template <class T>
int getNum(T &a)
{
    while (true) {
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR! Invalid data! Try again please: ->";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 1;
        }
    }
}

int getPositiveNum(int &a);

void print_menu();
void emptyConstructor(Prog3::BinarySignal& ptr);
void firstConstructor(Prog3::BinarySignal& ptr);
void secondConstructor(Prog3::BinarySignal &ptr);
void inputSequence(Prog3::BinarySignal& ptr);
void outputSequence(Prog3::BinarySignal &ptr);
void copyBinarySignal(Prog3::BinarySignal& ptr);
void inversionBinarySignal(Prog3::BinarySignal& ptr);
void insertBinarySignal(Prog3::BinarySignal& ptr);
void removeBinarySignal(Prog3::BinarySignal& ptr);
void addBinarySignal(Prog3::BinarySignal& ptr);
void elemArray(Prog3::BinarySignal& ptr);

#endif //PROG3A_MENU_H

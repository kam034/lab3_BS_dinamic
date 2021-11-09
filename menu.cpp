#include "menu.h"


void print_menu() {
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Empty constructor" << std::endl;
    std::cout << "2. Creating a binary signal with initialization of one signal with const level with max duration" << std::endl;
    std::cout << "3. Creating a binary signal with initialization of signal how string of char" << std::endl;
    std::cout << "4. Input a binary signal" << std::endl;
    std::cout << "5. Output a binary signal" << std::endl;
    std::cout << "6. Copying the signal multiple times" << std::endl;
    std::cout << "7. Inversion a binary signal" << std::endl;
    std::cout << "8. Insert binary signal" << std::endl;
    std::cout << "9. Remove binary signal" << std::endl;
    std::cout << "10. Add binary signal" << std::endl;
    std::cout << "11. Get a item of binary signal's array" << std::endl;
}

void emptyConstructor(Prog3::BinarySignal& ptr) {
    Prog3::BinarySignal tmp;
    ptr = tmp;
}

void firstConstructor(Prog3::BinarySignal& ptr) {
    bool el;
    std::cout << "Enter level of the binary signal: ->";
    getNum(el);
    Prog3::BinarySignal tmp(el);
    ptr = tmp;
}

void secondConstructor(Prog3::BinarySignal &ptr) {
    int sz;
    std::cout << "Enter the number of elements in the binary signal ->";
    getPositiveNum(sz);
    char sq[sz + 1];
    std::cout << "Enter the string of 0 and 1 ->" << std::endl;
    for (int i = 0; i < sz; i++)
        std::cin >> sq[i];
    try {
        Prog3::BinarySignal tmp(sz + 1, sq);
        ptr = tmp;
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
    catch (std::invalid_argument &ia) {
        std::cout << ia.what() << std::endl;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << "Memory allocation error!" << ba.what() << std::endl;
    }
}

void inputSequence(Prog3::BinarySignal& ptr)
{
    std::cin >> ptr;
}

void outputSequence(Prog3::BinarySignal& ptr) {
    std::cout << ptr;
}


void elemArray(Prog3::BinarySignal& ptr) {
    Prog3::Status t;
    int n;
    std::cout << "Enter the number of the item you want to receive ->";
    getNum(n);
    try {
        t = ptr.getM_ARRAY()[n];
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
    std::cout << "level " << t.m_level << std::endl;
    std::cout << "duration " << static_cast<int>(t.m_duration) << std::endl;
}


void copyBinarySignal(Prog3::BinarySignal& ptr) {
    int n;
    std::cout << "Enter number of signal copies ->";
    getNum(n);
    try {
        ptr.copy(n);
        //ptr *= n;    //перегрузка модифиц присваивания += (копирует сигнал n раз)
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << "Memory allocation error!" << ba.what() << std::endl;
    }
}


void inversionBinarySignal(Prog3::BinarySignal& ptr) {
    ptr.inverting();
    //~ptr;       // перегрузка оператора инверсии ~
}


void insertBinarySignal(Prog3::BinarySignal& ptr) {
    int prd;
    Prog3::BinarySignal tmp;
    std::cin >> tmp;
    std::cout << "Enter the period: ->";
    getPositiveNum(prd);
    try {
        ptr.insert(prd, tmp);
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
}

void removeBinarySignal(Prog3::BinarySignal& ptr) {
    int start, prd;
    std::cout << "Enter the start: ->";
    getPositiveNum(start);
    std::cout << "Enter the period: ->";
    getPositiveNum(prd);
    try {
        ptr.remove(start, prd);
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
}

void addBinarySignal(Prog3::BinarySignal& ptr) {
    Prog3::BinarySignal tmp;
    Prog3::BinarySignal t;
    std::cin >> tmp;
    try {
        ptr.add(tmp);
        //t = ptr + tmp;  //перегрузка бинарного оператора +
    }
    catch (std::length_error &le) {
        std::cout << le.what() << std::endl;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << "Memory allocation error!" << ba.what() << std::endl;
    }
}

int getPositiveNum(int &a) {
    const char *pr = "";
    do {
        std::cout << pr << std::endl;
        pr = "You are wrong! Repeat again please!";
        if (getNum(a) < 1)
            return 1;
    } while (a < 1);
}

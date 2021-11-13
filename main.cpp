#include "menu.h"


int main()
{
    int command;
    Prog3::BinarySignal tmp;

    print_menu();

    do {
        std::cout << "Enter the command: ->";
        getNum(command);
        switch(command)
        {
            case 0:
                std::cout << "EXIT!" << std::endl;
                break;
            case 1:
                emptyConstructor(tmp);
                break;
            case 2:
                firstConstructor(tmp);
                break;
            case 3:
                secondConstructor(tmp);
                break;
            case 4:
                inputSequence(tmp);
                break;
            case 5:
                outputSequence(tmp);
                break;
            case 6:
                copyBinarySignal(tmp);;
                break;
            case 7:
                inversionBinarySignal(tmp);
                break;
            case 8:
                insertBinarySignal(tmp);
                break;
            case 9:
                removeBinarySignal(tmp);
                break;
            case 10:
                addBinarySignal(tmp);
                break;
            case 11:
                elemArray(tmp);
                break;
            default:
                std::cout << "ERROR! There is no such command." << std::endl;
        }
    } while (command != 0);

    return 0;
}


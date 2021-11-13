#ifndef LAB3_BS_DINAMIC_BINARYSIGNAL_H
#define LAB3_BS_DINAMIC_BINARYSIGNAL_H

#include <iostream>
#include <limits>

namespace Prog3 {

    template<class T>
    void getNum(std::istream &in, T &num) {
        while (true) {
            in >> num;
            if (!in.good()) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
    }

    struct Status {
        bool m_level;
        unsigned char m_duration;
    };

    class BinarySignal {
    private:
        static const int BLOCK = 5;         //ПАМЯТЬ ВЫДЕЛЯЕТСЯ БЛОКАМИ
        static const int MAX = 255;
        int m_length;                //размер сигнала (110101 - размер 6)
        int m_size;                     //фактический размер массива(заполненные ячейки)
        int m_count;                     //количество ячеек, под которые выделена память
        Status* m_array;


    public:
                //контрукторы
        BinarySignal() noexcept;
        explicit BinarySignal(bool lvl) noexcept;
        BinarySignal(int size, const char* bs);
        BinarySignal(const BinarySignal& a);    //копирующий
        BinarySignal(BinarySignal&& a) noexcept;    //перемещающий

                //деструктор
        ~BinarySignal() noexcept;

                //методы
        BinarySignal& initialization(int size, int length, const char *string);
        BinarySignal& mem_alloc(int size);    //выделяет память и копирует данные из старого массива в новый бОльший массив
        BinarySignal& inverting() noexcept;
        BinarySignal& add(const BinarySignal &bs);
        BinarySignal& copy(int n);
        BinarySignal& insert(int prd, const BinarySignal &ptr);
        BinarySignal& remove(int start, int prd);

                //перегрузки
        friend std::istream &operator>>(std::istream &in, BinarySignal &bs);
        friend std::ostream &operator<<(std::ostream &out, const BinarySignal &bs);
        BinarySignal& operator = (const BinarySignal& a) noexcept;  //копирующий оператор присваивания
        BinarySignal& operator = (BinarySignal&& a) noexcept;   //перемещающий оператор присваивания
        friend BinarySignal operator+(const BinarySignal &a, const BinarySignal &b);
        BinarySignal& operator*=(int n);
        BinarySignal& operator()(const char* bs, int n, int size);
        Status& operator[](int n);
        const Status& operator[](int n) const;
        BinarySignal& operator~();
        BinarySignal& operator--();
        const BinarySignal operator--(int);
        friend bool operator==(const BinarySignal& a, const BinarySignal& b);

                //геттеры
        [[nodiscard]] const Status* getM_ARRAY() const;
        [[nodiscard]] int getM_SZ() const;
        [[nodiscard]] int getM_LGHT() const;
        [[nodiscard]] int getM_CNT() const;

    };
}

//посмотреть перегрузку индексирования у шустовой
//проверить склеиваются ли ячейки массива и размер выделенной памяти у массива
//написать нормальную перегрзку бинарного опреатора
//починить второй конструктор
//

#endif //LAB3_BS_DINAMIC_BINARYSIGNAL_H

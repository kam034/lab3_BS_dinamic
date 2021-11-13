#include "BinarySignal.h"

namespace Prog3 {


                        //======КОНСТРУКТОРЫ======

    //пустой
    BinarySignal::BinarySignal() noexcept: m_size(0), m_count(BLOCK), m_length(0), m_array(new Status[BLOCK]) {

    }

    //первый
    BinarySignal::BinarySignal(bool lvl) noexcept: m_size(1), m_length(MAX), m_count(BLOCK) {
        m_array = new Status[BLOCK];
        m_array[0].m_level = lvl;
        m_array[0].m_duration = MAX;
    }

    //второй
    BinarySignal::BinarySignal(int length, const char *string) : m_size(0), m_length(length), m_count(0), m_array{} {
        int size = 0;
        for (int i = 0; i < m_length;) {
            if (string[i] == '0') {
                size += 1;
                while (string[i] == '0' && i < m_length)
                    i++;
            } else if (string[i] == '1') {
                size += 1;
                while (string[i] == '1' && i < m_length)
                    i++;
            } else
                throw std::invalid_argument("ERROR! Illegal value from binary signal!");
        }
        initialization(size, length, string);
    }

    //КОПИРУЮЩИЙ КОНСТРУКТОР
    BinarySignal::BinarySignal(const BinarySignal &a) :
            m_count(a.m_count), m_size(a.m_size), m_length(a.m_length), m_array(new Status[m_count]) {
        for (int i = 0; i < m_size; i++)
            m_array[i] = a.m_array[i];
    }

    //ПЕРЕМЕЩАЮЩИЙ КОНСТРУКТОР
    BinarySignal::BinarySignal(BinarySignal &&a) noexcept:
            m_count(a.m_count), m_size(a.m_size), m_length(a.m_length), m_array(a.m_array) {
        delete[] a.m_array;
    }

                // ДЕКСТРУТОР
    BinarySignal::~BinarySignal() noexcept {
        delete[] m_array;
    }


                //======МЕТОДЫ=====


    //выделяет память и копирует данные из старого массива в новый бОльший массив
    BinarySignal& BinarySignal::mem_alloc(int size) {
        if (size != 0 && size != m_count) {
            Status *tmp = m_array;
            m_array = new Status[size];
            for (int i = 0; i < m_size; i++) {
                m_array[i] = tmp[i];
            }
            m_count = size;
            delete[] tmp;
        }
        return *this;
    }


    // обработка строки и распределение по массиву состояний
    BinarySignal &BinarySignal::initialization(int size, int length, const char *string) {
        m_size = size;
        m_length = length;
        m_count = BLOCK * ((m_size - 1) * BLOCK + 1);
        if (m_size == 0)
            m_array = nullptr;
        else {
            int counter = 0, duration = 0;
            m_array = new Status[m_count];
            for (int i = 0; i < m_length;) {
                if (string[i] == '0') {
                    m_array[counter].m_level = false;
                    while (string[i] == '0' && i < m_length) {
                        duration += 1;
                        i++;
                        if (duration > MAX)
                            throw std::length_error("ERROR! Illegal size for binary signal, because m_duration > MAX!");
                    }
                    m_array[counter].m_duration = duration;
                } else if (string[i] == '1') {
                    m_array[counter].m_level = true;
                    while (string[i] == '1' && i < m_length) {
                        duration += 1;
                        i++;
                        if (duration > MAX)
                            throw std::length_error("ERROR! Illegal size for binary signal, because m_duration > MAX!");
                    }
                    m_array[counter].m_duration = duration;
                } else
                    throw std::invalid_argument("ERROR! Illegal value from binary signal!");
                duration = 0;
                counter += 1;
            }
        }
        return *this;
    }

    // инвертирование сигнала
    BinarySignal& BinarySignal::inverting() noexcept {
        for (int i = 0; i < m_size; i++) {
            if (m_array[i].m_level)
                m_array[i].m_level = !m_array[i].m_level;
        }
        return *this;
    }


    // добавление в конец и склеивание
    BinarySignal& BinarySignal::add(const BinarySignal &bs) {
        mem_alloc(m_size + bs.m_size);
        if (!bs.m_size);
        else if (!m_size)
            *this = bs;
        else {
            if (m_array[m_size - 1].m_level == bs.m_array[0].m_level) {
                if (m_array[m_size - 1].m_duration + bs.m_array[0].m_duration > MAX)
                    throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
                m_array[m_size - 1].m_duration += bs.m_array[0].m_duration;
                for (int i = 0; i < bs.m_size - 1; i++)
                    m_array[i + m_size] = bs.m_array[i + 1];
                m_size += bs.m_size - 1;
                m_count = m_count - 1;
            } else {
                for (int i = 0; i < bs.m_size; i++)
                    m_array[i + m_size] = bs.m_array[i];
                m_size += bs.m_size;
            }
            m_length += bs.m_length;
        }
        m_count += bs.m_count;
        return *this;
    }

    //копирование сигнала n раз
    BinarySignal& BinarySignal::copy(int n) {
        BinarySignal tmp = *this;
        for (int i = 0; i < n - 1; i++)
            this->add(tmp);
        return *this;
    }

    //вставка в определенную duration
    BinarySignal& BinarySignal::insert(int prd, const BinarySignal &ptr) {
        if (prd > m_length)
            throw std::length_error("Illegal size for binary signal, because prd > m_lght!");
        BinarySignal begin, end, tmp = *this;
        if (prd == 0) {
            begin = ptr;
            begin.add(*this);
            *this = begin;
            return *this;
        }
        if (prd == m_length) {
            add(ptr);
            return *this;
        }
        int k = 0, i;
        for (i = 0; i < m_size; i++) {
            k += m_array[i].m_duration;
            if (k > prd - 1)
                break;
        }
        tmp.m_size = i + 1;
        tmp.m_length = prd;
        tmp.m_array[i].m_duration -= k - prd;
        begin = tmp;
        begin.add(ptr);
        if (k == prd) {
            end.m_size = m_size - tmp.m_size;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + tmp.m_size];
        } else {
            end.m_size = m_size - tmp.m_size + 1;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + tmp.m_size - 1];
            end.m_array[0].m_duration = k - prd;
        }
        end.m_length = m_length - prd;
        begin.add(end);
        *this = begin;
        return *this;
    }

    //удаление в опр момент времени с продолжительностью
    BinarySignal& BinarySignal::remove(int start, int prd) {
        if (start + prd > m_length)
            throw std::length_error("Illegal size for binary signal, because prd > m_lght!");
        int k = 0, q = 0, i;
        BinarySignal begin, end, tmp = *this;
        for (i = 0; i < m_size; i++) {
            k += m_array[i].m_duration;
            if (k > start - 1)
                break;
        }
        tmp.m_size = i + 1;
        tmp.m_length = start;
        tmp.m_array[i].m_duration -= k - start;
        begin = tmp;
        for (i = 0; i < m_size; i++) {
            q += m_array[i].m_duration;
            if (q > start + prd - 1)
                break;
        }
        int s = i;
        if (q == start + prd) {
            end.m_size = m_size - s - 1;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + s + 1];
        } else {
            end.m_size = m_size - s;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + s];
            end.m_array[0].m_duration = q - start - prd;
        }
        end.m_length = m_length - begin.m_length - prd;
        begin.add(end);
        *this = begin;
        return *this;
    }


                    //======ПЕРЕГРУЗКИ======


    std::istream &operator>>(std::istream &in, BinarySignal &bs) {
        if (bs.m_size != 0)
            delete[] bs.m_array;
        int length;
        std::cout << "Enter the size of string -> " << std::endl;
        getNum(in, length);
        if (length > 0) {
            int size = 1;
            char string[length + 1];
            std::cout << "Enter the string (separated by a space) ->" << std::endl;
            getNum(in, string[0]);
            for (int i = 1; i < length; i++) {
                getNum(in, string[i]);
                if (string[i - 1] != string[i])
                    size += 1;
            }
            bs.initialization(size, length, string);
        }
        return in;
    }


    std::ostream &operator<<(std::ostream &out, const BinarySignal &bs) {
        if (bs.m_size == 0)
            out << "Binary Signal is empty!";
        else {
            std::cout << "Binary signal -> ";
            for (int i = 0; i < bs.m_size; i++)
                for (int j = 0; j < bs.m_array[i].m_duration; j++)
                    out << bs.m_array[i].m_level;
        }
        std::cout << std::endl;
        return out;
    }


    //КОПИРУЮЩИЙ ОПЕРАТОР ПРИСВАИВАНИЯ
    BinarySignal &BinarySignal::operator=(const BinarySignal &a) noexcept {
        if (this != &a) {
            delete[] m_array;
            m_count = a.m_count;
            m_size = a.m_size;
            m_length = a.m_length;
            m_array = new Status[m_count];
            for (int i = 0; i < m_size; i++)
                m_array[i] = a.m_array[i];
        }
        return *this;
    }

    //ПЕРЕМЕЩАЮЩИЙ ОПЕРАТОР ПРИСВАИВАНИЯ
    BinarySignal &BinarySignal::operator=(BinarySignal &&a) noexcept {
        if (this != &a) {
            int tmp = m_count;
            m_count = a.m_count;
            a.m_count = tmp;

            tmp = m_size;
            m_size = a.m_size;
            a.m_size = tmp;

            tmp = m_length;
            m_length = a.m_length;
            a.m_length = tmp;

            Status *t = m_array;
            m_array = a.m_array;
            a.m_array = t;
        }
        return *this;
    }

    BinarySignal operator+(const BinarySignal &a, const BinarySignal &b) {
        BinarySignal c(a);
        c.add(b);
        std::cout << "1: " << a.getM_SZ() << " " << a.getM_CNT() << " " << a.getM_LGHT() ;
        std::cout << "2: " << b.getM_SZ() << " " << b.getM_CNT() << " " << b.getM_LGHT() ;
        std::cout << "rez: " << c.getM_SZ() << " " << c.getM_CNT() << " " << c.getM_LGHT() ;
        return c;
    }


    BinarySignal& BinarySignal::operator*=(int n) {
        copy(n);
        return *this;
    }

    BinarySignal& BinarySignal::operator()(const char* bs, int n, int size) {
        initialization(size, n, bs);
        return *this;
    }


    BinarySignal& BinarySignal::operator~() {
        inverting();
        return *this;
    }

    Status& BinarySignal::operator[](int n) {     //для не const массива
        if (n < 0 || n > m_size)
            throw std::invalid_argument("Invalid index of array!");
        return m_array[n];
    }

    const Status& BinarySignal::operator[](int n) const {    //для const массива
        if (n < 0 || n > m_size)
            throw std::invalid_argument("Invalid index of array!");
        return m_array[n];
    }

    BinarySignal& BinarySignal::operator--() {   //префикс
        remove(0, m_array[0].m_duration);
        return *this;
    }

    // (int) - фиктивный целочислинный параметр, чтобы отличить постфикс от префикса
    const BinarySignal BinarySignal::operator--(int) {  //постфикс
        BinarySignal t(*this);
        remove(0, m_array[0].m_duration);
        return t;
    }

    bool operator==(const BinarySignal &a, const BinarySignal& b) {
        int t = 0;
        for (int i = 0; i < a.m_size; i++) {
            if (a.m_array[i].m_level == b.m_array[i].m_level
            && a.m_array[i].m_duration == b.m_array[i].m_duration)
                t++;
        }
        if (b.m_count == a.m_count && b.m_size == a.m_size &&
        b.m_length == a.m_length && (t == a.m_size)) {
            return true; }
        else
            return false;
    }


                        //GETТЕРЫ

    const Status* BinarySignal::getM_ARRAY() const {
        return m_array;
    }

    int BinarySignal::getM_SZ() const {
        return m_size;
    }

    int BinarySignal::getM_LGHT() const {
        return m_length;
    }

    int BinarySignal::getM_CNT() const {
        return m_count;
    }

}







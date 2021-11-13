#include "..\..\lab3_BS_dinamic\BinarySignal.h"
#include "lib\googletest-master\googletest\include\gtest\gtest.h"



TEST(BinarySignalConstructor, CopyConstructor) {
    Prog3::BinarySignal a2(7, "1011001") ;
    Prog3::BinarySignal a1(a2);
    ASSERT_EQ(a1, a2);

    Prog3::BinarySignal b2(true);
    Prog3::BinarySignal b1(b2);
    ASSERT_EQ(b1, b2);
}

TEST(BinarySignalConstructor, MoveConstructor) {
    Prog3::BinarySignal b1(9, "101001101");
    Prog3::BinarySignal c1 = b1;

    b1 = std::move(b1);

    Prog3::BinarySignal a(b1);
    ASSERT_EQ(a, c1);

    Prog3::BinarySignal b2(false);
    Prog3::BinarySignal c2 = b2;

    b2 = std::move(b2);

    Prog3::BinarySignal a2(b2);
    ASSERT_EQ(a2, c2);
}

TEST(BinarySignalMethods, BinaryOperator) {
    Prog3::BinarySignal a1(3, "101");
    Prog3::BinarySignal b1(5, "00111");
    Prog3::BinarySignal c1(8, "10100111");
    Prog3::BinarySignal d1 = a1 + b1;
    ASSERT_EQ(c1, d1);

    Prog3::BinarySignal a2;
    Prog3::BinarySignal b2(6, "100101");
    Prog3::BinarySignal c2 = a2 + b2;
    ASSERT_EQ(b2, c2);

}

TEST(BinarySignalMethods, CopyAssignmentOperator) {
    Prog3::BinarySignal a1(3, "101");
    Prog3::BinarySignal b1(5, "00111");
    a1 = b1;
    ASSERT_EQ(a1, b1);

    Prog3::BinarySignal c1(8, "10100111");
    Prog3::BinarySignal d1;
    d1 = c1;
    ASSERT_EQ(c1, d1);

}

TEST(BinarySignalMethods, MoveAssignmentOperator) {
    Prog3::BinarySignal a1(7, "1011001");
    Prog3::BinarySignal c1(8, "10100111");
    Prog3::BinarySignal c2 = c1;

    c1 = std::move(c1);
    a1 = c1;

    ASSERT_EQ(a1, c2);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
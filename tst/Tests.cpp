#include "gtest/gtest.h"
#include "complex_lab.h"

//Получить / Установить действительную часть
//Получить / Установить мнимую часть
TEST(ComplexTest, ConstructorAndAccessors) {
	Complex c(2.0f, 3.0f);
	c.setReal(3.0f); c.setImaginary(2.0f);
	EXPECT_FLOAT_EQ(c.getReal(), 3.0f);
	EXPECT_FLOAT_EQ(c.getImaginary(), 2.0f);
}

// Сложение
TEST(ComplexTest, Addition) {
	Complex a(2.0f, 3.0f);
	Complex b(4.0f, -2.0f);
	Complex result = a + b;
	EXPECT_FLOAT_EQ(result.getReal(), 6.0f);
	EXPECT_FLOAT_EQ(result.getImaginary(), 1.0f);
}

//Вычитание
TEST(ComplexTest, Subtraction) {
	Complex a(2.0f, 3.0f);
	Complex b(4.0f, -2.0f);
	Complex result = a - b;
	EXPECT_FLOAT_EQ(result.getReal(), -2.0f);
	EXPECT_FLOAT_EQ(result.getImaginary(), 5.0f);
}

//Умножение
TEST(ComplexTest, Multiplication) {
	Complex a(2.0f, 3.0f);
	Complex b(4.0f, -2.0f);
	Complex result = a * b;
	EXPECT_FLOAT_EQ(result.getReal(), 14.0f);
	EXPECT_FLOAT_EQ(result.getImaginary(), 8.0f);
}

//Деление
TEST(ComplexTest, Division) {
	Complex a(2.0, 3.0);
	Complex b(4.0, -2.0);
	Complex result = a / b;
	EXPECT_NEAR(result.getReal(), 0.2, 0.1);
	EXPECT_NEAR(result.getImaginary(), 1.4, 1);
}

//Сравнение 2х чисел для Комплексных
TEST(ComplexTest, ComparisonOperators) {
	Complex c1(3.0, 4.0);
	Complex c2(5.0, 12.0);
	Complex c3(3.0, 4.0);

	EXPECT_TRUE(c1 < c2);
	EXPECT_FALSE(c1 > c2);
	EXPECT_TRUE(c1 == c3);
	EXPECT_TRUE(c1 != c2);
}

//Возведение в степень
TEST(ComplexTest, Exponentiation) {
	Complex a(2.0f, 3.0f);

	Complex powResult = a ^ 3;

	EXPECT_FLOAT_EQ(powResult.getReal(), -46.0);
	EXPECT_FLOAT_EQ(powResult.getImaginary(), 9.0);
}

//Модуль
TEST(ComplexNumberTest, Magnitude) {
	Complex a(2.0f, 3.0f);
	Complex b(4.0f, -2.0f);

	EXPECT_NEAR(a.lenght(), 3.605, 0.001);
	EXPECT_NEAR(b.lenght(), 4.472, 0.001);
}
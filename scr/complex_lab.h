#pragma once

#include <iostream>
#include <cmath>
#include <type_traits>

template<typename T>
class Complex {
private:
    T real;
    T imaginary;
public:
    Complex(T r = T(0), T i = T(0));

    Complex operator+(const Complex& other) const;

    Complex operator-(const Complex& other) const;

    Complex operator*(const Complex& other) const;

    Complex operator/(const Complex& other) const;

    Complex operator^(double power) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Complex<U>& obj);

    bool operator<(const Complex& other) const;

    bool operator>(const Complex& other) const;

    bool operator==(const Complex& other) const;

    bool operator!=(const Complex& other) const;

    bool operator<(T other) const;

    bool operator>(T other) const;

    bool operator==(T other) const;

    bool operator!=(T other) const;

    T lenght() const;

    T getReal() const;

    T getImaginary() const;

    void setReal(T r);

    void setImaginary(T i);
};

template<typename T>
Complex<T>::Complex(T r, T i) : real(r), imaginary(i)
{
    static_assert(std::is_arithmetic<T>::value, "T must be numeric type");
}

template<typename T>
Complex<T> Complex<T>::operator+(const Complex& other) const
{
    Complex result;

    result.real = this->real + other.real;
    result.imaginary = this->imaginary + other.imaginary;

    return result;
}

template<typename T>
Complex<T> Complex<T>::operator-(const Complex& other) const
{
    Complex result;

    result.real = this->real - other.real;
    result.imaginary = this->imaginary - other.imaginary;

    return result;
}

template<typename T>
Complex<T> Complex<T>::operator*(const Complex& other) const
{
    Complex result;

    result.real = this->real * other.real - this->imaginary * other.imaginary;
    result.imaginary = this->real * other.imaginary + other.real * this->imaginary;

    return result;
}

template<typename T>
Complex<T> Complex<T>::operator/(const Complex& other) const
{
    const T zero = T(0);

    if (other.real == zero && other.imaginary == zero) {
        throw std::runtime_error("Division by zero is not allowed");
    }

    T divisor = other.real * other.real + other.imaginary * other.imaginary;

    T newReal = (real * other.real + imaginary * other.imaginary) / divisor;
    T newImaginary = (imaginary * other.real - real * other.imaginary) / divisor;

    return Complex<T>(newReal, newImaginary);
}

template<typename T>
Complex<T> Complex<T>::operator^(double power) const
{
    double magnitude = std::pow(std::sqrt(real * real + imaginary * imaginary), power);
    double angle = std::atan2(imaginary, real) * power;

    return Complex(magnitude * std::cos(angle), magnitude * std::sin(angle));
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Complex<T>& obj)
{
    os << "Complex(" << obj.real << "f, " << obj.imaginary << "f)";

    return os;
}

template<typename T>
bool Complex<T>::operator<(const Complex& other) const
{
    return this->lenght() < other.lenght();
}

template<typename T>
bool Complex<T>::operator>(const Complex& other) const
{
    return this->lenght() > other.lenght();
}

template<typename T>
bool Complex<T>::operator==(const Complex& other) const
{
    return this->lenght() == other.lenght();
}

template<typename T>
bool Complex<T>::operator!=(const Complex& other) const
{
    return this->lenght() != other.lenght();
}

template<typename T>
bool Complex<T>::operator<(T other) const
{
    return this->lenght() < other;
}

template<typename T>
bool Complex<T>::operator>(T other) const
{
    return this->lenght() > other;
}

template<typename T>
bool Complex<T>::operator==(T other) const
{
    return this->lenght() == other;
}

template<typename T>
bool Complex<T>::operator!=(T other) const
{
    return this->lenght() != other;
}

template<typename T>
T Complex<T>::lenght() const
{
    return sqrt(pow(this->getReal(), 2) + pow(this->getImaginary(), 2));
}

template<typename T>
T Complex<T>::getReal() const
{
    return real;
}

template<typename T>
T Complex<T>::getImaginary() const
{
    return imaginary;
}

template<typename T>
void Complex<T>::setReal(T r)
{
    this->real = r;
}

template<typename T>
void Complex<T>::setImaginary(T i)
{
    this->imaginary = i;
}
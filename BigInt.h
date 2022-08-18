#pragma once
#include <iostream>

#define string std::string
#define ll long long

class BigInt {
private:
    string digits;
    void removeZeroes();
public:
    // constructors

    BigInt(string);
    BigInt(unsigned ll n=0);
    BigInt(const BigInt&);

    // operators

    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    friend std::istream& operator>>(std::istream&, BigInt&);
    BigInt& operator=(const BigInt&);

    BigInt& operator+=(BigInt);
    BigInt operator+(const BigInt&) const;
    void operator++();
    void operator++(int);

    BigInt& operator-=(BigInt);
    BigInt operator-(const BigInt&) const;
    void operator--();
    void operator--(int);

    BigInt& operator*=(const BigInt&);
    BigInt operator*(const BigInt&) const;

    BigInt& operator/=(const BigInt&);
    BigInt operator/(const BigInt&) const;

    BigInt& operator^=(const BigInt&);
    BigInt operator^(const BigInt&) const;

    BigInt& operator%=(const BigInt&);
    BigInt operator%(const BigInt&) const;

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator<=(const BigInt&) const;

    char operator[](const int&) const;

    // Fuctions

    int Length() const;
};

BigInt factorial(int);
BigInt sqrt(const BigInt&);
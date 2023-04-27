//https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/
#include "Fraction.hpp"

using namespace ariel;
using std::endl;


Fraction::Fraction(const int& numerator, const int& denominator)
{
    if(0 == denominator)
    {
        throw "ERROR: denominator can't be zero!";
    }

    _numerator = numerator;
    _denominator = denominator;
}


void Fraction::recude()
{
    int max = std::max(_numerator, _denominator);
    int quotient = 0;

    for(int i = 2; i <= max; i++)
    {
        while(_numerator % i == 0 && _denominator % i == 0)
        {
            _numerator /= i;
            _denominator /= i;
        }
    }
}


Fraction Fraction::fractionFromFloat(float value)
{
    int denominator = 1000;
    value *= 1000;

    Fraction f(value, denominator);
    f.recude();
    return f;
}


int Fraction::numerator() const
{
    return _numerator;   
}


int Fraction::denominator() const
{
    return _denominator;
}


Fraction ariel::operator+(const Fraction& frac1, const Fraction& frac2)
{
    int newNumorator = frac1._numerator * frac2._denominator + frac2._numerator * frac1._denominator;
    int newDenominator = frac1._denominator * frac2._denominator;
    
    // create the reduced form
    Fraction newFraction(newNumorator, newDenominator);
    newFraction.recude();

    return newFraction;
}


Fraction ariel::operator+(const Fraction& fraction, const float& value)
{
    return fraction + Fraction::fractionFromFloat(value);
}


Fraction ariel::operator+(const float& value, const Fraction& fraction)
{
    return  fraction + value;
}


Fraction ariel::operator-(const Fraction& frac1, const Fraction& frac2)
{
    int newNumorator = frac1._numerator * frac2._denominator - frac2._numerator * frac1._denominator;
    int newDenominator = frac1._denominator * frac2._denominator;
    
    // create the reduced form
    Fraction newFraction(newNumorator, newDenominator);
    newFraction.recude();

    return newFraction;
}


Fraction ariel::operator-(const Fraction& fraction, const float& value)
{
    return fraction - Fraction::fractionFromFloat(value);
}


Fraction ariel::operator-(const float& value, const Fraction& fraction)
{
    return  Fraction::fractionFromFloat(value) - fraction;
}


Fraction ariel::operator*(const Fraction& frac1, const Fraction& frac2)
{
    int newNumorator = frac1._numerator * frac2._numerator;
    int newDenominator = frac1._denominator * frac2._denominator;
    
    // create the reduced form
    Fraction newFraction(newNumorator, newDenominator);
    newFraction.recude();

    return newFraction;
}


Fraction ariel::operator*(const Fraction& fraction, const float& value)
{
    return fraction * Fraction::fractionFromFloat(value);
}


Fraction ariel::operator*(const float& value, const Fraction& fraction)
{
    return  fraction * value;
}


Fraction ariel::operator/(const Fraction& frac1, const Fraction& frac2)
{
    if(frac2._numerator == 0)
    {
        throw "Error: can't divide by zero!";
    }

    return frac1 * Fraction(frac2._denominator, frac2._numerator);
}


Fraction ariel::operator/(const Fraction& fraction, const float& value)
{
    return fraction / Fraction::fractionFromFloat(value);
}


Fraction ariel::operator/(const float& value, const Fraction& fraction)
{
    return  Fraction::fractionFromFloat(value) / fraction;
}


bool ariel::operator==(const Fraction& frac1, const Fraction& frac2)
{
    Fraction reducedLeft(frac1._numerator, frac1._denominator);
    reducedLeft.recude();

    Fraction reducedRight(frac2._numerator, frac2._denominator);
    reducedRight.recude();

    return reducedLeft._numerator == reducedRight._numerator && 
        reducedLeft._denominator == reducedRight._denominator;
}


bool ariel::operator==(const Fraction& fraction, const float& value)
{
    return fraction == Fraction::fractionFromFloat(value);
}


bool ariel::operator==(const float& value, const Fraction& fraction)
{
    return fraction == value;
}


bool ariel::operator<(const Fraction& frac1, const Fraction& frac2)
{
     return frac1._numerator * frac2._denominator < frac1._denominator * frac2._numerator;
}


bool ariel::operator<(const Fraction& fraction, const float& value)
{
     return fraction < Fraction::fractionFromFloat(value);
}


bool ariel::operator<(const float& value, const Fraction& fraction)
{
     return Fraction::fractionFromFloat(value) < fraction;
}


bool ariel::operator>(const Fraction& frac1, const Fraction& frac2)
{
     return frac1._numerator * frac2._denominator > frac1._denominator * frac2._numerator;
}


bool ariel::operator>(const Fraction& fraction, const float& value)
{
     return fraction > Fraction::fractionFromFloat(value);
}


bool ariel::operator>(const float& value, const Fraction& fraction)
{
     return Fraction::fractionFromFloat(value) > fraction;
}


bool ariel::operator<=(const Fraction& frac1, const Fraction& frac2)
{
    return frac1 < frac2 || frac1 == frac2;
}


bool ariel::operator<=(const Fraction& fraction, const float& value)
{
    return fraction <= Fraction::fractionFromFloat(value);
}


bool ariel::operator<=(const float& value, const Fraction& fraction)
{
    return Fraction::fractionFromFloat(value) <= fraction;
}


bool ariel::operator>=(const Fraction& frac1, const Fraction& frac2)
{
    return frac1 > frac2 || frac1 == frac2;
}


bool ariel::operator>=(const Fraction& fraction, const float& value)
{
    return fraction >= Fraction::fractionFromFloat(value);
}


bool ariel::operator>=(const float& value, const Fraction& fraction)
{
    return Fraction::fractionFromFloat(value) >= fraction;
}


Fraction& ariel::operator++(Fraction& fraction)
{
    fraction._numerator += fraction._denominator;
    return fraction;
}


Fraction& ariel::operator++(Fraction& fraction, int)
{
    fraction._numerator += fraction._denominator;
    return fraction;
}


Fraction& ariel::operator--(Fraction& fraction)
{
    fraction._numerator -= fraction._denominator;
    return fraction;
}


Fraction& ariel::operator--(Fraction& fraction, int)
{
    fraction._numerator -= fraction._denominator;
    return fraction;
}


ostream& ariel::operator<<(ostream& output, const Fraction& fraction)
{
    return output << fraction._numerator << "/" << fraction._denominator;
}


istream& ariel::operator>>(istream& input, Fraction& fraction)
{
    return input >> fraction._numerator >> fraction._denominator;
}

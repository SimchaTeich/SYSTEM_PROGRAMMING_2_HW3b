//https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/
#include "Fraction.hpp"
#include <limits.h>

using namespace ariel;
using std::endl;


Fraction::Fraction(const int& numerator, const int& denominator)
{
    if(0 == denominator)
    {
        throw std::invalid_argument("ERROR: denominator can't be zero!");
    }

    _isNegative = (numerator < 0 && denominator > 0) || (numerator >=0 && denominator < 0);

    _numerator = numerator;
    _denominator = denominator;

    recude();
}


Fraction::Fraction(const float& num)
{
    Fraction fruction = Fraction::fractionFromFloat(num);

    _isNegative = num < 0;
    _numerator = fruction.getNumerator();
    _denominator = fruction.getDenominator();
    
}


Fraction::Fraction()
{
    Fraction fruction = Fraction::fractionFromFloat(0);
    
    _isNegative = false;
    _numerator = fruction.getNumerator();
    _denominator = fruction.getDenominator();
}


void Fraction::recude()
{
    if(_numerator == 0)
    {
        _denominator = 1;
        _isNegative = false;
    }
    
    // just numerator will be negative.
    if(_isNegative)
    {
        _numerator = -std::abs(_numerator);
        _denominator = std::abs(_denominator);
    }
    else // no minus in numerator and denumerator
    {
        _numerator = std::abs(_numerator);
        _denominator = std::abs(_denominator);
    }
    
    if(std::abs(_numerator) == std::abs(_denominator))
    {
        _numerator = _isNegative ? -1 : 1;
        _denominator = 1;
    }
    else
    {
        int min = std::min(std::abs(_numerator), std::abs(_denominator));

        for(int i = 2; i <= min; i++)
        {
            while(_numerator % i == 0 && _denominator % i == 0)
            {
                _numerator /= i;
                _denominator /= i;
            }
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


int Fraction::getNumerator() const
{
    return _numerator;   
}


int Fraction::getDenominator() const
{
    return _denominator;
}


Fraction ariel::operator+(const Fraction& frac1, const Fraction& frac2)
{
    //https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-overflow
    double d1 = (double)frac1._numerator/frac1._denominator;
    double d2 = (double)frac2._numerator/frac2._denominator;
    if ((d2 > 0 && d1 > INT_MAX - d2) || (d2 < 0 && d1 < INT_MIN - d2))
    {
        throw std::overflow_error("Error: overflow in operator+");
    }

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
    //https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-overflow
    double d1 = (double)frac1._numerator/frac1._denominator;
    double d2 = (double)frac2._numerator/frac2._denominator;
    if ((d2 < 0 && d1 > INT_MAX + d2) || (d2 > 0 && d1 < INT_MIN + d2))
    {
        throw std::overflow_error("Error: overflow in operator-");
    }

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
    //https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-overflow
    int n1 = frac1._numerator;
    int d1 = frac1._denominator;
    int n2 = frac2._numerator;
    int d2 = frac2._denominator; 
    if((n1 != 0 && n1*n2 / n1 != n2) || (d1 != 0 && d1*d2 / d1 != d2))
    {
        throw std::overflow_error("Error: overflow in operator*");
    }

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
        throw std::runtime_error("Error: can't divide by zero!");
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
    Fraction afterFloat1((double)frac1._numerator/frac1._denominator);
    Fraction afterFloat2((double)frac2._numerator/frac2._denominator);

    return afterFloat1._numerator == afterFloat2._numerator &&
        afterFloat1._denominator == afterFloat2._denominator;
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


Fraction ariel::operator++(Fraction& fraction, int)
{
   Fraction temp = fraction;
    fraction._numerator += fraction._denominator;
    return temp;
}


Fraction& ariel::operator--(Fraction& fraction)
{
    fraction._numerator -= fraction._denominator;
    return fraction;
}


Fraction ariel::operator--(Fraction& fraction, int)
{
    Fraction temp = fraction;
    fraction._numerator -= fraction._denominator;
    return temp;
}


ostream& ariel::operator<<(ostream& output, const Fraction& fraction)
{
    return output << fraction._numerator << "/" << fraction._denominator;
}


istream& ariel::operator>>(istream& input, Fraction& fraction)
{
    fraction._numerator = 0;
    fraction._denominator = 0;
    input >> fraction._numerator >> fraction._denominator;

    if(fraction._denominator == 0)
    {
        throw std::runtime_error("Error: >> needs two parameters..");
    }

    fraction._isNegative = (fraction._numerator < 0 && fraction._denominator > 0) ||
                           (fraction._numerator >= 0 && fraction._denominator < 0);
    fraction.recude();

    return input;
}

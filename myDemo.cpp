#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

using std::cerr;
using std::cout;
using std::endl;
using std::string;

#include "sources/Fraction.hpp"

using namespace ariel;

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cout << argc;
        cerr << "usage: <number> <oparation> <number>" << endl;
        return 1;
    }

    Fraction f1(std::stof(argv[1]));
    Fraction f2(std::stof(argv[3]));
    Fraction *resultFraction = nullptr;
    bool resultBool = false;

    if(string(argv[2]) == "+")
    {
        resultFraction = new Fraction(f1 + f2);
    }
    else if(string(argv[2]) == "-")
    {
        resultFraction = new Fraction(f1 - f2);
    }
    else if(string(argv[2]) == "x")
    {
        resultFraction = new Fraction(f1 * f2);
    }
    else if(string(argv[2]) == "/")
    {
        resultFraction = new Fraction(f1 / f2);
    }
    else if(string(argv[2]) == "s")
    {
        resultBool = f1 < f2;
    }
    else if(string(argv[2]) == "se")
    {
        resultBool = f1 <= f2;
    }
    else if(string(argv[2]) == "b")
    {
        resultBool = f1 > f2;
    }
    else if(string(argv[2]) == "be")
    {
        resultBool = f1 >= f2;
    }
    else
    {
        cerr << "somthing go wrong." << endl;
        return 1;
    }


    cout << f1 << " " << argv[2] << " " << f2 << endl;
    cout << "result: " << (resultFraction ? *resultFraction : resultBool) << endl;

    if(resultFraction)
    {
        delete resultFraction;
        resultFraction = nullptr;
    }

    return 0;
}
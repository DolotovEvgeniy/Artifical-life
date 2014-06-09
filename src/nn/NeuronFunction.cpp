#include <vector>
#include <math.h>
#include <iostream>
using namespace std;
double linear(double value, std::vector<double> params)
{
    double a = params[0];
    double b = params[1];
    return (a * value) + b;
}
double	sign(double value, std::vector<double> params)
{
    double a = params[0];
    if (value > a)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double	sigma (double value, std::vector<double> params)
{
    double a = params[0];
    double b = params[1];
    double c = params[2];
    return a / (b + exp(-value * c) + 1);
}

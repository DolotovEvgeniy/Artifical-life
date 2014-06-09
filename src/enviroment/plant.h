#ifndef PLANT_H_INCLUDED
#define PLANT_H_INCLUDED
#include <cstdlib>
#define plantage 100
class Plant
{
public:
    double x;
    double y;
    int age;
public:
    Plant()
    {
        x=rand()%40;
        y=rand()%40;
    }
    Plant(double x,double y)
    {
        this->x=x;
        this->y=y;
        age=110;
    }

};


#endif // PLANT_H_INCLUDED

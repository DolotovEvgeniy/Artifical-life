#ifndef HERBIVORE_H_INCLUDED
#define HERBIVORE_H_INCLUDED
#include "agent.h"
class Herbivore:public Agent
{
public:
    Herbivore(double x,double y,double angle,double speed):Agent(x,y,angle,speed)
    {
        this->x=x;
        this->y=y;
        this->angle=angle;
        this->speed=speed;
        this->score=0;
        energy=300;
    }
    Herbivore(const Herbivore& herb)
    {
        this->x=herb.x;
        this->y=herb.y;
        this->angle=herb.angle;
        this->speed=herb.speed;
        this->score=herb.score;
        brain=herb.brain;
        energy=herb.energy;
    }
    Herbivore& operator=(const Herbivore& herb)
    {
        this->x=herb.x;
        this->y=herb.y;
        this->angle=herb.angle;
        this->speed=herb.speed;
        this->score=herb.score;
        brain=herb.brain;
        energy=herb.energy;
        return *(this);
    }
};


#endif // HERBIVORE_H_INCLUDED

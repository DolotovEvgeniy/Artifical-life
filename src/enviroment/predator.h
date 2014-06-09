#ifndef PREDATOR_H_INCLUDED
#define PREDATOR_H_INCLUDED
#include "agent.h"
class Predator:public Agent
{
public:
    Predator()
    {
        energy=1000;
    }
    Predator(double x,double y,double angle,double speed):Agent(x,y,angle,speed)
    {
        this->x=x;
        this->y=y;
        this->angle=angle;
        this->speed=speed;
        this->score=0;
        this->energy=300;
    }
    Predator(const Predator& pred)
    {
        this->x=pred.x;
        this->y=pred.y;
        this->angle=pred.angle;
        this->speed=pred.speed;
        this->score=pred.score;
        brain=pred.brain;
        energy=pred.energy;
    }
    Predator operator=(const Predator& pred)
    {
        this->x=pred.x;
        this->y=pred.y;
        this->angle=pred.angle;
        this->speed=pred.speed;
        this->score=pred.score;
        brain=pred.brain;
        energy=pred.energy;
        return *(this);
    }
};


#endif // PREDATOR_H_INCLUDED

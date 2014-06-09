#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../nn/NeuralNetwork.h"
#define plusinf 0x7FF0000000000000
#define mininf 0xFFF0000000000000
int energy_flag=0;
float max_speed=0.5;
bool IsNanOrInf(double v)
{
    if(v!=v||v==plusinf || v==mininf)
    {
        return true;
    }
    return false;
}
class Agent
{
public:
    double x;
    double y;
    double speed;
    double angle;
    double old;
    int score;
    double energy;
    NeuralNetwork brain;
    double signals[10];
    Agent(double x,double y,double angle,double speed)
    {
        this->x=x;
        this->y=y;
        this->angle=angle;
        this->speed=speed;
        energy=50;
    }
    Agent()
    {
    }
    void NormalizeSpeedAndAngle()
    {
        if(IsNanOrInf(angle))
        {
            this->angle=3;
        }
        if(IsNanOrInf(speed))
        {
            this->speed=0.6;
        }
        if(this->angle>100000000||this->angle<=-100000000)
        {
            this->angle=0;
        }
        if(speed>=100000000||speed<=-100000000)
        {
            this->speed=0.7;
        }
        if(abs(speed)>0.7)
        {
            speed=speed-0.7*(long)(speed/0.7);
        }
        if(abs(angle)>3.14)
        {
            angle=angle-3.14*(long)(angle/3.14);
        }
    }
    void step()
    {
        std::vector<double> out;
        out=brain.ActivateNetwork(signals);
        speed+=out[1];
        angle+=out[0];
        this->NormalizeSpeedAndAngle();
        if(energy>0&&energy_flag)
            energy-=0.5;
        return;
    }
};
#endif // AGENT_H_INCLUDED

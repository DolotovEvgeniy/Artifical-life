#ifndef NEURON_H_INCLUDED
#define NEURON_H_INCLUDED
#include <vector>
#include "NeuronFunction.h"
#include <stdlib.h>
class Neuron
{
public:
    double inputSignal;
    double afterActivationSignal;
    std::vector<double> params;
    double (*NeuronFunction)(double value, std::vector<double> params);
    double activate()
    {
        return NeuronFunction(this->inputSignal,this->params);
    }
    Neuron()
    {
        double x;

        for (int i=0; i<3; i++)
        {
            x = rand()%2;
            params.push_back(x);
        }
        inputSignal=0;
        afterActivationSignal=0;
        int y=rand()%3;
        if(y==0)
        {
            NeuronFunction=linear;

        }
        if(y==1)
        {
            NeuronFunction=sign;
        }
        if(y==2)
        {
            NeuronFunction=sigma ;
        }
    }
    Neuron(const Neuron& neuron)
    {
        params=neuron.params;
        inputSignal=neuron.inputSignal;
        afterActivationSignal=neuron.afterActivationSignal;
        NeuronFunction=neuron.NeuronFunction;
    }
    Neuron operator=(const Neuron& neuron)
    {
        params=neuron.params;
        inputSignal=neuron.inputSignal;
        afterActivationSignal=neuron.afterActivationSignal;
        NeuronFunction=neuron.NeuronFunction;
        return *(this);
    }
};
#endif // NEURON_H_INCLUDED

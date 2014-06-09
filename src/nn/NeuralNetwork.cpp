#include "NeuralNetwork.h"
#include <vector>
#include <iostream>
#include "constant.h"
using namespace std;
std::vector<double> NeuralNetwork::ActivateNetwork(double params[inputlayer])
{
    for(int i=0; i<(inputlayer+hidelayer+outlayer); i++)
    {
        neurons[i].inputSignal=0;
    }
    for(int i=0; i<inputlayer; i++)
    {
        neurons[i].inputSignal=params[i];
    }
    for(int i=0; i<inputlayer; i++)
    {
        neurons[i].afterActivationSignal=neurons[i].activate();
    }
    for(int i=0; i<inputlayer; i++)
    {

        for(unsigned int j=0; j<hidelayer; j++)
        {

            neurons[inputlayer+j].inputSignal+=neurons[i].afterActivationSignal*neuronsLinks.links[i*hidelayer+j];

        }

    }
    for(unsigned int j=inputlayer; j<(inputlayer+hidelayer); j++)
    {

        neurons[j].afterActivationSignal=neurons[j].activate();

    }
    for(int i=inputlayer; i<(inputlayer+hidelayer); i++)
    {
        for(unsigned int j=0; j<outlayer; j++)
        {
            neurons[inputlayer+hidelayer+j].inputSignal+=neurons[i].afterActivationSignal*neuronsLinks.links[inputlayer*hidelayer+i*outlayer+j];
        }
    }
    for(unsigned int j=(inputlayer+hidelayer); j<(inputlayer+hidelayer+outlayer); j++)
    {
        neurons[j].afterActivationSignal=neurons[j].activate();
    }
    std::vector<double> out;
    out.push_back(neurons[inputlayer+hidelayer+outlayer-2].afterActivationSignal);
    out.push_back(neurons[inputlayer+hidelayer+outlayer-1].afterActivationSignal);
    return out;
}

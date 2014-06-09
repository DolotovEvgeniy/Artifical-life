#ifndef NEURALNETWORK_H_INCLUDED
#define NEURALNETWORK_H_INCLUDED
#include "Neuron.h"
#include <vector>
#include "Links.h"
#include "constant.h"

class NeuralNetwork
{
public:
    std::vector<Neuron> neurons;
    Links neuronsLinks;
    std::vector<double> ActivateNetwork(double params[inputlayer]);
    NeuralNetwork()
    {
        for(int i=0; i<inputlayer*hidelayer+hidelayer*outlayer; i++)
        {
            neuronsLinks.links.push_back((static_cast<double>(rand()) / RAND_MAX)*4-2);
        }
        for(int i=0; i<(inputlayer+hidelayer+outlayer); i++)
        {
            Neuron newNeuron;
            neurons.push_back(newNeuron);
        }
    }
    NeuralNetwork(const NeuralNetwork& network)
    {
        neurons=network.neurons;
        neuronsLinks=network.neuronsLinks;
    }
    NeuralNetwork operator=(NeuralNetwork network)
    {
        this->neurons=network.neurons;
        this->neuronsLinks=network.neuronsLinks;
        return *(this);
    }



};
NeuralNetwork geneticevolve(NeuralNetwork&,NeuralNetwork&);
#endif // NEURALNETWORK_H_INCLUDED

#ifndef GENETICALGORITHM_H_INCLUDED
#define GENETICALGORITHM_H_INCLUDED
#include "../NeuralNetwork.h"
#include <vector>
#include <stdlib.h>
using namespace std;
bool contained(vector<int>& myvec,int number)
{
    int sizevec=myvec.size();
    for(int i=0; i<sizevec;i++)
    {
        if(myvec[i]==number)
        {
            return true;
        }
    }
    return false;
}
void shuffle(vector<double>& myvec)
{
    int sizevec=myvec.size();
    vector<int> used;
    for(int i=0; i<sizevec; i++)
    {
        double tmp=myvec[i];
        int random=rand()%sizevec;
        while(contained(used,random))
        {
            random=rand()%sizevec;
        }
        myvec[i]=myvec[random];
        myvec[random]=tmp;
        used.push_back(random);

    }
}

vector<Links> twoPointsWeightsCrossover(Links first, Links second)
{
    int left=rand()%first.links.size();
    int right=rand()%first.links.size();
    if (left > right)
    {
        int tmp = right;
        right = left;
        left = tmp;
    }
    for (int i = left; i < right; i++)
    {
        double link = second.links[i];
        second.links[i]=first.links[i];
        first.links[i]=link;
    }
    vector<Links> children;
    children.push_back(second);
    children.push_back(first);
    return children;
}

vector<Links> uniformelyDistributedWeightsCrossover(Links first, Links second)
{
    int linksize = first.links.size();
    int itersCount = rand()%linksize;
    if (itersCount == 0)
    {
        itersCount = 1;
    }
    vector<int> used;
    for (int iter = 0; iter < itersCount; iter++)
    {
        int i =rand()%linksize;
        while (contained(used,i))
        {
            i =rand()%linksize;
        }
        double firstlink = first.links[i];
        double secondlink = second.links[i];
        first.links[i]=secondlink;
        second.links[i]=firstlink;
        used.push_back(i);
    }
    vector<Links> children;
    children.push_back(second);
    children.push_back(first);
    return children;
}

vector<NeuralNetwork> twoPointsNeuronsCrossover(NeuralNetwork first,NeuralNetwork second)
{
    int left = rand()%first.neurons.size();
    int right = rand()%first.neurons.size();
    if (left > right)
    {
        int tmp = right;
        right = left;
        left = tmp;
    }
    for (int i = left; i < right; i++)
    {
        Neuron neuron = first.neurons[i];
        first.neurons[i]=second.neurons[i];
        second.neurons[i]=neuron;
    }
    vector<NeuralNetwork> children;
    children.push_back(second);
    children.push_back(first);
    return children;
}

vector<NeuralNetwork> uniformelyDistributedNeuronsCrossover(NeuralNetwork first,NeuralNetwork second)
{
    int neuronsSize = first.neurons.size();
    int itersCount = rand()%neuronsSize;
    if (itersCount == 0)
    {
        itersCount = 1;
    }
    vector<int> used;
    for (int iter = 0; iter < itersCount; iter++)
    {
        int i =rand()%neuronsSize;
        while (contained(used,i))
        {
            i = rand()%neuronsSize;
        }

        Neuron neuron = first.neurons[i];
        first.neurons[i]=second.neurons[i];
        second.neurons[i]=neuron;
        used.push_back(i);
    }
    vector<NeuralNetwork> children;
    children.push_back(second);
    children.push_back(first);
    return children;
}

Links mutateWeights(Links links)
{
    int linksize = links.links.size();
    int itersCount = rand()%linksize;
    if (itersCount == 0)
    {
        itersCount = 1;
    }
    vector<int> used;
    for (int iter = 0; iter < itersCount; iter++)
    {
        int i =rand()%linksize;
        while (contained(used,i))
        {
            i =rand()%linksize;
        }

        double link = links.links[i];
        link += (static_cast<double>(rand()) / RAND_MAX)-(static_cast<double>(rand()) / RAND_MAX);
        links.links[i]=link;
        used.push_back(i);
    }
    return links;
}

NeuralNetwork mutateNeuronsFunctionsParams(NeuralNetwork network)
{
    int neuronsSize = network.neurons.size();
    int itersCount = rand()%neuronsSize;
    if (itersCount == 0)
    {
        itersCount = 1;
    }
    vector<int> used;
    for (int iter = 0; iter < itersCount; iter++)
    {
        int i =rand()%neuronsSize;
        while (contained(used,i))
        {
            i =rand()%neuronsSize;
        }
        Neuron neuron = network.neurons[i];

        vector<double> params = neuron.params;
        for (unsigned int j = 0; j < params.size(); j++)
        {
            double param = params[j];
            param += (static_cast<double>(rand()) / RAND_MAX)-(static_cast<double>(rand()) / RAND_MAX);
            params[j]=param;
        }
        neuron.params=params;
        network.neurons[i]=neuron;
        used.push_back(i);
    }
    return network;
}

NeuralNetwork mutateChangeNeuronsFunctions(NeuralNetwork network)
{
    int neuronsSize = network.neurons.size();
    int itersCount = rand()%neuronsSize;
    if (itersCount == 0)
    {
        itersCount = 1;
    }
    vector<int> used;
    for (int iter = 0; iter < itersCount; iter++)
    {
        int i =rand()%neuronsSize;
        while (contained(used,i))
        {
            i =rand()%neuronsSize;
        }
        int y=rand()%3;
        if(y==0)
        {
            network.neurons[i].NeuronFunction=linear;
        }
        if(y==1)
        {
            network.neurons[i].NeuronFunction=sign;
        }
        if(y==2)
        {
            network.neurons[i].NeuronFunction=sigma ;
        }
        used.push_back(i);
    }

return network;
}

Links shuffleWeightsOnSubinterval(Links link)
{
		int left = rand()%link.links.size();
		int right = rand()%link.links.size();
		if (left > right) {
			int tmp = right;
			right = left;
			left = tmp;
		}
		vector<double> tmp;
		for (int i = 0; i < ((right - left) + 1); i++) {
			tmp.push_back(link.links[left + i]);
		}
		shuffle(tmp);
		for (int i = 0; i < ((right - left) + 1); i++) {
			link.links[left + i]=tmp[i];
		}
		return link;
	}


NeuralNetwork mutate(NeuralNetwork network)
{
    NeuralNetwork mutated=network;
int choice=rand()%4;
    switch (choice)
    {
    case 0:
        mutated.neuronsLinks=mutateWeights(mutated.neuronsLinks);
        break;
    case 1:
        mutated=mutateNeuronsFunctionsParams(mutated);
        break;
    case 2:
        mutated=mutateChangeNeuronsFunctions(mutated);
        break;
    case 3:
        mutated.neuronsLinks=shuffleWeightsOnSubinterval(mutated.neuronsLinks);
    break;
    }

    return mutated;
}


vector<NeuralNetwork> crossover(NeuralNetwork first,NeuralNetwork second)
{
    NeuralNetwork firstchild=first;
    NeuralNetwork secondchild=second;
    int choice=rand()%4;
    switch (choice)
    {
    case 0:
        {

        vector<Links> childlinks=twoPointsWeightsCrossover(first.neuronsLinks,second.neuronsLinks);
        firstchild.neuronsLinks=childlinks[0];
        secondchild.neuronsLinks=childlinks[1];
        }
        break;
    case 1:
        {
        vector<Links> childlinks=uniformelyDistributedWeightsCrossover(first.neuronsLinks,second.neuronsLinks);
        firstchild.neuronsLinks=childlinks[0];
        secondchild.neuronsLinks=childlinks[1];
        }
    break;
    case 2:
    {
        vector<NeuralNetwork> children=twoPointsNeuronsCrossover(first,second);
        firstchild=children[0];
        secondchild=children[1];
    }
    break;
    case 3:
        {
        vector<NeuralNetwork> children=uniformelyDistributedNeuronsCrossover(first,second);
        firstchild=children[0];
        secondchild=children[1];
        }
    break;
    }
    vector<NeuralNetwork> ret;
    ret.push_back(firstchild);
    ret.push_back(secondchild);
    ret.push_back(mutate(firstchild));
    ret.push_back(mutate(secondchild));
    return ret;
}
#endif // GENETICALGORITHM_H_INCLUDED

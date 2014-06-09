#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED
#include "../NeuralNetwork.h"
#include <vector>
#include <algorithm>
using namespace std;
class Member
{
public:
    NeuralNetwork network;
    double fitness;
    Member()
    {
        NeuralNetwork net;
        this->network.neurons=net.neurons;
        this->network.neuronsLinks=net.neuronsLinks;
        this->fitness=0;
    }
    Member(const Member& m)
    {
        this->network.neurons=m.network.neurons;
        this->network.neuronsLinks=m.network.neuronsLinks;
        this->fitness=m.fitness;
    }
    Member operator=(Member mem)
    {
        this->network.neurons=mem.network.neurons;
        this->network.neuronsLinks=mem.network.neuronsLinks;
this->fitness=mem.fitness;
        return mem;
    }
};
    bool operator<(Member one,Member two)
    {
        return (one.fitness<two.fitness);
    }
class Population
{
public:
    vector<Member> members;
    Population cut(int length)
    {
        Population tmp;
        for(int i=0; i<length; i++)
        {
            tmp.members.push_back(this->members[i]);
        }
        return tmp;
    }
    Population()
    {
      this->members.clear();
    }
    Population(const Population& pop)
    {
        this->members.clear();
        for(int i=0;i<pop.members.size();i++)
        {
           this->members.push_back(pop.members[i]);
        }
    }
    Population operator=(Population pop)
    {
        this->members=pop.members;
        return pop;
    }
    Member getRandomMember()
    {
        return (this->members[rand()%this->members.size()]);
    }
    void sortByFitness()
    {
        std::sort(members.begin(), members.end());
    }
};


#endif // POPULATION_H_INCLUDED

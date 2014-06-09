#ifndef AGENTSENVIROMENT_H_INCLUDED
#define AGENTSENVIROMENT_H_INCLUDED
#include <fstream>
#include <vector>
#include <math.h>
#include <iostream>
#include "herbivore.h"
#include "plant.h"
#include "predator.h"
#include "../nn/genetic/GeneticAlgorithm.h"
#include "../nn/genetic/Population.h"
#define parentChromosomesSurviveCount 15
using namespace std;
inline double module(double x1,double x2,double y1,double y2)
{
    double s=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return s;
}
inline double module(double v1,double v2)
{
    double s=sqrt(v1*v1+v2*v2);
    return s;
}
inline double cosTeta(double vx1, double vy1, double vx2, double vy2)
{
    double v1 = module(vx1, vy1);
    double v2 = module(vx2, vy2);
    if (v1 == 0)
    {
        v1 = 1E-5;
    }
    if (v2 == 0)
    {
        v2 = 1E-5;
    }
    double ret = ((vx1 * vx2) + (vy1 * vy2)) / (v1 * v2);
    return ret;
}
inline double pseudoScalarProduct(double vx1, double vy1, double vx2, double vy2)
{
    return (vx1 * vy2) - (vy1 * vx2);
}

Population evolve(Population*,string,NeuralNetwork);
//Population evolve2(Population*,string);
double selection(NeuralNetwork&,string,NeuralNetwork&);
//vector<double> selectionmass(Population*,string);
class AgentsEnviroment
{
public:
    vector<Predator> predators;
    vector<Herbivore> herbivorious;
    vector<Plant> plants;
    vector<Herbivore> deadherb;
    vector<Predator> deadpred;
    int width;
    double bestherbfitness;
    double bestpredfitness;

public:
    void NewStep()
    {
        for(unsigned int i=0; i<predators.size(); i++)
        {
            predators[i].step();
        }
        for(unsigned int i=0; i<herbivorious.size(); i++)
        {
            herbivorious[i].step();
        }
        if(energy_flag)
        {
            for(unsigned int i=0; i<plants.size(); i++)
            {
                plants[i].age--;
                if(plants[i].age<=1)
                {
                    plants.erase(plants.begin()+i);
                    Plant one(rand()%width,rand()%width);
                    Plant two(rand()%width,rand()%width);
                    plants.push_back(one);
                    plants.push_back(two);
                }
            }
        }
    }
    void AgentsObserver()
    {
        double eatendist=1;
        double distance,scalartmp,scalar;
        for (unsigned int i=0; i<predators.size(); i++)
        {
            if(predators[i].energy>600&&energy_flag)
            {
                Predator pred(predators[i].x+1,predators[i].y+1,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
                pred.energy=300;
                pred.brain=mutate(predators[i].brain);
                predators[i].energy-=300;
                predators.push_back(pred);
            }
            if(predators[i].energy<=0.5)
            {
                predators.erase(predators.begin() + i);
                continue;
            }
            double goal;
            int near;
            bool found=false;
            goal=200;

            for(unsigned int j=0; j<predators.size(); j++)
            {

                distance=module(predators[i].x,predators[j].x,predators[i].y,predators[j].y);
                scalartmp=(predators[j].x-predators[i].x)*sin(predators[i].angle)+(predators[j].y-predators[i].y)*cos(predators[i].angle);

                if(distance<goal&&scalartmp>0)
                {
                    goal=distance;
                    found=true;
                    near=j;
                    scalar=scalartmp;
                }
            }
            if(found)
            {
                predators[i].signals[0]=1;
                predators[i].signals[1]=goal;
                double agentDirectionVectorX=predators[near].x-predators[i].x;
                double agentDirectionVectorY=predators[near].y-predators[i].y;
                double psp=pseudoScalarProduct(sin(predators[i].angle), cos(predators[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                double teta=cosTeta(sin(predators[i].angle), cos(predators[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                predators[i].signals[2]=psp*teta/fabs(psp);
            }
            else
            {
                predators[i].signals[0]=0;
                predators[i].signals[1]=1;
                predators[i].signals[2]=1;
            }


            found=false;
            goal=200;

            for(unsigned int j=0; j<herbivorious.size(); j++)
            {
                double distance=module(predators[i].x,herbivorious[j].x,predators[i].y,herbivorious[j].y);
                double scalar=(herbivorious[j].x-predators[i].x)*sin(predators[i].angle)+(herbivorious[j].y-predators[i].y)*cos(predators[i].angle);
                if(distance<eatendist)
                {
                    deadherb.push_back(herbivorious[j]);
                    Herbivore newagent(rand()%width,rand()%width,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
                    newagent.brain=herbivorious[j].brain;
                    herbivorious.erase(herbivorious.begin() + j);
                    herbivorious.push_back(newagent);
                    predators[i].score++;
                    if(energy_flag)
                        predators[i].energy+=60;
                    continue;
                }
                if(distance<goal&&scalar>0)
                {
                    goal=distance;
                    found=true;
                    near=j;
                }
            }
            if(found)
            {
                predators[i].signals[3]=1;
                predators[i].signals[4]=goal;
                double agentDirectionVectorX=herbivorious[near].x-predators[i].x;
                double agentDirectionVectorY=herbivorious[near].y-predators[i].y;
                double psp=pseudoScalarProduct(sin(predators[i].angle), cos(predators[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                double teta=cosTeta(sin(predators[i].angle), cos(predators[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                predators[i].signals[5]=psp*teta/fabs(psp);
                predators[i].signals[9]=near;
            }
            else
            {
                predators[i].signals[9]=-1;
                predators[i].signals[3]=0;
                predators[i].signals[4]=1;
                predators[i].signals[5]=1;

            }
            found=false;
            goal=200;

            for(unsigned int j=0; j<plants.size(); j++)
            {
                double distance=module(predators[i].x,plants[j].x,predators[i].y,plants[j].y);
                double scalar=(plants[j].x-predators[i].x)*sin(predators[i].angle)+(plants[j].y-predators[i].y)*cos(predators[i].angle);
                if(distance<goal&&scalar>0)
                {
                    goal=distance;
                    found=true;
                    near=j;
                }
            }
            if(found)
            {
                predators[i].signals[6]=1;
                predators[i].signals[7]=goal;
                double agentDirectionVectorX=plants[near].x-predators[i].x;
                double agentDirectionVectorY=plants[near].y-predators[i].y;
                double psp=pseudoScalarProduct(sin(predators[i].angle), cos(predators[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                double teta=cosTeta(sin(predators[i].angle), cos(predators[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                predators[i].signals[8]=psp*teta/fabs(psp);

            }
            else
            {
                predators[i].signals[6]=0;
                predators[i].signals[7]=1;
                predators[i].signals[8]=1;
            }
        }

        for (unsigned int i=0; i<herbivorious.size(); i++)
        {
            if(herbivorious[i].energy>750&&energy_flag)
            {
                Herbivore herb(herbivorious[i].x+1,herbivorious[i].y+1,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
                herb.energy=300;
                herb.brain=mutate(herbivorious[i].brain);
                herbivorious[i].energy-=300;
                herbivorious.push_back(herb);
            }
            if(herbivorious[i].energy<=0.5)
            {
                herbivorious.erase(herbivorious.begin() + i);
                continue;
            }
            double goal;
            int near;
            bool found=false;
            goal=200;

            for(unsigned int j=0; j<predators.size(); j++)
            {

                distance=module(herbivorious[i].x,predators[j].x,herbivorious[i].y,predators[j].y);
                scalartmp=(predators[j].x-herbivorious[i].x)*sin(herbivorious[i].angle)+(predators[j].y-herbivorious[i].y)*cos(herbivorious[i].angle);

                if(distance<goal&&scalartmp>0)
                {
                    goal=distance;
                    found=true;
                    near=j;
                    scalar=scalartmp;
                }
            }
            if(found)
            {
                herbivorious[i].signals[0]=1;
                herbivorious[i].signals[1]=goal;
                double agentDirectionVectorX=predators[near].x-herbivorious[i].x;
                double agentDirectionVectorY=predators[near].y-herbivorious[i].y;
                double psp=pseudoScalarProduct(sin(herbivorious[i].angle), cos(herbivorious[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                double teta=cosTeta(sin(herbivorious[i].angle), cos(herbivorious[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                herbivorious[i].signals[2]=psp*teta/fabs(psp);


            }
            else
            {
                herbivorious[i].signals[0]=0;
                herbivorious[i].signals[1]=1;
                herbivorious[i].signals[2]=1;
            }


            found=false;
            goal=200;

            for(unsigned int j=0; j<herbivorious.size(); j++)
            {
                double distance=module(herbivorious[i].x,herbivorious[j].x,herbivorious[i].y,herbivorious[j].y);
                double scalar=(herbivorious[j].x-herbivorious[i].x)*sin(herbivorious[i].angle)+(herbivorious[j].y-herbivorious[i].y)*cos(herbivorious[i].angle);
                if(distance<goal&&scalar>0)
                {
                    goal=distance;
                    found=true;
                    near=j;
                }
            }
            if(found)
            {
                herbivorious[i].signals[3]=1;
                herbivorious[i].signals[4]=goal;
                herbivorious[i].signals[5]=scalar/goal;
                double agentDirectionVectorX=herbivorious[near].x-herbivorious[i].x;
                double agentDirectionVectorY=herbivorious[near].y-herbivorious[i].y;
                double psp=pseudoScalarProduct(sin(herbivorious[i].angle), cos(herbivorious[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                double teta=cosTeta(sin(herbivorious[i].angle), cos(herbivorious[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                herbivorious[i].signals[5]=psp*teta/fabs(psp);

            }
            else
            {
                herbivorious[i].signals[3]=0;
                herbivorious[i].signals[4]=1;
                herbivorious[i].signals[5]=1;
            }
            found=false;
            goal=200;
            for(unsigned int j=0; j<plants.size(); j++)
            {
                double distance=module(herbivorious[i].x,plants[j].x,herbivorious[i].y,plants[j].y);
                double scalar=(plants[j].x-herbivorious[i].x)*sin(herbivorious[i].angle)+(plants[j].y-herbivorious[i].y)*cos(herbivorious[i].angle);
                if(distance<eatendist)
                {
                    plants.erase(plants.begin() + j);
                    Plant plant(rand()%width,rand()%width);
                    plants.push_back(plant);
                    herbivorious[i].score++;
                    if(energy_flag)
                        herbivorious[i].energy+=30;
                    continue;
                }
                if(distance<goal&&scalar>0)
                {
                    goal=distance;
                    found=true;
                    near=j;
                }
            }
            if(found)
            {
                herbivorious[i].signals[6]=1;
                herbivorious[i].signals[7]=goal;
                double agentDirectionVectorX=plants[near].x-herbivorious[i].x;
                double agentDirectionVectorY=plants[near].y-herbivorious[i].y;
                double psp=pseudoScalarProduct(sin(herbivorious[i].angle), cos(herbivorious[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                double teta=cosTeta(sin(herbivorious[i].angle), cos(herbivorious[i].angle), agentDirectionVectorX, agentDirectionVectorY);
                herbivorious[i].signals[8]=psp*teta/fabs(psp);
            }
            else
            {
                herbivorious[i].signals[6]=0;
                herbivorious[i].signals[7]=1;
                herbivorious[i].signals[8]=1;
            }
            herbivorious[i].signals[9]=0;
        }

    }
    void AgentsMove(int width)
    {
        int pred_size=this->predators.size();
        for(unsigned int i=0; i<pred_size; i++)
        {

            predators[i].x=predators[i].x+sin(predators[i].angle)*predators[i].speed;
            predators[i].y=predators[i].y+cos(predators[i].angle)*predators[i].speed;
            if(predators[i].x>=width||predators[i].x!=predators[i].x)
                predators[i].x=0.5;
            if(predators[i].y>=width||predators[i].y!=predators[i].y)
                predators[i].y=0.5;
            if(predators[i].x<=0)
                predators[i].x=width-0.5;
            if(predators[i].y<=0)
                predators[i].y=width-0.5;
        }
        int herb_size=this->herbivorious.size();
        for(unsigned int i=0; i<herb_size; i++)
        {

            herbivorious[i].x=herbivorious[i].x+sin(herbivorious[i].angle)*herbivorious[i].speed;
            herbivorious[i].y=herbivorious[i].y+cos(herbivorious[i].angle)*herbivorious[i].speed;
            if(herbivorious[i].x>=width||herbivorious[i].x!=herbivorious[i].x)
                herbivorious[i].x=0.5;
            if(herbivorious[i].y>=width||herbivorious[i].y!=herbivorious[i].y)
                herbivorious[i].y=0.5;
            if(herbivorious[i].x<=0)
                herbivorious[i].x=width-0.5;
            if(herbivorious[i].y<=0)
                herbivorious[i].y=width-0.5;
        }

    }

    void NewPopulation()
    {
        Population herbparents;
        int herb_size=this->herbivorious.size();
        for(int i=0; i<herb_size; i++)
        {

            Member member;
            member.network.neurons=herbivorious[i].brain.neurons;
            member.network.neuronsLinks=herbivorious[i].brain.neuronsLinks;
            herbparents.members.push_back(member);
        }
        Population herbchild=evolve(&herbparents,"herb",predators[0].brain);
        Population predparents;
        int pred_size=this->predators.size();
        for(unsigned int i=0; i<pred_size; i++)
        {
            Member member;
            member.network.neurons=predators[i].brain.neurons;
            member.network.neuronsLinks=predators[i].brain.neuronsLinks;
            predparents.members.push_back(member);
        }

        Population predchild=evolve(&predparents,"pred",herbivorious[0].brain);


        for(unsigned int i=0; i<this->predators.size(); i++)
        {
            this->predators[i].brain=predchild.members[i].network;

        }

        for(unsigned int i=0; i<this->herbivorious.size(); i++)
        {
            this->herbivorious[i].brain=herbchild.members[i].network;
        }

    }


    AgentsEnviroment()
    {

    }
    AgentsEnviroment(const AgentsEnviroment& env)
    {
        this->predators=env.predators;
        this->herbivorious=env.herbivorious;
        this->plants=env.plants;
        this->deadherb=env.deadherb;
        this->deadpred=env.deadpred;
        this->width=env.width;
        this->bestherbfitness=env.bestherbfitness;
        this->bestpredfitness=env.bestpredfitness;
    }
    AgentsEnviroment& operator=(const AgentsEnviroment& env)
    {
        this->predators=env.predators;
        this->herbivorious=env.herbivorious;
        this->plants=env.plants;
        this->deadherb=env.deadherb;
        this->deadpred=env.deadpred;
        this->width=env.width;
        this->bestherbfitness=env.bestherbfitness;
        this->bestpredfitness=env.bestpredfitness;
        return *(this);
    }
};

Population evolve(Population* parents1,string type,NeuralNetwork vrag)
{
    Population parents=*(parents1);
    Population newPopulation;
    newPopulation.members.clear();
    int parentPopulationSize=parents.members.size();
    for (int i = 0; (i < parentPopulationSize) && (i <parentChromosomesSurviveCount); i++)
    {
        newPopulation.members.push_back(parents.members[i]);
    }
    for (int i = 0; i < parentPopulationSize; i++)
    {
        Member member=parents.members[i];
        Member mutated;
        mutated.network=mutate(member.network);

        Member randmember =parents.getRandomMember();
        vector<NeuralNetwork> crossoverednet=crossover(member.network,randmember.network);
        vector<Member> crossovered;
        for(unsigned int j=0; j<crossoverednet.size(); j++)
        {
            Member newmem;
            newmem.network=crossoverednet[j];
            crossovered.push_back(newmem);
        }

        newPopulation.members.push_back(mutated);
        for (unsigned int j=0; j<crossovered.size(); j++)
        {
            newPopulation.members.push_back(crossovered[j]);
        }
    }
    for(unsigned int i=0; i<newPopulation.members.size(); i++)
    {
        newPopulation.members[i].fitness=selection(newPopulation.members[i].network,type,vrag);
    }
    newPopulation.sortByFitness();
    cout<<"Best:"<<newPopulation.members[0].fitness<<endl;
    newPopulation=newPopulation.cut(parents.members.size());
    return newPopulation;
}
double selection(NeuralNetwork& testnet,string type,NeuralNetwork& vrag)
{
    AgentsEnviroment testenv;
    testenv.width=20;
    double result;
    if(type=="pred")
    {
        for(int i=0; i<10; i++)
        {
            Predator pred(rand()%testenv.width,rand()%testenv.width,(static_cast<double>(rand()) / RAND_MAX)*4-2,(static_cast<double>(rand()) / RAND_MAX)*4-2);
            pred.brain.neurons=testnet.neurons;
            pred.brain.neuronsLinks=testnet.neuronsLinks;
            testenv.predators.push_back(pred);
        }
        for(int i=0; i<5; i++)
        {
            Herbivore herb(rand()%testenv.width,rand()%testenv.width,(static_cast<double>(rand()) / RAND_MAX)*4-2,(static_cast<double>(rand()) / RAND_MAX)*4-2);
            herb.brain=vrag;
            testenv.herbivorious.push_back(herb);
        }
    }
    if(type=="herb")
    {
        for(int i=0; i<3; i++)
        {
            Predator pred(rand()%testenv.width,rand()%testenv.width,(static_cast<double>(rand()) / RAND_MAX)*4-2,(static_cast<double>(rand()) / RAND_MAX)*4-2);
            pred.brain=vrag;
            testenv.predators.push_back(pred);
        }
        for(int i=0; i<10; i++)
        {
            Herbivore herb(rand()%testenv.width,rand()%testenv.width,(static_cast<double>(rand()) / RAND_MAX)*4-2,(static_cast<double>(rand()) / RAND_MAX)*4-2);
            herb.brain.neurons=testnet.neurons;
            herb.brain.neuronsLinks=testnet.neuronsLinks;
            testenv.herbivorious.push_back(herb);
        }
    }
    for(int i=0; i<6; i++)
    {
        Plant plant(rand()%testenv.width,rand()%testenv.width);
        testenv.plants.push_back(plant);
    }
    for(int i=0; i<50; i++)
    {
        testenv.AgentsObserver();
        testenv.NewStep();
        testenv.AgentsMove(testenv.width);
    }
    if(type=="pred")
    {
        result=0;
        for(unsigned int i=0; i<testenv.predators.size(); i++)
            result+=testenv.predators[i].score;
        result=1.0/result;
    }
    if(type=="herb")
    {
        result=0;
        for(unsigned int i=0; i<testenv.herbivorious.size(); i++)
        {
            result+=testenv.herbivorious[i].score;
        }
        for(int i=0; i<testenv.deadherb.size(); i++)
        {
            result+=testenv.deadherb[i].score;
        }
        result=1.0/result;
    }
   // cout<<result<<endl;
    return result;
}
#endif // AGENTSENVIROMENT_H_INCLUDED

#include "AgentsEnviroment.h"
#include <math.h>
#include <vector>
using namespace std;
/*double AgentsEnviroment::module(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
vector<double> AgentsEnviroment::PredatorObserver(Predator agent)
{
    vector<double> out;
    //���������� ��� �������� ��������� ��������
    Herbivore nearestherbivore;
    Plant nearestplat;
    Predator nearestpredator;
    //��� ������� �������
    vector<Herbivore> visibleherbivorous;
    vector<Predator> visiblepredators;
    vector<Plant> visibleplant;
    //���������� �� ��������
    double herbivoredistance=module(agent.x,agent.y,nearestherbivore.x,nearestherbivore.y);
    double predatordistance=module(agent.x,agent.y,nearestpredator.x,nearestpredator.y);
    double plantdistance=module(agent.x,agent.y,nearestplat.x,nearestplat.y);
    double tmpdistance;
    //��������� ������������
    double scalar;
    //���������� ������� ��������
    for (unsigned int i=0; i<this->predators.size(); i++)
    {
        scalar=cos(agent.angle)*(predators[i].x-agent.x)+sin(agent.angle)*(predators[i].y-agent.y);
        if (scalar>0)
        {
            visiblepredators.push_back(predators[i]);
        }
    }
    //���������� ������� ����������
    for (unsigned int i=0; i<this->herbivorous.size(); i++)
    {
        scalar=cos(agent.angle)*(herbivorous[i].x-agent.x)+sin(agent.angle)*(herbivorous[i].y-agent.y);
        if (scalar>0)
        {
            visibleherbivorous.push_back(herbivorous[i]);
        }
    }
    //���������� ������� ��������
    for (unsigned int i=0; i<this->plants.size(); i++)
    {
        scalar=cos(agent.angle)*(plants[i].x-agent.x)+sin(agent.angle)*(plants[i].y-agent.y);
        if (scalar>0)
        {
            visibleplant.push_back(plants[i]);
        }
    }
    //���� ���������� ������� ����� �������
    if(visiblepredators.size()>0)
    {
        nearestpredator=visiblepredators[0];
        predatordistance=module(agent.x,agent.y,visiblepredators[0].x,visiblepredators[0].y);
        for (unsigned int i=1; i<visiblepredators.size(); i++)
        {
            tmpdistance=module(agent.x,agent.y,visiblepredators[i].x,visiblepredators[i].y);
            if(predatordistance>tmpdistance )
                nearestpredator=visiblepredators[i];
        }
    }
    //���� ���������� ����������� ����� �������
    if(visibleherbivorous.size()>0)
    {
        nearestherbivore=visibleherbivorous[0];
        herbivoredistance=module(agent.x,agent.y,visibleherbivorous[0].x,visibleherbivorous[0].y);
        for (unsigned int i=1; i<visibleherbivorous.size(); i++)
        {
            tmpdistance=module(agent.x,agent.y,visibleherbivorous[i].x,visibleherbivorous[i].y);
            if(herbivoredistance>tmpdistance)
                nearestherbivore=visibleherbivorous[i];
        }
    }
    //���� ��������� �������� ����� �������
    if(visibleplant.size()>0)
    {
        nearestplat=visibleplant[0];
        plantdistance=module(agent.x,agent.y,visibleplant[0].x,visibleplant[0].y);
        for (unsigned int i=1; i<visibleplant.size(); i++)
        {
            tmpdistance=module(agent.x,agent.y,visibleplant[i].x,visibleplant[i].y);
            if(plantdistance>tmpdistance)
                nearestplat=visibleplant[i];
        }
    }
//all found
if(visibleplant.size()==0)
{
   // out[0]=0;
    //out[1]=
    //out[2]
    //out[]
}


}*/


#ifndef LINKS_H_INCLUDED
#define LINKS_H_INCLUDED
#include <vector>
#include "constant.h"
#include <stdlib.h>
using namespace std;

class Links
{
public:
    vector<float> links;
public :
    Links()
    {
    }
    Links(const Links& link)
    {
        this->links.clear();
        for(int i=0; i<link.links.size(); i++)
        {
            this->links.push_back(link.links[i]);
        }
    }
    Links operator=(Links link)
    {
        this->links.clear();
        for(int i=0; i<link.links.size(); i++)
        {
            this->links.push_back(link.links[i]);
        }
        return link;
    }
};


#endif // LINKS_H_INCLUDED

#ifndef NETWORK_H
#define NETWORK_H
#include <map>
#include <string>
#include "router.h"
using namespace std;

class Network
{
public:
    Network();
    void addRouter(Router newRouter);
    void addLink(string routerA, string routerB, int cost);
    void removeLink(string routerA, string routerB);
    void removeRouter(string name);

private:
    map<string,Router> routers;
};

#endif // NETWORK_H

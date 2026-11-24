#ifndef NETWORK_H
#define NETWORK_H
#include <map>
#include <string>
#include "router.h"
#include <queue>
#include <vector>
using namespace std;

class Network
{
public:
    Network();
    void addRouter(Router newRouter);
    void addLink(string routerA, string routerB, int cost);
    void removeLink(string routerA, string routerB);
    void removeRouter(string name);
    void calculateRoutes(string source); // dijkstra
    void updateAllRoutes();
    int getCost(string origin, string destination); // -1 if there is no path
    vector<string> getPath(string origin, string destination);
    bool hasRouter(string name);
    bool loadFromFile(string fileName);
    bool saveToFile(string fileName);
    void generateRandom(int numRouters, int extraLinks, string fileName);
    void printLinks();
    void printTables();

private:
    map<string,Router> routers;
};

#endif // NETWORK_H

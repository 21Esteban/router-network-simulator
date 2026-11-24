#include "router.h"

Router::Router(string routerName) {
    name=routerName;
}

void Router::addNeighbor(string neighborName, int cost)
{
    neighbors[neighborName] = cost;
}

void Router::eraseNeighbor(string neighborName)
{
    neighbors.erase(neighborName);
}

string Router::getName()
{
    return name;
}

map<string,int> Router::getNeighbors(){
    return neighbors;
}


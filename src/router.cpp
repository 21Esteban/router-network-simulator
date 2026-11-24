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

void Router::setRoute(string destination, int cost, vector<string> path)
{
    routeCost[destination] = cost;
    routePath[destination] = path;
}

int Router::getCost(string destination){
    return routeCost[destination];
}
vector<string> Router::getPath(string destination){
    return routePath[destination];
}

bool Router::hasRoute(string destination){
    return routeCost.count(destination) > 0;
}

void Router::clearRoutes(){
    routeCost.clear();
    routePath.clear();
}

#include "network.h"

Network::Network() {}

void Network::addRouter(Router newRouter){
    routers[newRouter.getName()] = newRouter;
}

void Network::addLink(string routerA, string routerB, int cost){

    if (routers.count(routerA) == 0) addRouter(Router(routerA));
    if (routers.count(routerB) == 0) addRouter(Router(routerB));

    routers[routerA].addNeighbor(routerB,cost);
    routers[routerB].addNeighbor(routerA,cost);

}


void Network::removeLink(string routerA, string routerB){
    routers[routerA].eraseNeighbor(routerB);
    routers[routerB].eraseNeighbor(routerA);
}

void Network::removeRouter(string name)
{
    for (auto &entry : routers) {
        entry.second.eraseNeighbor(name);
    }
    routers.erase(name);
}
#include "network.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

Network::Network() {}

void Network::addRouter(Router newRouter){
    routers[newRouter.getName()] = newRouter;
    updateAllRoutes();
}

void Network::addLink(string routerA, string routerB, int cost){

    if (routers.count(routerA) == 0) addRouter(Router(routerA));
    if (routers.count(routerB) == 0) addRouter(Router(routerB));

    routers[routerA].addNeighbor(routerB,cost);
    routers[routerB].addNeighbor(routerA,cost);
    updateAllRoutes();

}


void Network::removeLink(string routerA, string routerB){
    routers[routerA].eraseNeighbor(routerB);
    routers[routerB].eraseNeighbor(routerA);
    updateAllRoutes();
}

void Network::removeRouter(string name)
{
    for (auto &entry : routers) {
        entry.second.eraseNeighbor(name);
    }
    routers.erase(name);
    updateAllRoutes();
}

void Network::calculateRoutes(string source)
{
    map<string, int> distance; // best cost to each router
    map<string, string> previous; // router we came from, to rebuild the path
    priority_queue<pair<int, string>,
    vector<pair<int, string>>,
    greater<pair<int, string>>> queue; // the cheapest comes out first

    distance[source] = 0;
    queue.push({0, source});

    while (!queue.empty()) {
        int cost = queue.top().first;
        string current = queue.top().second;
        queue.pop();

        // old entry, we already have a better cost for this one
        if (cost > distance[current]) continue;

        for (auto &neighbor : routers[current].getNeighbors()) {
            string next = neighbor.first;
            int newCost = cost + neighbor.second;

            // not visited yet or cheaper this way
            if (distance.count(next) == 0 || newCost < distance[next]) {
                distance[next] = newCost;
                previous[next] = current;
                queue.push({newCost, next});
            }
        }
    }

    // build the paths going backwards with previous
    routers[source].clearRoutes();
    for (auto &entry : distance) {
        string destination = entry.first;
        vector<string> path;

        string at = destination;
        while (at != source) {
            path.insert(path.begin(), at);
            at = previous[at];
        }
        path.insert(path.begin(), source);

        routers[source].setRoute(destination, entry.second, path);
    }
}

void Network::updateAllRoutes()
{
    for (auto &entry : routers) {
        calculateRoutes(entry.first);
    }
}

int Network::getCost(string origin, string destination)
{
    if (routers.count(origin) == 0 || !routers[origin].hasRoute(destination)) return -1;
    return routers[origin].getCost(destination);
}

vector<string> Network::getPath(string origin, string destination)
{
    if (routers.count(origin) == 0 || !routers[origin].hasRoute(destination)) return {};
    return routers[origin].getPath(destination);
}

bool Network::hasRouter(string name)
{
    return routers.count(name) > 0;
}

// file format: one link per line -> A B 4
bool Network::loadFromFile(string fileName)
{
    ifstream file(fileName);
    if (!file.is_open()) return false;

    routers.clear();
    string routerA, routerB;
    int cost;
    while (file >> routerA >> routerB >> cost) {
        addLink(routerA, routerB, cost);
    }
    file.close();
    return true;
}

bool Network::saveToFile(string fileName)
{
    ofstream file(fileName);
    if (!file.is_open()) return false;

    for (auto &entry : routers) {
        for (auto &neighbor : entry.second.getNeighbors()) {
            // each link is in both routers, write it only once
            if (entry.first < neighbor.first) {
                file << entry.first << " " << neighbor.first << " " << neighbor.second << endl;
            }
        }
    }
    file.close();
    return true;
}

// makes a random network, saves it in a file and then loads it
void Network::generateRandom(int numRouters, int extraLinks, string fileName)
{
    srand(time(nullptr));

    vector<string> names;
    for (int i = 0; i < numRouters; i++) {
        names.push_back("R" + to_string(i + 1));
    }

    ofstream file(fileName);
    // connect each router with one of the previous ones so nobody is left alone
    for (int i = 1; i < numRouters; i++) {
        int other = rand() % i;
        file << names[i] << " " << names[other] << " " << (rand() % 20 + 1) << endl;
    }
    for (int i = 0; i < extraLinks; i++) {
        int a = rand() % numRouters;
        int b = rand() % numRouters;
        if (a != b) {
            file << names[a] << " " << names[b] << " " << (rand() % 20 + 1) << endl;
        }
    }
    file.close();

    loadFromFile(fileName);
}

void Network::printLinks()
{
    if (routers.empty()) {
        cout << "The network is empty" << endl;
        return;
    }
    for (auto &entry : routers) {
        cout << entry.first << ":";
        for (auto &neighbor : entry.second.getNeighbors()) {
            cout << " " << neighbor.first << "(" << neighbor.second << ")";
        }
        cout << endl;
    }
}

void Network::printTables()
{
    for (auto &entry : routers) {
        cout << "Routing table of " << entry.first << endl;
        for (auto &other : routers) {
            string destination = other.first;
            cout << "  " << destination << ": ";
            if (!entry.second.hasRoute(destination)) {
                cout << "no path" << endl;
                continue;
            }
            cout << "cost " << entry.second.getCost(destination) << ", path";
            for (string step : entry.second.getPath(destination)) cout << " " << step;
            cout << endl;
        }
    }
}

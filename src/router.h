#ifndef ROUTER_H
#define ROUTER_H
#include <map>
#include <string>
#include <vector>
using namespace std;
class Router
{
private:
    string name;
    map<string,int> neighbors;
    map<string, int> routeCost; // destination -> cost
    map<string, vector<string>> routePath; // destination -> path
public:
    Router(string routerName="");
    void addNeighbor(string neighborName, int cost);
    void eraseNeighbor(string neighborName);
    string getName();
    map<string,int> getNeighbors();
    void setRoute(string destination, int cost, vector<string> path);
    int getCost(string destination);
    vector<string> getPath(string destination);
    bool hasRoute(string destination);
    void clearRoutes();
};

#endif // ROUTER_H

#ifndef ROUTER_H
#define ROUTER_H
#include <map>
#include <string>
using namespace std;
class Router
{
private:
    string name;
    map<string,int> neighbors;
public:
    Router(string routerName="");
    void addNeighbor(string neighborName, int cost);
    void eraseNeighbor(string neighborName);
    string getName();
    map<string,int> getNeighbors();
};

#endif // ROUTER_H

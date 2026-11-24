#include <iostream>
#include "router.h"
using namespace std;

int main()
{
    cout << "Router network simulator" << endl;

    Router a("A");
    a.addNeighbor("B",4);
    a.addNeighbor("C",10);

    for(auto neighbord : a.getNeighbors()){
        cout << neighbord.first << "-->" << neighbord.second <<endl;
    }

    return 0;
}

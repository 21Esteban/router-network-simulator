# router-network-simulator

Router network simulation in C++ using STL containers and Dijkstra shortest paths. Informatica II, UdeA.

## How to run
Open `CMakeLists.txt` in Qt Creator (or build with CMake) and run `router_network`.

The menu lets you load a network from a file, generate a random one, add/remove routers and links, and ask for the cost and path between two routers.

## File format
One link per line: `router1 router2 cost`. Example (`guide_network.txt`, the network from the guide):

```
A B 4
A C 10
B D 1
C D 2
```

## STL containers used
- `map<string, Router>`: routers of the network, searched by name
- `map<string, int>`: neighbors of a router and the cost of each route
- `map<string, vector<string>>`: path to each destination
- `priority_queue`: Dijkstra, the cheapest router comes out first

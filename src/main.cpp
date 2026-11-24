#include <iostream>
#include "network.h"
using namespace std;

void printPath(Network &network, string origin, string destination)
{
    int cost = network.getCost(origin, destination);
    if (cost == -1) {
        cout << "There is no path from " << origin << " to " << destination << endl;
        return;
    }
    cout << "Cost: " << cost << endl << "Path:";
    for (string step : network.getPath(origin, destination)) cout << " " << step;
    cout << endl;
}

int main()
{
    Network network;
    int option = -1;

    while (option != 0) {
        cout << endl << "===== Router network simulator =====" << endl;
        cout << "1. Load network from file" << endl;
        cout << "2. Generate random network" << endl;
        cout << "3. Add router" << endl;
        cout << "4. Remove router" << endl;
        cout << "5. Add or change a link" << endl;
        cout << "6. Remove link" << endl;
        cout << "7. Cost and path between two routers" << endl;
        cout << "8. Show network" << endl;
        cout << "9. Show routing tables" << endl;
        cout << "10. Save network to file" << endl;
        cout << "0. Exit" << endl;
        cout << "Option: ";
        cin >> option;

        if (cin.fail()) { // the user typed letters
            cin.clear();
            cin.ignore(1000, '\n');
            option = -1;
        }

        string a, b, fileName;
        int number, cost;

        switch (option) {
        case 1:
            cout << "File name: ";
            cin >> fileName;
            if (network.loadFromFile(fileName)) cout << "Network loaded" << endl;
            else cout << "Could not open " << fileName << endl;
            break;
        case 2:
            cout << "How many routers? ";
            cin >> number;
            if (number < 2) {
                cout << "At least 2 routers" << endl;
                break;
            }
            network.generateRandom(number, number, "random_network.txt");
            cout << "Saved in random_network.txt" << endl;
            network.printLinks();
            break;
        case 3:
            cout << "Name: ";
            cin >> a;
            if (network.hasRouter(a)) cout << a << " already exists" << endl;
            else network.addRouter(Router(a));
            break;
        case 4:
            cout << "Name: ";
            cin >> a;
            if (network.hasRouter(a)) network.removeRouter(a);
            else cout << a << " does not exist" << endl;
            break;
        case 5:
            cout << "Router 1, router 2 and cost (ex: A B 4): ";
            cin >> a >> b >> cost;
            if (a == b || cost <= 0) cout << "Invalid link" << endl;
            else network.addLink(a, b, cost);
            break;
        case 6:
            cout << "Router 1 and router 2: ";
            cin >> a >> b;
            if (network.hasRouter(a) && network.hasRouter(b)) network.removeLink(a, b);
            else cout << "Those routers do not exist" << endl;
            break;
        case 7:
            cout << "Origin and destination: ";
            cin >> a >> b;
            printPath(network, a, b);
            break;
        case 8:
            network.printLinks();
            break;
        case 9:
            network.printTables();
            break;
        case 10:
            cout << "File name: ";
            cin >> fileName;
            if (network.saveToFile(fileName)) cout << "Saved" << endl;
            else cout << "Could not save" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Invalid option" << endl;
        }
    }
    return 0;
}

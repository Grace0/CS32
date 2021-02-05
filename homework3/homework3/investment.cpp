#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

class Investment {
    
};

class House {
    
};

class Stock {
    
};

class Painting {
    
};

void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main()
{
    Investment* portfolio[4];
    portfolio[0] = new Painting("Salvator Mundi", 450300000);
      // Stock holdings have a name, value, and ticker symbol
    portfolio[1] = new Stock("Lyft", 50000, "LYFT");
    portfolio[2] = new Stock("GameStop", 10000, "GME");
    portfolio[3] = new House("4 Privet Drive", 660000);

    for (int k = 0; k < 4; k++)
        display(portfolio[k]);

      // Clean up the investments before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete portfolio[k];
}

//Salvator Mundi: painting bought for $450300000
//Lyft (fungible): stock trading as LYFT bought for $50000
//GameStop (fungible): stock trading as GME bought for $10000
//4 Privet Drive: house bought for $660000
//Cleaning up
//Destroying Salvator Mundi, a painting
//Destroying Lyft, a stock holding
//Destroying GameStop, a stock holding
//Destroying the house 4 Privet Drive

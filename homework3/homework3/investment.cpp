#include <iostream>
#include <string>
using namespace std;

class Investment {
public:
    Investment(string name, int price) {
        m_name = name;
        m_price = price;
    }
    
    virtual ~Investment() {} //virtual so that subclass' destructors get called; note that subclasses get destructed first
    
    int purchasePrice() const {
        return m_price;
    }
    
    string name() const {
        return m_name;
    }
    
    virtual string description() const = 0; //pure virtual functions; must be overriden in subclasses
    virtual bool fungible() const {
        return false;
    }

    
private:
    string m_name;
    int m_price;
};

class Painting : public Investment {
    
public:
    Painting(string name, int price) : Investment(name, price) {

    }
    
    virtual ~Painting() {
        cout << "Destroying " << name() << ", a painting" << endl;
    }
    
    virtual string description() const {
        return "painting";
    }
    
private: //no member variables in addition to those in Investment superclass
 
};

class House : public Investment {
    
public:
    House(string address, int price) : Investment(address, price) {
        
    }
    virtual ~House() {
        cout << "Destroying the house " << name() << endl;
    }
    
    virtual string description() const {
        return "house";
    }
    
private:
    
};

class Stock : public Investment {
    
public:
    
    Stock(string company, int price, string ticker) : Investment(company, price) {
        m_ticker = ticker;
    }
    
    virtual ~Stock() {
        cout << "Destroying " << name() << ", a stock holding" << endl;
    }
    
    virtual string description() const {
        return "stock trading as " + m_ticker;
    }
    
    virtual bool fungible() const {
        return true;
    }
    
private:
    string m_ticker;
};

void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}
//
//int main()
//{
//    Investment* portfolio[4];
//    portfolio[0] = new Painting("Salvator Mundi", 450300000);
//      // Stock holdings have a name, value, and ticker symbol
//    portfolio[1] = new Stock("Lyft", 50000, "LYFT");
//    portfolio[2] = new Stock("GameStop", 10000, "GME");
//    portfolio[3] = new House("4 Privet Drive", 660000);
//
//    for (int k = 0; k < 4; k++)
//        display(portfolio[k]);
//
//      // Clean up the investments before exiting
//    cout << "Cleaning up" << endl;
//    for (int k = 0; k < 4; k++)
//        delete portfolio[k];
//}

//Salvator Mundi: painting bought for $450300000
//Lyft (fungible): stock trading as LYFT bought for $50000
//GameStop (fungible): stock trading as GME bought for $10000
//4 Privet Drive: house bought for $660000
//Cleaning up
//Destroying Salvator Mundi, a painting
//Destroying Lyft, a stock holding
//Destroying GameStop, a stock holding
//Destroying the house 4 Privet Drive

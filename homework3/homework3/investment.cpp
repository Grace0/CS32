
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

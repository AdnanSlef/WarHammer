#include <iostream>
#include <vector>

using namespace std;

class Model
{
public:
    int stat;
};

class Unit
{
public:
    string brand = "Ford";
    vector<Model> models;
    void honk()
    {
        cout << "Tuut, tuut! \n";
    }
};

class TypeOfUnit : public Unit
{
public:
    string model = "Mustang";
};

int main()
{
    Model myObj;
    cout << myObj.stat << endl;
}

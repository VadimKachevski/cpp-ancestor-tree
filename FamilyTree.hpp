#pragma once
#include <string>
#include <iostream>
using namespace std;

namespace family
{
class Tree
{

private:
    string name;
    int depth;
    string parent;
    Tree *mother;
    Tree *father;

public:
    Tree(string theName);
    ~Tree()
    {
        delete father;
        delete mother;
       // delete this;
    }
    string getName();
    int getDepth();
    string getType();
    Tree *getMother();
    Tree *getFather();
    Tree &addFather(string from, string newN);
    Tree &addMother(string from, string newN);
    string relation(string who);
    string find(string who);
    void display();
    void remove(string theName);

};

} // namespace family
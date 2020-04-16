#include "FamilyTree.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstring>

using namespace std;
using namespace family;

Tree::Tree(string theName)
{
    this->name = theName;
    this->depth = 0;
    this->father = NULL;
    this->mother = NULL;
    this->parent = "me";
}

int Tree::getDepth()
{
    return this->depth;
}
string Tree::getType()
{
    return this->parent;
}
//return the name of the curr subTree
string Tree::getName()
{
    return this->name;
}
//return pointer to the mother of the curr sub tree
Tree *Tree::getMother()
{
    return this->mother;
}
// returns pointer to the father of the curr sub tree
Tree *Tree::getFather()
{
    return this->father;
}
// searches for the string who should be usefull for most of the other functions
//returns the sub tree he is located in
Tree *findfrom(Tree *where, string who)
{
    if (where == NULL)
    {
        return NULL;
    }
    if (who.compare(where->getName()) == 0)
    {
        return where;
    }
    else
    {
        Tree *f = findfrom(where->getFather(), who);
        if (f != NULL)
        {
            return f;
        }
        Tree *m = findfrom(where->getMother(), who);
        if (m != NULL)
        {
            return m;
        }
    }
    return NULL;
}

Tree &Tree::addFather(string from, string newN)
{
    Tree *curr = findfrom(this, from);
    if (curr != NULL)
    {
        if (curr->father == NULL)
        {
            curr->father = new Tree(newN);
            curr->father->depth = curr->depth + 1;
            curr->father->parent = "father";
        }
        else
        {
            string test = "'" + from + "' allready have a father!..?";
            throw invalid_argument(test);
        }
    }
    else
    {
        string test = "Could'nt find '" + from + "'";
        throw invalid_argument(test);
    }
    return *this;
}

Tree &Tree::addMother(string from, string newN)
{
    Tree *curr = findfrom(this, from);
    if (curr != NULL)
    {
        if (curr->mother == NULL)
        {
            curr->mother = new Tree(newN);
            curr->mother->depth = curr->depth + 1;
            curr->mother->parent = "mother";
        }
        else
        {
            string test = "'" + from + "' allready have a mother!..?";
            throw invalid_argument(test);
        }
    }
    else
    {
        string test = "Could'nt find '" + from + "'";
        throw invalid_argument(test);
    }
    return *this;
}

void Tree::display()
{
    if (this->mother != NULL)
    {
        this->mother->display();
    }
    cout << this->name << endl;
    if (this->father != NULL)
    {
        this->father->display();
    }
}

string getRealtionName(int depth)
{
    if (depth <= 1)
    {
        return "";
    }
    if (depth == 2)
    {
        return "grand";
    }
    string ans = "";
    for (int i = 2; i < depth; i++)
    {
        ans = ans + "great-";
    }
    ans = ans + "grand";
    return ans;
}
string Tree::relation(string who)
{
    Tree *curr = findfrom(this, who);
    if (curr != NULL)
    {
        string ans = getRealtionName(curr->depth);
        ans = ans + curr->parent;
        return ans;
    }
    else
    {
        return "unrelated";
    }
}

Tree *findAtDepth(Tree *t, int depth, string what)
{
    if (t == NULL)
    {
        return NULL;
    }
    if (what.compare(t->getType()) == 0 && t->getDepth() == depth)
    {
        return t;
    }
    else
    {
        Tree *f = findAtDepth(t->getFather(), depth, what);
        if (f != NULL)
        {
            return f;
        }
        Tree *m = findAtDepth(t->getMother(), depth, what);
        if (m != NULL)
        {
            return m;
        }
    }
    return NULL;
}

string Tree::find(string who)
{
    int searchDepth = 0;
    string what;
    int counter = 0;
    if ((who.find_first_not_of(' ') != string::npos))
    {
        char *cstrText = new char[who.length() + 1];
        strcpy(cstrText, who.c_str());
        char *test;
        test = strtok(cstrText, "-");

        while (test != NULL)
        {
            counter++;
            test = strtok(NULL, "-");
        }
        if (counter == 1)
        {
            if (who.compare("me") == 0)
            {
                return this->name;
            }
            if (who.compare("mother") == 0)
            {
                if (this->mother != NULL)
                {
                    return this->mother->name;
                }
                else
                {
                   string test = "Can't handle " + who;
            throw invalid_argument(test);
                }
            }
            if (who.compare("father") == 0)
            {
                if (this->father != NULL)
                {
                    return this->father->name;
                }
                else
                {
                    string test = "Can't handle " + who;
            throw invalid_argument(test);
                }
            }
            if (who.compare("grandmother") == 0 || who.compare("grandfather") == 0)
            {
                searchDepth = 2;
                size_t pos = who.find("grand");
                what = who.substr(pos + 5);
            }
            else
            {
                string test = "Can't handle " + who;
                throw invalid_argument(test);
            }
            Tree *ans = findAtDepth(this, searchDepth, what);
            if (ans == NULL)
            {
                string test = "Can't handle " + who;
                 throw invalid_argument(test);
            }
            else
            {
                return ans->getName();
            }
        }
        if (counter > 1)
        {
            searchDepth = counter + 1;
            size_t pos = who.find("grand");
            if (pos == string::npos || pos == 0)
            {
                string test = "Can't handle " + who;
                throw invalid_argument(test);
            }
            what = who.substr(pos + 5);
            Tree *ans = findAtDepth(this, searchDepth, what);
            if (ans == NULL)
            {
                string test = "Can't handle " + who;
            throw invalid_argument(test);
            }
            else
            {
                return ans->getName();
            }
        }
        else
        {
            string test = "Can't handle " + who;
            throw invalid_argument(test);
        }
    }
    else
    {
        return "Can't handle empty names";
        //throw invalid_argument(test);
    }
}

Tree *removeHelper(string theName, Tree *t)
{
    if (t != NULL)
    {
        if (t->getFather() != NULL)
        {
            if (theName.compare(t->getFather()->getName()) == 0)
            {
                return t;
            }
        }
        if (t->getMother() != NULL)
        {
            if (theName.compare(t->getMother()->getName()) == 0)
            {
                return t;
            }
        }

        Tree *f = removeHelper(theName, t->getFather());
        if (f != NULL)
        {
            return f;
        }
        Tree *m = removeHelper(theName, t->getMother());
        if (m != NULL)
        {
            return m;
        }
        return NULL;
    }
    return NULL;
}
void Tree::remove(string theName)
{

    Tree *curr = removeHelper(theName, this);
    //cout << curr->name;
    if (curr)
    {
        if(curr->father != nullptr)
        {
        if (curr->father->name == theName)
        {
            delete curr->father;
            curr->father = nullptr;
            return;
        }
        }
        if(curr->mother != nullptr)
        {
            if(curr->mother != nullptr)
            {
            delete curr->mother;
            curr->mother = nullptr;
            return;
            }
        }
        
    }
    else
    {
        string test = "Can't handle " + theName;
            throw invalid_argument(test);
    }
    
}

#ifndef SHAPE
#define SHAPE

// STL
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Shape
{
public:
    Shape();
    void setElement(pair<char, string>);
    void setSize(int);
    virtual void createPattern() = 0;
    vector<vector<stack<pair<char,string>*>>>* getPattern();
protected:
    int size;
    pair<char, string> element;
    vector<vector<stack<pair<char,string>*>>> shapePattern;
private:
};

#endif

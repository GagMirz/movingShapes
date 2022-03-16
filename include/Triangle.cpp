#include "Triangle.h"

Triangle::Triangle() {
}

void Triangle::createPattern() {
    shapePattern.resize(size, vector<stack<pair<char, string>*>>(size * 2 - 1, stack<pair<char, string>*>()));
    int i = size - 1;
    for(auto it = shapePattern.begin(); it != shapePattern.end(); it++, i--){
        for(auto innerIt = it->begin() + i; innerIt != it->end() - i; innerIt++){
            innerIt->push(&element);
        }
    }
}

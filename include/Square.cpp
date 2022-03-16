#include "Square.h"

Square::Square() {
}

void Square::createPattern() {
    shapePattern.resize(size, vector<stack<pair<char, string>*>>(size, stack<pair<char, string>*>()));
    for(auto it = shapePattern.begin(); it != shapePattern.end(); it++){
        for(auto innerIt = it->begin(); innerIt != it->end(); innerIt++){
            innerIt->push(&element);
        }
    }
}

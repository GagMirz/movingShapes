#include "Shape.h"

Shape::Shape() :element('#',"BLUE"), size(1) {}

void Shape::setElement(pair<char, string> element) {
    this->element = element;
}

void Shape::setSize (int newSize) {
    size = newSize;
    createPattern();
}

vector<vector<stack<pair<char,string>*>>> * Shape::getPattern(){
    return &shapePattern;
}
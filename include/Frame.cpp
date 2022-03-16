#include "Frame.h"

Frame::Frame() : change(false)
{
}

void Frame::reSizeFrame(int height, int width)
{
    this->height = height;
    this->width = width;
    while (change)
    {
        sleep_for(milliseconds(5));
    };
    change = true;
    frameMat.resize(height, vector<stack<pair<char, string> *>>(width, stack<pair<char, string> *>()));
    for (auto it = frameMat.begin(); it != frameMat.end(); it++)
    {
        for (auto innerIt = it->begin(); innerIt != it->end(); innerIt++)
        {
            innerIt->push(&element);
        }
    }
    change = false;
}

void Frame::emptyFrame()
{
    for (auto it = frameMat.begin(); it != frameMat.end(); it++)
    {
        for (auto innerIt = it->begin(); innerIt != it->end(); innerIt++)
        {
            while(innerIt->top()!=&element)innerIt->pop();
        }
    }
}

void Frame::fillFrame(pair<char, string> newElement)
{
    element = newElement;
}

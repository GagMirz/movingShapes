#include "Display.h"

#include <iostream>

Display *Display::inst_ = nullptr;

Display::Display() : frameRate(1), backgroundElement('.', "WHITE")
{
   Display::colorMap.insert(pair<string, string>("BLACK", "\033[30m"));
   Display::colorMap.insert(pair<string, string>("RED", "\033[31m"));
   Display::colorMap.insert(pair<string, string>("GREEN", "\033[32m"));
   Display::colorMap.insert(pair<string, string>("YELLOW", "\033[33m"));
   Display::colorMap.insert(pair<string, string>("BLUE", "\033[34m"));
   Display::colorMap.insert(pair<string, string>("MAGENTA", "\033[35m"));
   Display::colorMap.insert(pair<string, string>("CYAN", "\033[36m"));
   Display::colorMap.insert(pair<string, string>("WHITE", "\033[37m"));
}

bool Display::chechkColor(string color)
{
   return Display::colorMap.find(color) != Display::colorMap.end();
}

void Display::setFrameRate(int rate)
{
   frameRate = rate;
}

void Display::addShape(Shape *newShape)
{
   shapes[newShape] = pair<int, int>(0, 0);
}

bool Display::checkBounds(Shape *shape, pair<int, int> move, pair<int, int> *coords)
{
   int heightCoord = backgroundFrame->height / 2;
   int widthCoord = backgroundFrame->width / 2;
   heightCoord -= shape->getPattern()->size() / 2;
   heightCoord += coords->first + move.first;
   widthCoord -= shape->getPattern()[0].size() / 2;
   widthCoord += coords->second + move.second;
   if (heightCoord < 0 || widthCoord < 0)
   {
      return false;
   }
   else if (heightCoord + shape->getPattern()->size() > backgroundFrame->height || widthCoord + shape->getPattern()[0].size() >= backgroundFrame->width)
   {
      return false;
   }
   return true;
}

void Display::moveShape(Shape *shape, pair<int, int> move)
{
   pair<int, int> *coords = &shapes[shape];
   if (checkBounds(shape, move, coords))
   {
      coords->first += move.first;
      coords->second += move.second;
   }
}

void Display::setFrame(Frame &frame)
{
   backgroundFrame = &frame;
}

void Display::displayElement(stack<pair<char, string> *> element)
{
   cout << Display::colorMap[element.top()->second] << element.top()->first;
}

void Display::displayFrame()
{
   system("clear");
   for (auto it = backgroundFrame->frameMat.begin(); it != backgroundFrame->frameMat.end(); it++)
   {
      for (auto innerIt = it->begin(); innerIt != it->end(); innerIt++)
      {
         this->displayElement(*innerIt);
      }
      cout << endl;
   }
}

void Display::addShapesToFrame()
{
   for (auto it = shapes.begin(); it != shapes.end(); it++)
   {
      vector<vector<stack<pair<char, string> *>>> *pattern = it->first->getPattern();
      backgroundFrame->emptyFrame();
      int patternHeight = pattern->size();
      int patternWidth = pattern[0].size();
      int heightCoord = backgroundFrame->height / 2;
      int widthCoord = backgroundFrame->width / 2;
      heightCoord -= patternHeight / 2;
      heightCoord += it->second.first;
      widthCoord -= patternWidth / 2;
      widthCoord += it->second.second;
      for (auto [itFrame, itPattern] = tuple{backgroundFrame->frameMat.begin() + heightCoord, pattern->begin()}; itPattern != pattern->end(); itFrame++, itPattern++)
      {
         for (auto [innerItFrame, innerItPattern] = tuple{itFrame->begin() + widthCoord, itPattern->begin()}; innerItPattern != itPattern->end(); innerItFrame++, innerItPattern++)
         {
            if (!innerItPattern->empty())
               innerItFrame->push(innerItPattern->top());
         }
      }
   }
}

void Display::delay(int rate)
{
   sleep_for(milliseconds(1000 / rate));
}

void Display::run()
{
   while (true)
   {
      addShapesToFrame();
      while (backgroundFrame->change)
      {
         sleep_for(milliseconds(5));
      }
      backgroundFrame->change = true;
      displayFrame();
      backgroundFrame->change = false;
      delay(frameRate);
   }
}

Display *Display::getInstance()
{
   if (inst_ == nullptr)
   {
      inst_ = new Display();
   }
   return (inst_);
}

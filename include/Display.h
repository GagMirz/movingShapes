#ifndef DISPLAY
#define DISPLAY

// STL
#include <vector>
#include <string>
#include <iostream>
#include <map>

// Classes
#include "Frame.h"
#include "Shape.h"

// Thread Time ATOMIC
#include <chrono>
#include <thread>
#include <atomic>

using namespace std;
using namespace this_thread;
using namespace chrono;

class Display
{
public:
   static Display *getInstance();

   static bool chechkColor(string);

   void setFrameRate(int);
   void addShape(Shape*);

   void moveShape(Shape*, pair<int, int>);

   void setFrame(Frame &);
   void run();

protected:
   inline static map<string, string> colorMap;
   int frameRate;
   pair<char, string> backgroundElement;
   map<Shape*, pair<int, int>> shapes;
   Frame *backgroundFrame;

   void displayElement(stack<pair<char, string>*>);
   void displayFrame();

   void addShapesToFrame();

   bool checkBounds(Shape*, pair<int, int>, pair<int,int>*);

   void delay(int);

private:
   static Display *inst_;
   Display();
   Display(const Display &);
   Display &operator=(const Display &);
};

#endif

// int main() {
//    Display* p1 = Display::getInstance();
// }
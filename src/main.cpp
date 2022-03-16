#include <iostream>

// STL
#include <string>
#include <utility>

// Window size
#include <sys/ioctl.h>
#include <unistd.h>

// Classes
#include "../include/Display.h"
#include "../include/Frame.h"
#include "../include/nonBlockingInput.h"
#include "../include/Square.h"
#include "../include/Triangle.h"

using namespace std;
using namespace this_thread;
using namespace chrono;

pair<int, int> windowSize(winsize window)
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
    return {window.ws_row - 1, window.ws_col};
}

void delay(int rate)
{
    sleep_for(milliseconds(1000 / rate));
}

int main()
{
    int choice;
    Shape *shape;
    bool cond = true;
    while (cond)
    {
        cout << "choose shape (input number)" << endl;
        cout << "1) triangle" << endl;
        cout << "2) square" << endl;
        cin >> choice;
        if (choice == 1)
        {
            shape = new Triangle();
            cond = false;
        }
        if (choice == 2)
        {
            shape = new Square();
            cond = false;
        }
        else
        {
            cout << endl
                 << "From above shapes ";
        }
    }

    map<int, string> colorPalette;
    colorPalette.insert(pair<int, string>(1, "BLACK"));
    colorPalette.insert(pair<int, string>(2, "RED"));
    colorPalette.insert(pair<int, string>(3, "GREEN"));
    colorPalette.insert(pair<int, string>(4, "YELLOW"));
    colorPalette.insert(pair<int, string>(5, "BLUE"));
    colorPalette.insert(pair<int, string>(6, "MAGENTA"));
    colorPalette.insert(pair<int, string>(7, "CYAN"));
    colorPalette.insert(pair<int, string>(8, "WHITE"));
    cond = true;
    while (cond)
    {
        cout << "choose color (input number)" << endl;
        cout << "1) BLACK" << endl;
        cout << "2) RED" << endl;
        cout << "3) GREEN" << endl;
        cout << "4) YELLOW" << endl;
        cout << "5) BLUE" << endl;
        cout << "6) MAGENTA" << endl;
        cout << "7) CYAN" << endl;
        cout << "8) WHITE" << endl;
        cin >> choice;
        if (colorPalette.find(choice) != colorPalette.end())
        {
            shape->setElement(pair<char, string>('+', colorPalette[choice]));
            cond = false;
        }
        else
        {
            cout << endl
                 << "From above color";
        }
    }
    colorPalette.~map();

    shape->setSize(5);
    shape->createPattern();

    struct winsize window;
    auto [windowHeight, windowWidth] = windowSize(window);

    Frame mainFrame;
    mainFrame.reSizeFrame(windowHeight, windowWidth);
    mainFrame.fillFrame(pair<char, string>('.', "WHITE"));

    Display *myDisplay = Display::getInstance();
    myDisplay->setFrameRate(60);
    myDisplay->setFrame(mainFrame);

    thread threadUI(&Display::run, myDisplay);

    char controller = ' ';

    myDisplay->addShape(shape);

    while (true)
    {
        controller = getch();
        if (controller == '\033')
        {
            getch();
            switch(getch()) {
        case 'A':
            controller='w';
            break;
        case 'B':
            controller='s';
            break;
        case 'C':
            controller='d';
            break;
        case 'D':
            controller='a';
            break;
    }
        }
        if (controller == 'w')
        {
            myDisplay->moveShape(shape, pair<int, int>(-1, 0));
        }
        else if (controller == 'a')
        {
            myDisplay->moveShape(shape, pair<int, int>(0, -1));
        }
        else if (controller == 's')
        {
            myDisplay->moveShape(shape, pair<int, int>(1, 0));
        }
        else if (controller == 'd')
        {
            myDisplay->moveShape(shape, pair<int, int>(0, 1));
        }
        delay(30);
    }
    return 0;
}
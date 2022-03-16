#ifndef FRAME
#define FRAME

// STL
#include <vector>
#include <stack>
#include <string>
#include <tuple>

#include <thread>
#include <chrono>
#include <atomic>

using namespace std;
using namespace this_thread;
using namespace chrono;

class Frame
{
public:
    Frame();
    void reSizeFrame(int, int);
    void fillFrame(pair<char, string>);
    void emptyFrame();
protected:
    int height;
    int width;
    atomic<bool>change;
    pair<char,string> element;
    vector<vector<stack<pair<char, string>*>>> frameMat;
    friend class Display;

private:
};

#endif

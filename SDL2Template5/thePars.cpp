#include<iostream>
#include<bits/stdc++.h>

using namespace std;
// constructors
class Point2D
{
    private:
    int mX, mY;
    
    public:
    // Point2D(int x = 0, int y = 0);
    Point2D();
    Point2D(int x, int y);
};

// initilizer lists
// delegating constructors
Point2D::Point2D(): Point2D(0, 0)
{

}
Point2D::Point2D(int x, int y): mX(x), mY(y)
{

}

// destructors
class A
{
    private:
    string mStrVal;
    public:
    A():A(""){}
    A(const string &strVal): mStrVal(strVal) {}
    ~A() {
        cout << "Destroying: " << mStrVal << endl;
    }
};

class B
{
    private:
    A mA1;
    A mA2;
    public:
    B():mA1("A1"), mA2("A2") {}
};

int main(int argc, char* argv[]) {
    /* 
    Point2D mP(10, 10);
    Point2D mp = {10, 10};
    Point2D mP = Point2D(10, 10);
    */
B myB;
}
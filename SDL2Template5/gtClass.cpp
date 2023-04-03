#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Classes and objects
class Point2D
{
    private:
    int mX, mY;
    
    public:
    void SetX(int x);
    void SetY(int y);
    int GetX();
    int GetY();
    void Display();
};

void Point2D::Display()
{
    cout << "X: " << mX << ", Y: " << mY << endl;
}

void Point2D::SetX(int x) {
    mX = x;
}
void Point2D::SetY(int y) {
    mY = y;
}
int Point2D::GetX() {
    return mX;
}
int Point2D::GetY() {
    return mY;
}

// Section 2 Practice Problem
class Time
{
    private:
    int hour, minute, second;
    
    public:

    void Init()
    {
        cin >> hour >> minute >> second;
    }
    
    void Display12hFormat() 
    {   
        int tmp = hour;
        if(hour > 12) 
        {
            hour -= 12;
        }
        string h = to_string(hour), m = to_string(minute), 
        s = to_string(second);
        if(hour < 10) {
            h = "0" + h;
        }
        if(minute < 10) {
            m = "0" + m;
        }
        if(second < 10) {
            s = "0" + s;
        }
        if(tmp > 12) {
            cout << h << ":" << m << ":" << s << " pm";
        }
        else cout << h << ":" << m << ":" << s << " am";
    }
    void Display24Format() 
    {
        string h = to_string(hour), m = to_string(minute), 
        s = to_string(second);
        if(hour < 10) {
            h = "0" + h;
        }
        if(minute < 10) {
            m = "0" + m;
        }
        if(second < 10) {
            s = "0" + s;
        }
        cout << h << ":" << m << ":" << s << endl;
    }
};

int main() 
{
    /*
    Point2D mP;
    mP.SetX(0);
    
    cout << "Size of myPoint is: " << sizeof(mP) << endl;// 8
    return 0;
    */
    Time now;
    now.Init();
    now.Display12hFormat();
}

// Structs and Classes
class CPoint2D
{
    // by default - public access
    int mX, mY;
    void SetX(int x);
    void SetY(int y);
    int GetX();
    int GetY();
    void Display();
};
struct SPoint2D
{
    // by default - private class
    int mX, mY;
    void SetX(int x);
    void SetY(int y);
    int GetX();
    int GetY();
    void Display();
};



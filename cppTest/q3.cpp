#include <iostream>
using namespace std;

class Rect
{
public:
    Rect(int w, int h)
        : width(w), height(h)
    {
    }

private:
    int width;
    int height;

public:
    int area() const
    {
        return this->width * this->height;
    }

    void setWidth(int _width)
    {
        if (_width < 0)
            this->width = 0;
        else
            this->width = _width;
    }

    void setHeight(int _height)
    {
        if (_height < 0)
            this->height = 0;
        else
            this->height = _height;
    }
};

int main()
{
    Rect r(3, 4);
    cout << r.area() << "\n"; // 12
    r.setWidth(-5);
    r.setHeight(2);
    cout << r.area() << "\n"; // 0
}
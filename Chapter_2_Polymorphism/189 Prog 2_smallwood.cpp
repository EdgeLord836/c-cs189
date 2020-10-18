#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>

class Shape
{
public:
    double mSize = 0.0;
    virtual void SetSize( double tSize )
    {
        mSize = tSize;
    }
    virtual double GetArea() = 0;
};

class Square :public Shape
{
public:
    virtual double GetArea()
    {
        return mSize * mSize;
    };
};

class Circle :public Shape
{
public:
    virtual double GetArea()
    {
        return M_PI * mSize * mSize;
    };
};

int main()
{
    std::vector<Shape*>tShapes;
    tShapes.push_back( new Square );
    tShapes.push_back( new Circle );
    tShapes.push_back( new Square );
    tShapes.push_back( new Circle );

    for( int i = 0; i < tShapes.size(); i++ )
        tShapes[i]->SetSize( i );
    for( int i = 0; i < tShapes.size(); i++ )
        std::cout << tShapes[i]->GetArea( ) << std::endl;
}



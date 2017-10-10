#include "Prostokat.h"
#include "ball.h"

ball::ball()
{

}

ball::ball(double x, double y, double szerokosc):
    Prostokat(x, y, szerokosc, szerokosc)
{
    m_kolor = { 1,0,0 };
}


void ball::setPosition(double x, double y)
{
    m_x = x;
    m_y = y;
}

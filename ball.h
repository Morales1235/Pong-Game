#pragma once
#ifndef BALL_H
#define BALL_H
#include "Prostokat.h"

class ball : public Prostokat
{
public:
    ball();
    ball(double x, double y, double szerokosc);
    void setPosition(double x, double y);
};

#endif // BALL_H

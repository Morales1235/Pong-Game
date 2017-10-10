#include "Prostokat.h"
#include <GL/freeglut.h>
#include<iostream>
using namespace std;
Prostokat::Prostokat():
	m_x(0),m_y(0),m_szerokosc(0),m_wysokosc(0),m_kat(0)
{
	m_kolor = { 1,0,0 };
}

Prostokat::Prostokat(double x, double y, double szerokosc, double wysokosc):
	m_x(x), m_y(y), m_szerokosc(szerokosc), m_wysokosc(wysokosc), m_kat(0)
{
	m_kolor = { 1,0,0 };
}

Prostokat::Prostokat(double x, double y, double szerokosc, double wysokosc, kolor kolor):
	m_x(x),m_y(y),m_szerokosc(szerokosc),m_wysokosc(wysokosc),m_kolor(kolor),m_kat(0)
{

}

double Prostokat::wysokosc()
{
return m_wysokosc;
}

double Prostokat::szerokosc()
{
    return m_szerokosc;
}

void Prostokat::rysuj()
{
	glPushMatrix();
    glTranslated(m_x, m_y, 0.0);

	glColor3d(m_kolor.r, m_kolor.g, m_kolor.b);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-m_szerokosc / 2, m_wysokosc / 2, 0);
		glVertex3d(m_szerokosc / 2, m_wysokosc / 2, 0);
		glVertex3d(m_szerokosc / 2, -m_wysokosc / 2, 0);
		glVertex3d(-m_szerokosc / 2, -m_wysokosc / 2, 0);
	}
	glEnd();
    glTranslated(-m_x, -m_y, 0.0);

	glPopMatrix();
}
void Prostokat::ustawKat(double kat)
{
m_kat=kat;
}

void Prostokat::przesun(double dx, double dy)
{
	m_x += dx;
	m_y += dy;
}

void Prostokat::ustaw(double x, double y)
{
    m_x = x;
    m_y = y;
}

void Prostokat::zmienKolor(kolor kolor)
{
	m_kolor = kolor;
}

void Prostokat::obroc(double dx)
{

	m_kat += dx;

}


double Prostokat::kat()
{
	return m_kat;
}

double Prostokat::pos_x()
{
    return m_x;
}

double Prostokat::pos_y()
{
    return m_y;
}

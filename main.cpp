/**
* \file main.cpp
* \author PUT Rover Programowanie
* \date 08-12-16
*/



#include <stdio.h>
#include <iostream>
#include"Prostokat.h"
#include "ball.h"
#define NDEBUG
#include<vector>
#include<ctime>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include"sKolor.h"
#include <ctime>
#include <math.h>
#include <cstring>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
using namespace std;
vector<Prostokat> vProstokaty;  ///< The venctor contains rectangles drawed on the screen

ball ball1(0.0, 0.0, 0.1);
double dx = 0, dy = 0;
int count_l = 0, count_r = 0;
double speed_factor = 2000, click_pos;
char wynik_l[2], wynik_r[2], mouse_pos[6];
char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
string winner;
GLboolean L_up = false, L_down = false, R_up = false, R_down = false, slide_en;


void resize(int width, int height) //! Function used to change size of OpenGL window and to rescale its elements
                                /**
                                \param width - the width of screen
                                \param height - the height of screen
                                */

{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void IntToChar(int number, char * buf)
{
    ostringstream msg;
    msg << number;
    strcpy(buf, msg.str().c_str());
}

void idle()
{
    glutPostRedisplay();
    if (L_up) vProstokaty[0].przesun(0, 0.07);
    if (L_down) vProstokaty[0].przesun(0, -0.07);
    if (R_up) vProstokaty[1].przesun(0, 0.07);
    if (R_down) vProstokaty[1].przesun(0, -0.07);
}

bool touch_Ltable()
{
    return ((ball1.pos_x() - ball1.szerokosc()/2 - vProstokaty[0].szerokosc()/2) < -3.0) & (ball1.pos_y() > (vProstokaty[0].pos_y() - vProstokaty[0].wysokosc()/2)) & (ball1.pos_y() < (vProstokaty[0].pos_y() + vProstokaty[0].wysokosc()/2));
}

bool touch_Rtable()
{
    return ((ball1.pos_x() + ball1.szerokosc()/2 + vProstokaty[1].szerokosc()/2) > 3.0) & (ball1.pos_y() > (vProstokaty[1].pos_y() - vProstokaty[1].wysokosc()/2)) & (ball1.pos_y() < (vProstokaty[1].pos_y() + vProstokaty[1].wysokosc()/2));
}

double rescaleX(double x)
{
    return ((x + 3.6) * 111.1);
}

double rescaleY(double y)
{
    return ((2.55 - y) * 117.5);
}


bool touch_border()
{
    return ((ball1.pos_y() > 2.42) | (ball1.pos_y() < -2.2));
}

double loss()
{
    return rand() % 140 - 70;
}

void licz_wspolrzedne()
{
    dy /= speed_factor;
    int * temp = new int;
    *temp = int(dx);
    dx = sqrt(pow((100.0/speed_factor), 2) - pow(dy, 2.0));
    if (*temp < 0) dx *= -1;
    delete temp;
}

void slower()
{
    if (speed_factor < 3000) {
        dy *= speed_factor;
        speed_factor += 100;
        licz_wspolrzedne();
    }
}

void faster()
{
    if (speed_factor > 900){
        dy *= speed_factor;
        speed_factor -= 100;
        licz_wspolrzedne();
    }
}


void startGame(char pos)
{
    speed_factor = 2000;
    dy = loss();
    licz_wspolrzedne();;
    switch (pos) {
    case 'l':
        ball1.setPosition(-2.5, 0);
        break;
    case 'r':
        ball1.setPosition(2.5, 0);
        dx *= -1;
        break;
    default:
        break;
    }
}

void startGame()
{
    speed_factor = 2000;
    dy = loss();
    licz_wspolrzedne();
    if (loss() > 0) ball1.setPosition(-2.5, 0.0);
    else {
        ball1.setPosition(2.5, 0.0);
        dx *= -1;}
}

void drawBorder()
{
    glPopMatrix();
    glLineWidth(3.0f);
    glColor3b(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2d((-3.0 - vProstokaty[0].szerokosc()/2), (2.42 + ball1.wysokosc()/2));
        glVertex2d((3.0 + vProstokaty[0].szerokosc()/2), (2.42 + ball1.wysokosc()/2));
    glEnd();
    glBegin(GL_LINES);
        glVertex2d((-3.0 - vProstokaty[0].szerokosc()/2), (-2.2 - ball1.wysokosc()/2));
        glVertex2d((3.0 + vProstokaty[0].szerokosc()/2), (-2.2 - ball1.wysokosc()/2));
    glEnd();
    glPushMatrix();
}

void drawBitmapText(char *string,float x,float y)
{
    glColor3d(0, 0, 0);
    char *c;
    glRasterPos3f(x, y, 0.01f);


    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
    glRasterPos3f(0.0f, 0.0f, 0.0f);
}


void drawCharText(char mychar, float x,float y)
{
    glRasterPos2f(x, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mychar);
}

void logic()
{
    if (touch_border()) {
        dy = -dy;
        ball1.przesun(dx, dy);}
    else if (touch_Ltable()){
        dx = -dx;
        faster();
        if (ball1.pos_y() > vProstokaty[0].pos_y()) dy += 0.01;
        else dy -= 0.001;
        ball1.przesun(dx, dy);
    }
    else if (touch_Rtable()){
        faster();
        dx = -dx;
        if (ball1.pos_y() > vProstokaty[1].pos_y()) dy += 0.01;
        else dy -= 0.001;
        ball1.przesun(dx, dy);
    }

    else ball1.przesun(dx, dy);
    if (ball1.pos_x() < -3.1) {
        glColor3f(0, 0, 0);
        count_r++;
        startGame('l');}
    else if (ball1.pos_x() > 3.1) {
            glColor3f(0, 0, 0);
            count_l++;
            startGame('r');}
}



void display()  //! The function displays elements on the screen

{
    // clear the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    drawBorder();
    glTranslated(-3.0, 0.0, 0.0);
    vProstokaty[0].rysuj();
    glTranslated(6.0, 0.0, 0.0);
    vProstokaty[1].rysuj();
    glTranslated(-3.0, 0.0, 0.0);
    logic();
    ball1.rysuj();

    glTranslated(0.0, -2.4, 0.0);
    vProstokaty[2].rysuj();
    vProstokaty[3].rysuj();
    glTranslated(0, 2.4, 0.0);
    vProstokaty[4].rysuj();
    vProstokaty[5].rysuj();

    sprintf(wynik_r, "%d", count_r);
    drawBitmapText(wynik_r, 2.0f, 1.8f);
    sprintf(wynik_l, "%d", count_l);
    drawBitmapText(wynik_l, -2.0f, 1.8f);
    drawBitmapText("-", -1.32f, -2.45f);
    drawBitmapText("+", 1.22f, -2.45f);
    drawBitmapText(mouse_pos, 0, 0);

    glPopMatrix();
    glutSwapBuffers();
}




void InitGLUTScene(char* window_name)  //! The function creates a window for drawing
                                        /**
                                        \param window_name - name of the window
                                        */
{
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(40, 40);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutCreateWindow(window_name);

    // set white as the clear colour
    glClearColor(1, 1, 1, 1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}




void FunkcjaDoObslugiKlawiatury(unsigned char key, int mouse_x, int mouse_y)  //! The function gets data from keyboard
                                                                        /**
                                                                        \param key  - pushed button
                                                                        \param mouse_x The x coordinate of the mouse
                                                                        \param mouse_y The y coordinate of the mouse
                                                                        */


{
    if (key == 'w')
        L_up = true;
    if (key == 's')
        L_down = true;
    if (key == 'p')
        R_up = true;
    if (key == 'l')
        R_down = true;
    if (key == 'z') faster();


}

void KeyboardUpFunc(unsigned char key, int x, int y)
{
    if (key == 'w')
        L_up = false;
    if (key == 's')
        L_down = false;
    if (key == 'p')
        R_up = false;
    if (key == 'l')
        R_down = false;
    if (key == 13) startGame();
}

void MouseFunc(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON & state == GLUT_DOWN)
    {
        click_pos = GLdouble(vProstokaty[2].pos_x() - x);
        if (y < rescaleY(vProstokaty[5].pos_y() - vProstokaty[5].wysokosc()/2) & y > rescaleY(vProstokaty[5].pos_y() + vProstokaty[5].wysokosc()/2))
        {
            if (x < rescaleX(vProstokaty[4].pos_x() + vProstokaty[4].szerokosc()/2) & x > rescaleX(vProstokaty[4].pos_x() - vProstokaty[4].szerokosc()/2)) slower();
            else if (x < rescaleX(vProstokaty[5].pos_x() + vProstokaty[5].szerokosc()/2) & x > rescaleX(vProstokaty[5].pos_x() - vProstokaty[5].szerokosc()/2)) faster();
        }
        if (x < rescaleX(vProstokaty[2].pos_x() + vProstokaty[2].szerokosc()/2) & x > rescaleX(vProstokaty[2].pos_x() - vProstokaty[2].szerokosc()/2)) slide_en = true;
    }
    if (state == GLUT_UP) slide_en = false;
}

void MousePassive(int x, int y)
{
    //sprintf(mouse_pos, "%d", x);
}

void MouseMotion(int x, int y)
{
    if (slide_en)
    {
        if (x < rescaleX(vProstokaty[2].pos_x() + vProstokaty[2].szerokosc()/2) & x > rescaleX(vProstokaty[2].pos_x() - vProstokaty[2].szerokosc()/2))
        {
            if ((vProstokaty[2].pos_x() > -0.5) & ((click_pos + GLdouble(x))/125) < 0.5) vProstokaty[2].ustaw((click_pos + GLdouble(x))/125, 0);
            else if ((vProstokaty[2].pos_x() < 0.5) & ((click_pos + GLdouble(x))/125) > -0.5) vProstokaty[2].ustaw((click_pos + GLdouble(x))/125, 0);
            dy *= speed_factor;
            speed_factor = 2000 - 2000 * vProstokaty[2].pos_x();
            licz_wspolrzedne();
        }
    }
}

void SetCallbackFunctions()
{
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(FunkcjaDoObslugiKlawiatury);
    glutKeyboardUpFunc(KeyboardUpFunc);
    glutMouseFunc(MouseFunc);
    glutPassiveMotionFunc(MousePassive);
    glutMotionFunc(MouseMotion);
}





int main(int argc, char *argv[])
{
    srand(time(NULL));

    kolor k1 = { 1,0,0 };
    kolor k2 = { 0,1,0 };
    kolor k3 = { 0,0.5,1 };
    kolor k4 = {0, 0, 0};
    vProstokaty.push_back(Prostokat(0, 0, 0.2, 1.5, k2));
    vProstokaty.push_back(vProstokaty[0]);
    vProstokaty.push_back(Prostokat(0.0, 0, 1.4, 0.15, k4));
    vProstokaty.push_back(Prostokat(0.0, 0, 2.4, 0.15, kolor({0.9, 0.9, 0.9})));
    vProstokaty.push_back(Prostokat(-1.27, -2.4, 0.15, 0.15, k3));
    vProstokaty.push_back(Prostokat(1.27, -2.4, 0.15, 0.15, k3));
    glutInit(&argc, argv);
    InitGLUTScene("Ping-Pong");
    SetCallbackFunctions();

    // start GLUT event loop. It ends when user close the window.
    glutMainLoop();

    return 0;
}


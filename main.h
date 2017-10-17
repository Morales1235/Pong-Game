#ifndef MAIN_H
#define MAIN_H

void InitGLUTScene(char *);
void SetCallbackFunctions();
void display();
void drawAll();
void drawTables();
void drawBorder();
void logic();
bool touch_border();
bool touch_Ltable();
bool touch_Rtable();
void faster();
void slower();
void changeDirectionOnLeft();
void changeDirectionOnRight();
void startGame(char);
void startGame();
double loss();
void licz_wspolrzedne();
void drawScores();
void drawBitmapText(char *, float, float);
void drawSlider();
void resize(int, int);
void idle();
void keyboardFunction(unsigned char, int, int);
void KeyboardUpFunc(unsigned char, int, int);
void MouseFunc(int, int, int, int);
void MouseMotion(int, int);
double rescaleX(double);
double rescaleY(double);

#endif // MAIN_H

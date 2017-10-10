/**
* \file Prostokat.h
* \author PUT Rover Programowanie
* \date 08-12-16
*/



//! The calss Prostokat allows drawing rectangles on the screen

/**
* You can set the dimensions of the rectangle
 Rectangles can be moved,rotated and its colour can be changed.

*/
#pragma once
#ifndef __Prostokat_h
#define __Prostokat_h
#include"sKolor.h"

class Prostokat {
protected:
    double m_x;			 ///< Stores the X coordinate of middle of the rectangle
    double m_y;			 ///< Stores the Y coordinate of middle of the rectangle
    double m_szerokosc;  ///< Stores the width of the rectangle
    double m_wysokosc;   ///< Stores the heigth of the rectangle
    kolor m_kolor;       /**< \brief Stores the colour of the rectangle
                        * Stores the 3 variables of colour (r, g, b - double type)*/
    double m_kat;		///< Stores the angle value(in degrees)
public:
    Prostokat(); /// Default class contructor
    Prostokat(double x, double y, double szerokosc, double wysokosc); /// The class constructor
    Prostokat(double x, double y, double szerokosc, double wysokosc, kolor kolor); /// The class constructor
    void rysuj();					       //! The methor draws made rectangle on screen
    void przesun(double dx,double dy);		//! The method changes coordinates of middle of the rectangle
											/**
                                                The method adds argument values (dx, dy) to
                                                corresponding rectangle coordinates (m_x, m_y).
                                                Makes the move of the rectangle
                                                \param dx value of shift of rectangle on X axis
                                                \param dy value of shift of rectangle on Y axis
											*/
    void ustaw (double x, double y);
    void zmienKolor(kolor kolor);			//! The method changes rectangle colour to set in argument
    void ustawKat(double kat);				//! The method sets angle value to set in argument
    void obroc(double dx);					//! The method changes the value of angle of rotation
											/**
                                            The method adds dx value to
                                            coordinate of angle of rotation (do wspolrzednej kata obrotu prostokata (m_kat)?).
                                            \param dx value of angle in degrees

											*/

    double wysokosc();					//! The methodc returns height of the rectangle
    double szerokosc();
    double kat();						//! The method returns angle of rotation value (type double)
    double pos_y();                     //!The method stores y pos of the rectangle
    double pos_x();

};


#endif

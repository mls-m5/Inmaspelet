/*
 * ImageFunctions.h
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "common.h"

namespace Images{

class Image{
public:
	unsigned int _num = 0;
	int _w = 0;
	int _h = 0;
	Image(){};
	Image(std::string filename){
		load(filename);
	}

	Image(int texNum, int width, int height){
		_num = texNum;
		_w = width;
		_h = height;
	}

	void load(std::string res);
	void convertFromSurface(SDL_Surface *surface);
	void draw(double x, double y, double angle,
			double w = 1, double h = 1, double alpha = 1);
};

class Color{
public:
	Color(double r, double g, double b, double a = 1)
:_r(r)
,_g(g)
,_b(b)
,_a(a)
{}

	double _r = 1;
	double _g = 1;
	double _b = 1;
	double _a = 1;
};

SDL_Surface *createSurface(SDL_Surface *surf, int w, int h, bool transparent);

SDL_Surface* loadRawSurface(std::string res);
};

using Images::Image;


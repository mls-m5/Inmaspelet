/*
 * ImageFunctions.cpp
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

//#define GL_GLEXT_PROTOTYPES

//#include <GL/glew.h>
#include "Image.h"
#include "common.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <SDL2/SDL_opengl.h>
#include <math.h>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include <map>

/* SDL interprets each pixel as a 32-bit number, so our masks must depend
   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000;
#define rmask 0x00ff0000;
#define rmask 0x0000ff00;
#define rmask 0x000000ff;
#else
#define rmask (0x000000ff)
#define gmask (0x0000ff00)
#define bmask (0x00ff0000)
#define amask (0xff000000)
#endif


static std::map<string, Image*> images;

SDL_Surface *Images::createSurface(SDL_Surface*surf, int w, int h, bool transparent){

	auto surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
			rmask, gmask, bmask, amask);

	SDL_Rect source;
	source.x = source.y = 0;
	source.w = surf->w;
	source.h = surf->h;
	auto dest = source;
	if (surf)
		SDL_BlitSurface(surf, &source, surface, &dest);
	return surface;
}

SDL_Surface* Images::loadRawSurface(string res) {
	SDL_Surface* bi;
	bi = IMG_Load(res.c_str());
	cout << "har läst in bild " << res << endl;
	if (!bi) {
		cout << "Kunde inte läsa in grafik: " << res << endl;
		//return NULL;
	}
	return bi;
}

void Image::load(string res) {
	auto f = images.find(res);

	if (f == images.end()){
		SDL_Surface *bi = loadRawSurface(res);
		convertFromSurface(bi);
		SDL_FreeSurface(bi);
		images[res] = this;
	}
	else {
		*this = *f->second;
	}
}

void Image::convertFromSurface(SDL_Surface* surface) {
	//////////////////////////////////////7
	GLuint texture;
	// This is a handle to our texture object
	//	SDL_Surface* surface = surface; // This surface will tell us the details of the image
	GLenum texture_format;
	GLint nOfColors;
	if ((surface)) {

		// Check that the image's width is a power of 2
		if ((surface->w & (surface->w - 1)) != 0) {
			printf("warning: image.bmp's width is not a power of 2\n");
		}

		// Also check if the height is a power of 2
		if ((surface->h & (surface->h - 1)) != 0) {
			printf("warning: image.bmp's height is not a power of 2\n");
		}

		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4) // contains an alpha chann<el
		{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else if (nOfColors == 3) // no alpha channel
		{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		} else {
			cout << "warning: the image is not truecolor..  this will probably break\n" << endl;
			// this error should not go unhandled
		}

		// Have OpenGL generate a texture object handle for us
		glGenTextures(1, &texture);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, texture);

		// Set the texture's stretching properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
				texture_format, GL_UNSIGNED_BYTE, surface->pixels);
		_num = texture;
	}
	else {
		_num = 0;
	}
}

void Images::Image::draw(double x, double y, double angle,
		double w, double h, double alpha) {
	glBindTexture(GL_TEXTURE_2D, _num);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	{
		glTranslated(x, y, 0);
		glScaled(w, h, 0);
		glRotated(angle * 180. / pi, 0,0,1);

		glBegin(GL_TRIANGLE_FAN);
		glColor4d(1,1,1,alpha);
		glTexCoord2d(0, 0);
		glVertex2d (-1, 1);
		glTexCoord2d(1, 0);
		glVertex2d (1, 1);
		glTexCoord2d(1, 1);
		glVertex2d(1, -1);
		glTexCoord2d(0, 1);
		glVertex2d(-1, -1);
		glEnd();

	}
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

/*
 * ImageFunctions.cpp
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

//#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
#include "imagefunctions.h"
#include "common.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <iosfwd>
#include <GL/gl.h>
#include <math.h>

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



GLuint ImageFunctions::levelPicFBO;

SDL_Surface * BackSurface;
static int ViewportHeight;
static int ViewportWidth;

SDL_Surface *ImageFunctions::createSurface(SDL_Surface*surf, int w, int h, bool transparent){

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

inline int
pow2roundup (int x)
{
	if (x < 0)
		return 0;
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x+1;
}

Image ImageFunctions::ConvertToImage(SDL_Surface* bi) {


	//Öker storleken så att gl blir glad
	int nw = (bi->w > bi->h)? bi->w: bi->h;
	nw = pow2roundup(nw);

	auto surface = createSurface(bi, nw,nw, false);

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
		if (nOfColors == 4) // contains an alpha channel
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
			printf(
					"warning: the image is not truecolor..  this will probably break\n");
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
	} else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		SDL_FreeSurface(surface);
		SDL_Quit();
		Image empty(0, 0,0, 0);
		return empty;
	}

	auto im = Image(texture, bi->w, bi->h,nw);
	// Free the SDL_Surface only if it was successfully created
	if (surface) {
		SDL_FreeSurface(surface);
	}
	return im;
}

SDL_Surface* ImageFunctions::loadRawSurface(bool CustomPath, string res) {
	SDL_Surface* bi;
	if (CustomPath) {
		bi = SDL_LoadBMP(res.c_str());
	} else {
		bi = SDL_LoadBMP(string("data/gfx/" + res + ".bmp").c_str());
	}
	if (!bi) {
		cout << "Kunde inte läsa in grafik: " << res << endl;
		//return NULL;
	}
	return bi;
}

Image ImageFunctions::loadImage(string res, bool CustomPath) {
	SDL_Surface *bi = loadRawSurface(CustomPath, res);

	//Gör om svart till alphalager
//	SDL_SetColorKey( bi, SDL_SRCCOLORKEY, SDL_MapRGB(bi->format, 0, 0, 0) );

	auto image = ConvertToImage(bi);
	SDL_FreeSurface(bi);

	return image;
}


void ImageFunctions::DrawPicture(int picNum, double x, double y, double w, double h,
		int rotateNum) {

	glColor4d(1,1,1,1);
	glBindTexture(GL_TEXTURE_2D, picNum);
	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glTexParameteri( GL_TEXTURE_2D,
	//	                 GL_TEXTURE_WRAP_T,
	//	                 GL_REPEAT );
	double x1 = x;
	double x2 = x + w;
	double y1 = y;
	double y2 = y + h;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(1,1,1);
	glTexCoord2d(0, 0 + 0);
	glVertex2d (x1, y1);
	glTexCoord2d(0 + 1, 0 + 0);
	glVertex2d (x2, y1);
	glTexCoord2d(0 + 1, 0 + 1);
	glVertex2d(x2, y2);
	glTexCoord2d(0 + 0, 0 + 1);
	glVertex2d(x1, y2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}
void ImageFunctions::InitImageFunctions(SDL_Surface *surface){

//	glewInit();

	BackSurface = surface;
	//	LoadBufferedImageToArray(ddCrossHair, "chassi");
}


void ImageFunctions::drawAirCircleToMap(int x, int y, int r) {
	//	Graphics2D g = ForePicture[ddLevel].createGraphics();
	//	g.setColor(new Color(ForePicture[ddLevel].getRGB(0, 0), true));
	//	g.fillOval(x - r, y - r, r * 2, r * 2);
	//	g.dispose();
}

unsigned int ImageFunctions::RGBToColor(int r, int g, int b, int a) {
	return SDL_MapRGBA(BackSurface->format,r,g,b,a);
}



void ImageFunctions::SetViewport(int x1, int y1, int w, int h) {
	glViewport(x1,y1,w,h);

	ViewportWidth = w;
	ViewportHeight = h;
}


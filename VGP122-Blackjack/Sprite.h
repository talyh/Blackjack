#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>
#include <sdl_mixer.h>

using namespace std;

class Sprite
{
public:
	Sprite();
	Sprite(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer = nullptr);
	~Sprite();
	void animate ( Uint16 start_frame, Uint16 end_frame);
	void move (int deltaX, int deltaY);	
	void draw( SDL_Renderer *renderer );
	
	void setCurrentFrame( Uint16 frame );
	void setRow( Uint16 row );
	Uint16 getRow();
	Uint16 getCurrentFrame();

	SDL_Texture *getImage();
	int getWidth();
	int getHeight();
	int getXPos();
	int getYPos();
	bool getVisibility();
	bool GetLoaded();
	string GetFilename();
	SDL_Rect* const GetSource();

	void setWidth(int width); // size of each fram
	void setHeight(int height); // size of each frame
	void setXPos(int x); // screen position in X
	void setYPos(int y); // screen position in y
	void setVisible(bool visible);

	void load(const char* filename, SDL_Renderer *renderer);

private:
	SDL_Texture *image; // the image that represents the sprite
	SDL_Rect source; // the source to use from that image
	int xpos, ypos;
	bool visible;
	string name;
	bool loaded;
	string filename;
};


#endif //SPRITE_H

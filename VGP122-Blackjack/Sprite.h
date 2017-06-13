#ifndef SPRITE_H
#define SPRITE_H

#include "Common.h"

class Sprite
{
public:
	Sprite(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer);
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

	void setWidth(int width);
	void setHeight(int height);
	void setXPos(int x);
	void setYPos(int y);
	void setVisible(bool visible);

private:
	void load(const char* filename, SDL_Renderer *renderer);

	SDL_Texture *image; // the image that represents the sprite
	SDL_Rect rect; // the rect to use from that image
	int xpos, ypos;
	bool visible;
	string name;
};


#endif //SPRITE_H

#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer)
{
	/** Set SDL_Rect variable in Sprite class */
	source.x = 0;
	source.y = 0;
	source.w = width;
	source.h = height;
	
	/** Set position variable of Sprite class */
	this-> xpos = xpos;
	this-> ypos = ypos;
	
	this->filename = filename;

	/** Set visibility of Sprite class */
	visible = true;

	if (renderer)
	/** Load image to use for Sprite */
	{
		load(this->filename.c_str(), renderer);
	}

	name = filename;

	cout << "Image " << name << " created" << endl;
}

Sprite::~Sprite()
{
	/** Delete any resources created */
	SDL_DestroyTexture(image);
}

void Sprite::load(const char* filename, SDL_Renderer* renderer) 
{
	/** Load picture for Sprite */
	image = IMG_LoadTexture(renderer, filename);
	
	/** Check if the Sprite was loaded */
	if (!image)
	{
		/** Bad stuff happened */
		cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
		exit(1);
	}
	else
	{
		loaded = true;
	}
}

void Sprite::draw( SDL_Renderer *renderer)
{
	/** Check if sprite should be drawn to the screen */
	if(this->visible)
	{
		/** Position sprite on Screen */
		SDL_Rect dest = {xpos, ypos, source.w, source.h};
		
		/** Draw Sprite to Screen */
		SDL_RenderCopy(renderer, image, &source, &dest);

		cout << "Image " << name << " drawn" << endl;
	}
	else
	{
		cout << "Couldn't draw " << name << endl;
	}
}

void Sprite::animate( Uint16 start_frame, Uint16 end_frame)
{
	/** Store current animation frame */
	Uint16 currentFrame = getCurrentFrame();
	
	/** Check if animation should be looped back to start */
	if (currentFrame < start_frame || currentFrame > end_frame)
	{
		/** Set animation frame back to start animation frame */
		currentFrame = start_frame;
	}
	else
	{
		/** Increment frame */
		currentFrame++;

		/** Check if animation is passed last animation frame */
		if (currentFrame > end_frame)
		{
			/** Set animation frame back to start animation frame */
			currentFrame = start_frame;
		}
	}
	
	/** Set current animation frame of Sprite */
	setCurrentFrame(currentFrame);
}

void Sprite::move(int deltaX, int deltaY)
{
	/** Move Sprite along X with appropriate value */
	xpos += deltaX;

	/** Move Sprite along Y with appropriate value */
	ypos += deltaY;
}

void Sprite::setCurrentFrame(Uint16 frame)
{
	/** Check if SDL_Rect was properly initialized */
	if (!source.w)
	{
		/** Not properly initialized so end function */
		return;
	}

	/** Calculate current frame of animation */
	source.x = frame * source.w;
}

void Sprite::setRow(Uint16 row)
{
	/** Check if SDL_Rect was properly initialized */
	if (!source.w)
	{
		/** Not properly initialized so end function */
		return;
	}

	/** Calculate current frame of animation */
	source.y = source.h * row;
}

Uint16 Sprite::getRow()
{
	/** Check if SDL_Rect was properly initialized */
	if (!source.w)
	{
		/** Not properly initialized so end function */
		return 0;
	}

	/** Calculate current frame of animation */
	return source.y / source.h;
}

Uint16 Sprite::getCurrentFrame()
{
	/** Check if SDL_Rect was properly initialized */
	if (!source.w)
	{
		/** Not properly initialized so end function */
		return 0;
	}

	/** Calculate current frame of animation */
	return source.x / source.w;
}

/** Create Getters and Setters for private variables */
SDL_Texture *Sprite::getImage()
{
	return this->image;
}

int Sprite::getWidth()
{
	return this->source.w;
}

int Sprite::getHeight()
{
	return this->source.h;
}

int Sprite::getXPos()
{
	return this->xpos;
}

int Sprite::getYPos()
{
	return this->ypos;
}

bool Sprite::getVisibility()
{
	return this->visible;
}

bool Sprite::GetLoaded()
{
	return loaded;
}

string Sprite::GetFilename()
{
	return filename;
}

void Sprite::setWidth(int width)
{
	this->source.w = width;
}

void Sprite::setHeight(int height)
{
	this->source.h = height;
}

void Sprite::setXPos(int x)
{
	this->xpos = x;
}

void Sprite::setYPos(int y)
{
	this->ypos = y;
}

void Sprite::setVisible(bool visible)
{
	this->visible = visible;
}
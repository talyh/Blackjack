#include "GameRender.h"

static vector<void*> itemsCreated; // to store items dynamically created so we can delete them afterwards

SDL_Window* window = nullptr; // the window for the project
SDL_Renderer* renderer = nullptr; // the renderer to use in that window
Sprite* background = nullptr;

TTF_Font *font = NULL; // the font we'll use throughout the game

Mix_Music *music = NULL; // the music listener to be used throughout the game

int GameRender::Initialize(string gameFont, int fontSize)
{
	/** Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cerr << "Unable to init SDL: " << SDL_GetError() << endl;
		return 1;
	}
	else
	{
		cout << "SDL_Init successful" << endl;
	}
	// Close SDL at program end
	atexit(SDL_Quit);

	// Initialize window Window for Project
	window = SDL_CreateWindow("Blackjack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		//return 1;
	} 
	else
	{
		cout << "Window created" << endl;
	}

	// Initialize Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		//return 1;
	}
	else
	{
		cout << "Renderer created" << endl;
	}

	// initialize font library
	if (TTF_Init() < 0)
	{
		cerr << "TTF_Init Error: " << TTF_GetError() << endl;
		return 1;
	}
	// Close TTF at program end
	atexit(TTF_Quit);

	// open font
	font = TTF_OpenFont(gameFont.c_str(), fontSize);
	if (!font)
	{
		cerr << "TTF_OpenFont Error: " << TTF_GetError() << endl;
	}

	// initialize SDL_Mixer
	if (Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) < 0)
	{
		cerr << "Mix_OpenAudio Error: " << Mix_GetError() << endl;
		return 1;
	}
	atexit(Mix_CloseAudio);

	return 0;
}

void GameRender::SetBackground(string backgroundImagePath)
{
	// create a new sprite, with the info provided
	//Sprite* background = NULL;
	background = new Sprite(backgroundImagePath.c_str(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	itemsCreated.push_back(background);

	DrawBackground();
}

void GameRender::SetMusic(string musicPath)
{
	// Load music sound file
	music = Mix_LoadMUS(musicPath.c_str());
	if (!music)
	{
		cerr << "Mix_LoadMUS Error: " << Mix_GetError() << endl;
	}
	else
	{
		cout << "Playing music " << musicPath << endl;
	}

	// play music
	Mix_PlayMusic(music, -1);
}

void GameRender::DrawBackground()
{
	// send the sprite to the renderer
	background->draw(renderer);

	// redraw the renderer
	SDL_RenderPresent(renderer);
}

void GameRender::DrawElement(string filename, int xPos, int yPos, int width, int height, Sprite** elementPtr)
{
	// create a new sprite, with the info provided
	Sprite* image = NULL;
	image = new Sprite(filename.c_str(), xPos, yPos, width, height, renderer);
	itemsCreated.push_back(image);

	// associate the sprite info to the sprite pointer, so the main game can reference it
	*elementPtr = image;

	// send the sprite to the renderer
	image->draw(renderer);

	// redraw the renderer
	SDL_RenderPresent(renderer);
}

void GameRender::DrawElement(Sprite* image, int xPos, int yPos, int width, int height)
{
	if (image)
	{
		// reposition and ensure image is visible
		image->setXPos(xPos);
		image->setYPos(yPos);
		image->setVisible(true);

		// send the sprite to the renderer
		image->draw(renderer);

		// redraw the renderer
		SDL_RenderPresent(renderer);
	}
	else
	{
		cout << "Cannot get image to draw" << endl;
	}
}

void GameRender::PrintText(string text, int xPos, int yPos, int size, SDL_Color color)
{
	cout << "Printing text " << text << endl;
		
	// set the text properties
	SDL_Color textColor = color;
	SDL_Rect dest = { xPos, yPos }; // set textbox position, but allow for size to be defined later on
	SDL_Surface *textbox = NULL; // the text image to be drawn to represent the text
	SDL_Texture *scoreTexture = NULL; // the texture to apply

	// set the style for the font
	TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);

	// set message for text
	textbox = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor, SCREEN_WIDTH - xPos);

	// convert the text to image
	scoreTexture = SDL_CreateTextureFromSurface(renderer, textbox);

	// set the size of the text
	dest.w = textbox->w;
	dest.h = textbox->h;

	// render the image
	SDL_RenderCopy(renderer, scoreTexture, nullptr, &dest);

	// update the screen
	SDL_RenderPresent(renderer);

	// free text resources
	SDL_FreeSurface(textbox);
	SDL_DestroyTexture(scoreTexture);
}

void GameRender::PlaySound(string sfxPath, int loops)
{
	// create a new chunk with the sound provided
	Mix_Chunk *sfx = NULL;
	sfx = Mix_LoadWAV(sfxPath.c_str());
	if (!sfx)
	{
		cerr << "Mix_LoadWAV Error: " << Mix_GetError() << endl;
	}
	else
	{
		cout << "Playing sound " << sfxPath << endl;
	}

	// play sound
	Mix_PlayChannel(-1, sfx, loops);

	// free resource
	while (!Mix_Playing(-1))
	{
		Mix_FreeChunk(sfx);
		sfx = NULL;
	}	
}

void GameRender::ClearScreen()
{
	SDL_RenderClear(renderer);
	DrawBackground();
}

void GameRender::Finish()
{
	// clean items created
	for (void* item : itemsCreated)
	{
		delete item;
		item = nullptr;
	}

	// free text resources
	TTF_CloseFont(font);

	// free audio resources
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	
	// free graphics resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

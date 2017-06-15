#include "GameRender.h"

static vector<void*> itemsCreated; // to store items dynamically created so we can delete them afterwards
static vector<GameRender::Component> savedComponents;

SDL_Window* GameRender::window;
SDL_Renderer* GameRender::renderer;
Sprite* GameRender::background;
TTF_Font* GameRender::font;
Mix_Music* GameRender::music;

int GameRender::Initialize(string gameFont, int fontSize)
{
	GameRender::window = NULL;
	renderer = NULL;
	background = NULL;
	font = NULL;
	music = NULL;
	
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

void GameRender::DrawElement(string filename, int xPos, int yPos, int width, int height, Sprite** elementPtr, string saveName)
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

	SaveComponent((saveName != "" ? saveName : filename), image->getImage(), { image->getXPos(), image->getYPos() });
}

void GameRender::DrawElement(Sprite* image, Position position)
{
	if (image)
	{
		if (!image->GetLoaded())
		{
			image->load(image->GetFilename().c_str() , renderer);
		}

		// reposition and ensure image is visible
		image->setXPos(position.xPos);
		image->setYPos(position.yPos);
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

void GameRender::DrawElement(Component* c)
{
	cout << "Drawing component " << c->name << endl;
	
	if (c->texture)
	{
		SDL_Texture* t = c->texture;
		SDL_Rect dest { c->position.xPos, c->position.yPos };
		SDL_QueryTexture(c->texture, nullptr, nullptr, &dest.w, &dest.h);
		SDL_RenderCopy(renderer, c->texture, nullptr, &dest);
	}
	else
	{
		cout << "Cannot get image to draw" << endl;
	}
}

void GameRender::DrawElement(Button* button)
{
	DrawElement(button->src, button->position.xPos, button->position.yPos, button->size.width, button->size.height, &(button->image), button->name);
	if (button->tooltip)
	{
		button->tooltip->setVisible(false);
		DrawElement(button->tooltipSrc, button->position.xPos + button->size.width + BUTTON_PADDING, button->position.yPos + button->size.height / 2, button->tooltipSize.width, button->tooltipSize.height, &(button->tooltip), button->name + "Tooltip");
	}
	itemsCreated.push_back(button->image);
	itemsCreated.push_back(button->tooltip);
}

void GameRender::DrawElement(Card* card, Position position)
{
	if (card->GetFaceUp())
	{
		DrawElement(card->GetImage(), position);
	}
	else
	{
		Sprite* cardBack = new Sprite(CARD_BACK_IMAGE.c_str(), position.xPos, position.yPos, CARD_WIDTH, CARD_HEIGHT, renderer);
		DrawElement(cardBack, position);
		delete cardBack;
		cardBack = nullptr;
	}
}

void GameRender::PrintText(Textbox* textbox, bool save)
{
	cout << "Printing text " << textbox->name << endl;

	// set the text properties
	SDL_Rect dest = { textbox->position.xPos, textbox->position.yPos }; // set textbox position, but allow for size to be defined later on
	SDL_Surface* surface = NULL; // the text image to be drawn to represent the text
	SDL_Texture* texture = NULL; // the texture to apply
		
	// set the style for the font
	TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);

	// set message for text
	surface = TTF_RenderText_Blended_Wrapped(font, textbox->value.c_str(), { 0,0,0 }, SCREEN_WIDTH - textbox->position.xPos);

	// convert the text to image
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	// set the size of the text
	dest.w = surface->w;
	dest.h = surface->h;

	textbox->size.width = dest.w;
	textbox->size.height = dest.h;

	// render the image
	SDL_RenderCopy(renderer, texture, nullptr, &dest);

	// update the screen
	SDL_RenderPresent(renderer);

	if (save)
	{
		SaveComponent(textbox->name, texture, {dest.x , dest.y} );
	}
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

void GameRender::ClearScreen(bool keepSavedItems)
{
	SDL_RenderClear(renderer);
	DrawBackground();

	if (keepSavedItems)
	{
		for (Component c : savedComponents)
		{
			DrawElement(&c);
		}
		SDL_RenderPresent(renderer);
	}
	else
	{
		savedComponents.clear();
	}
}

void GameRender::SaveComponent(string name, SDL_Texture * texture, Position position)
{
		Component c { name, texture, position.xPos, position.yPos };
		savedComponents.push_back(c);
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

// blok12_task3.cpp 
//

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);
	int getPosX();
	int getPosY();
	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
	int PosX;
	int PosY;
};

//The application time based timer
class LTimer
{
public:
	//Initializes variables
	LTimer();

	//The various clock actions
	void start();
	void stop();


	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font* gFont = NULL;

float gData;
//Scene textures
LTexture gTimeTextTexture;
LTexture gBestTimeTextTexture;

LTexture gButtonSpriteSheetTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	PosX = 0;
	PosY = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		PosX = 0;
		PosY = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	this->PosX = x;
	this->PosY = y;

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
int LTexture::getPosX()
{
	return PosX;
}

int LTexture::getPosY()
{
	return PosY;
}
LTimer::LTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	//Start the timer
	mStarted = true;



	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	//Stop the timer
	mStarted = false;



	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}



Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{

		time = SDL_GetTicks() - mStartTicks;

	}

	return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Blok12_task3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

//creating an arbitrary choice of height
int getRandomHeight(LTexture* texture)
{

	const int RandRangeHeight = SCREEN_HEIGHT - texture->getHeight() - 71;
	int newPosY = rand() % RandRangeHeight + 71;
//value search cycles
	while (newPosY<texture->getPosY()
		&& newPosY >(texture->getPosY() + texture->getHeight()))
	{

		newPosY = rand() % RandRangeHeight + 71;
	}

	return newPosY;
}

//create arbitrary width selection
int getRandomWidth(LTexture* texture)
{

	const int RandRangeWidth = SCREEN_WIDTH - texture->getWidth();
	int newPosx = rand() % RandRangeWidth + 1;
//value search cycles
	while (newPosx < texture->getPosX() &&
		(newPosx > (texture->getPosX() + texture->getWidth())))
	{

		newPosx = rand() % RandRangeWidth + 1;
	}

	return newPosx;
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;
	SDL_Color textColor = { 0, 0, 0, 0xFF };
	//Open the font
	gFont = TTF_OpenFont("Lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };




		if (!gButtonSpriteSheetTexture.loadFromFile("dot.bmp"))
		{
			printf("Failed to load button sprite texture!\n");
			success = false;
		}
	}
	SDL_RWops* file = SDL_RWFromFile("nums.bin", "r+b");

	//File does not exist
	if (file == NULL)
	{
		printf("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());

		//Create file for writing
		file = SDL_RWFromFile("nums.bin", "w+b");
		if (file != NULL)
		{
			printf("New file created!\n");


			gData = INT32_MAX;
			SDL_RWwrite(file, &gData, sizeof(float), 1);


			//Close file handler
			SDL_RWclose(file);
		}
		else
		{
			printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
	}
	//File exists
	else
	{
		//Load data
		printf("Reading file...!\n");

		SDL_RWread(file, &gData, sizeof(float), 1);


		//Close file handler
		SDL_RWclose(file);
	}



	gBestTimeTextTexture.loadFromRenderedText(std::to_string(gData), textColor);


	return success;

	return success;
}

bool isInsideClick(LTexture* texture, SDL_Event* e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);


	bool inside = true;


	if (x < texture->getPosX())
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > texture->getPosX() + texture->getWidth())
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < texture->getPosY())
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > texture->getPosY() + texture->getHeight())
	{
		inside = false;
	}
	return inside;
}
void close()
{
	//Free loaded images
	SDL_RWops* file = SDL_RWFromFile("nums.bin", "w+b");
	if (file != NULL)
	{


		SDL_RWwrite(file, &gData, sizeof(float), 1);


		//Close file handler
		SDL_RWclose(file);
	}
	else
	{
		printf("Error: Unable to save file! %s\n", SDL_GetError());
	}


	gTimeTextTexture.free();
	gBestTimeTextTexture.free();


	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	srand(time(NULL));
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			bool quit = false;

			SDL_Event e;
			int PosX = getRandomWidth(&gButtonSpriteSheetTexture);
			int PosY = getRandomHeight(&gButtonSpriteSheetTexture);

			SDL_Color textColor = { 0, 0, 0, 255 };



			LTimer timer;

			//In memory text stream
			std::stringstream timeText;
			//In memory text stream
			std::stringstream besttimeText;




			bool start = true;

			while (!quit)
			{

				if (start)
				{
					timer.start();

					start = false;
				}


				while (SDL_PollEvent(&e) != 0)
				{

					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}


					if ((e.type == SDL_MOUSEBUTTONDOWN) && isInsideClick(&gButtonSpriteSheetTexture, &e))
					{
						if (timer.getTicks() / 1000.f < gData)
						{
							gData = timer.getTicks() / 1000.f;
						}

						timer.stop();

						timer.start();
						PosX = getRandomWidth(&gButtonSpriteSheetTexture);
						PosY = getRandomHeight(&gButtonSpriteSheetTexture);



					}



				}

				timeText.str("");
				timeText << "Time " << (timer.getTicks() / 1000.f);

				besttimeText.str("");
				besttimeText << "Best time is : " << gData;

				//Render text
				if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
				{
					printf("Unable to render time texture!\n");
				}
				if (!gBestTimeTextTexture.loadFromRenderedText(besttimeText.str().c_str(), textColor))
				{
					printf("Unable to render time texture!\n");
				}
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);
				gButtonSpriteSheetTexture.render(PosX, PosY);
				gTimeTextTexture.render((SCREEN_WIDTH - gTimeTextTexture.getWidth() - gBestTimeTextTexture.getWidth()) / 4, 30);

				if (gData != INT32_MAX)
				{

					gBestTimeTextTexture.render(SCREEN_WIDTH - gBestTimeTextTexture.getWidth() - gBestTimeTextTexture.getWidth() / 3, 30);
				}

				SDL_RenderPresent(gRenderer);
			}
		}
	}


	close();

	return 0;
}
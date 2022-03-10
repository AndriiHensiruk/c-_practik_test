// blok11_task1.cpp 
//

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Texture wrapper class
class LTexture
{
public:

    //Initializes variables
    LTexture()
    {
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }

    //Deallocates memory
    ~LTexture()
    {
        free();
    }

    //Loads image at specified path
    bool loadFromFile(std::string path)
    {
        free();

        SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

            newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            if (newTexture == NULL)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            }
            else
            {
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }

            SDL_FreeSurface(loadedSurface);
        }

        mTexture = newTexture;
        return mTexture != NULL;
    }

    //Deallocates texture
    void free()
    {
        if (mTexture != NULL)
        {
            SDL_DestroyTexture(mTexture);
            mTexture = NULL;
            mWidth = 0;
            mHeight = 0;
        }
    }

    //Shows the dot on the screen
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
        SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        if (clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
    }

    int getWidth() { return mWidth; }

    int getHeight() { return mHeight; }

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};

class Dot
{
public:
    static const int DOT_WIDTH = 50;
    static const int DOT_HEIGHT = 50;

    static const int DOT_VEL = 1;

    Dot(int x, int y);

    void move(std::vector<SDL_Rect>& otherColliders);
    void move_one(std::vector<SDL_Rect>& otherColliders);

    void render();
    void render_one();

    std::vector<SDL_Rect>& getColliders();

private:
    int mPosX, mPosY;

    int mVelX, mVelY;

    std::vector<SDL_Rect> mColliders;

    void shiftColliders();
};

bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

LTexture gDotTexture;
LTexture gTexture;

Dot::Dot(int x, int y)
{
    mPosX = x;
    mPosY = y;

    mColliders.resize(11);

    mVelX = 0;
    mVelY = 0;

    mColliders[1].w = 20;
    mColliders[1].h = 20;

    shiftColliders();
}


void Dot::move(std::vector<SDL_Rect>& otherColliders)
{
    mPosX += 1;
    shiftColliders();

    if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(mColliders, otherColliders))
    {
        mPosX -= 1;
        shiftColliders();
    }

}

void Dot::move_one(std::vector<SDL_Rect>& otherColliders)
{
    mPosX -= 1;
    shiftColliders();

    if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(mColliders, otherColliders))
    {
        mPosX += 1;
        shiftColliders();
    }


}
void Dot::render()
{
    gDotTexture.render(mPosX, mPosY);
}

void Dot::render_one()
{
    gTexture.render(mPosX, mPosY);
}


void Dot::shiftColliders()
{
    int r = 0;

    for (int set = 0; set < mColliders.size(); ++set)
    {
        mColliders[set].x = mPosX + (DOT_WIDTH - mColliders[set].w) / 2;

        mColliders[set].y = mPosY + r;

        r += mColliders[set].h;
    }
}

std::vector<SDL_Rect>& Dot::getColliders()
{
    return mColliders;
}

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

            gWindow = SDL_CreateWindow("blok11_task1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    if (!gDotTexture.loadFromFile("dot.bmp"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gTexture.loadFromFile("dot.bmp"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    return success;
}

void close()
{
    gDotTexture.free();
    gTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    for (int Abox = 0; Abox < a.size(); Abox++)
    {
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        bottomA = a[Abox].y + a[Abox].h;

        for (int Bbox = 0; Bbox < b.size(); Bbox++)
        {
            leftB = b[Bbox].x;
            rightB = b[Bbox].x + b[Bbox].w;
            topB = b[Bbox].y;
            bottomB = b[Bbox].y + b[Bbox].h;

            if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
            {
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            bool quit = false;

            SDL_Event e;

            Dot dot(0, SCREEN_HEIGHT / 4);
            Dot otherDot(640, SCREEN_HEIGHT / 4);

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                }

                dot.move(otherDot.getColliders());
                otherDot.move_one(dot.getColliders());

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                dot.render();
                otherDot.render_one();

                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();

    return 0;
}
#include "LTexture.hpp"

LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::LTexture(int mW,int mH,SDL_Texture* mT) {
    mTexture = mT;
    mWidth = mW;
    mHeight = mH;
}
LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile( SDL_Renderer* gRenderer,std::string path ) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(SDL_Renderer* &gRenderer,TTF_Font* &gFont, std::string textureText, SDL_Color textColor ) {
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL ) {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    } else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL ) {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        } else {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}

void LTexture::free() {
    //Free texture if it exists
    if( mTexture != NULL ) {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ) {
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha ) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center,SDL_RendererFlip flip  ) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { pos.x, pos.y, mWidth, mHeight };
    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center,flip );
}
void LTexture::render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center,SDL_RendererFlip flip  ) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    pos.x = x;
    pos.y = y;
    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center,flip );
}

//getter
int LTexture::getWidth() {
    return mWidth;
}
int LTexture::getHeight() {
    return mHeight;
}
Vec2d LTexture::getPos() {
    return pos;
}
double LTexture::getPosX() {
    return pos.x;
}
double LTexture::getPosY() {
    return pos.y;
}
SDL_Rect LTexture::getRect() {
    SDL_Rect ansRect = {pos.x,pos.y,mWidth,mHeight};
    return ansRect;
}
//setter
void LTexture::setPos(Vec2d p) {
    pos = p;
}
void LTexture::setPos (double x,double y) {
    pos = Vec2d(x,y);
}
void LTexture::setPosX(double x) {
    pos.x=x;
}
void LTexture::setPosY(double y) {
    pos.y=y;
}
void LTexture::setHeight(int h) {
    mHeight=h;
}
void LTexture::setWidth(int w) {
    mWidth=w;
}




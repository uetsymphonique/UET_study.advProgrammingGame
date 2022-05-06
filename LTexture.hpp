#ifndef LTEXTURECLASS__
#define LTEXTURECLASS__
#include "params.hpp"
#include "Vec2d.hpp"
using std::string;
class LTexture {
  public:
    //constructor
    LTexture();
    LTexture(int mW,int mH,SDL_Texture* mT);

    //Deallocates memory
    ~LTexture();

    //Loads image
    bool loadFromFile(SDL_Renderer* gRenderer,std::string path);

    //Creates image from font string
    bool loadFromRenderedText(SDL_Renderer* &gRenderer,TTF_Font* &gFont, std::string textureText, SDL_Color textColor );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Set pos
    void setPos(Vec2d p);
    void setPos (double x,double y);
    void setPosX(double x);
    void setPosY(double y);
    void setHeight(int h);
    void setWidth(int w);
    void setAngle(double angle);


    //Renders texture at given point
    void render( SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE );
    void render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image informations
    int getWidth();
    int getHeight();
    double getPosX();
    double getPosY();
    Vec2d getPos();
    SDL_Rect getRect();
    SDL_Texture* getTexture(){return mTexture;}
  private:
    //The actual hardware texture
    SDL_Texture* mTexture;
  protected:
    double mAngle = 0.0;
    //Image dimensions
    int mWidth;
    int mHeight;
    Vec2d pos;
};

#endif // LTEXTURECLASS__

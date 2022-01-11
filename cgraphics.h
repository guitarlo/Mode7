#ifndef CGRAPHIC_H

#define CGRAPHIC_H
#include <SDL2/SDL.h>

typedef struct mode7params
{
    int space_z;
    int horizon;
    int scalex,scaley;

};
class cgraphic
{
    public:
        cgraphic(int resx,int resy);
        virtual ~cgraphic();
        void render(SDL_Surface* screen);
        void SetFullscreen(int i);
        void mode7(SDL_Surface *bmp,SDL_Surface *tile, float angle,float cx, float cy, mode7params *params);
        void mode7top(SDL_Surface *bmp,SDL_Surface *tile, float angle,float cx, float cy, mode7params *params);

        void putpixel(SDL_Surface *bmp ,int  x,int y,int c);
        Uint32 getpixel(SDL_Surface *bmp ,int  x,int y);

        SDL_Surface* screen;


    protected:
    private:
    SDL_Window *window;

};

#endif // CGRAPHIC_H

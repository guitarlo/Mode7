#include "cgraphics.h"
#include <stdio.h>
#include <math.h>
cgraphic::cgraphic(int resx,int resy)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "Mode7",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        resx,
        resy,
        SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN
    );


    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        delete this;
    }
    screen = SDL_GetWindowSurface( window );

}

cgraphic::~cgraphic()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void cgraphic::render(SDL_Surface* screen)
{
    SDL_UpdateWindowSurface(window);
}
void cgraphic::SetFullscreen(int i)
{
    SDL_SetWindowFullscreen(window,i);
}

void cgraphic::mode7 (SDL_Surface *screen,SDL_Surface *tile, float angle,float cx, float cy, mode7params *params)
{

    float screenx,screeny,
    distance,horizonscale;
    int maskx=tile->w-1,
    masky=tile->h-1;
    float spacex,spacey,
    linex,liney;

    for (screeny=(screen->h/2); screeny < screen->h;screeny++)
    {
        distance = (params->space_z * params->scaley) / (screeny + params->horizon);
        horizonscale=(distance / params->scalex);


        linex= (-SDL_sinf(angle) * horizonscale);
        liney= (SDL_cosf(angle) * horizonscale);


        spacex=cx+(distance * SDL_cosf(angle))- screen->w/2  * linex;
        spacey=cy+(distance * SDL_sinf(angle))- screen->h/2  * liney;


        for (screenx=0; screenx < screen->w;screenx++)
        {
            putpixel (screen,
                      (int)screenx,
                      (int)screeny,
                      getpixel (tile,
                                (int)spacex &maskx,
                                (int)spacey &masky ));

            spacex += linex;
            spacey += liney;
        }

    }

}

void cgraphic::mode7top (SDL_Surface *screen,SDL_Surface *tile, float angle,float cx, float cy, mode7params *params)
{

    float screenx,screeny,
    distance,horizonscale;
    int maskx=tile->w-1,
    masky=tile->h-1;
    float spacex,spacey,
    linex,liney;

    for (screeny=(screen->h/2); screeny > 0;screeny--)
    {
        distance = (params->space_z * params->scaley) / (screeny + params->horizon);
        horizonscale=(distance / params->scalex);


        linex= (-SDL_sinf(angle) * horizonscale);
        liney= (SDL_cosf(angle) * horizonscale);


        spacex=cx+(distance * SDL_cosf(angle))- screen->w/2  * linex;
        spacey=cy+(distance * SDL_sinf(angle))- screen->h/2  * liney;


        for (screenx=0; screenx < screen->w;screenx++)
        {
            putpixel (screen,
                      (int)screenx,
                      (int)screeny,
                      getpixel (tile,
                                (int)spacex &maskx,
                                (int)spacey &masky ));

            spacex += linex;
            spacey += liney;
        }

    }

}


void cgraphic::putpixel(SDL_Surface *bmp,int x, int y, int c)
{
    int bpp = bmp->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)bmp->pixels + y * bmp->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = c;
        break;

    case 2:
        *(Uint16 *)p = c;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (c >> 16) & 0xff;
            p[1] = (c >> 8) & 0xff;
            p[2] = c & 0xff;
        } else {
            p[0] = c & 0xff;
            p[1] = (c >> 8) & 0xff;
            p[2] = (c >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = c;
        break;
    }

}
Uint32 cgraphic::getpixel(SDL_Surface *bmp, int x, int y)
{
    int bpp = bmp->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)bmp->pixels + y * bmp->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;
    }
}

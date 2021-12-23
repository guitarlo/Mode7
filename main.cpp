#include <iostream>
#include "cgraphics.h"
using namespace std;


cgraphic *g;

SDL_Event e;
SDL_Surface *tile,*bg;

float posx=100,posy=100;
int quit;

float angle=0;
bool  moveup,movedown,turnleft,turnright;

mode7params params;

void ControlCheck();


int main(int argc, char *argv[])
{
    g=new cgraphic(1024,748);
    tile=SDL_LoadBMP("GFX/map.bmp");
    bg=SDL_LoadBMP("GFX/bg.bmp");
    SDL_Rect r_bg{0,0,1024,768};

    params.horizon=-350;
    params.scalex=500;
    params.scaley=500;
    params.space_z=20;

    while (!quit)
    {
        if (moveup)
        {
            posx+=SDL_cosf(angle)*1.5;
            posy+=SDL_sinf(angle)*1.5;
        }
        if (movedown)
        {
            posx-=SDL_cosf(angle)*2;
            posy-=SDL_sinf(angle)*2;
        }
        if(turnleft)
        {
            angle-=0.01;
            r_bg.x-=1;

        }
        if(turnright)
        {
            angle+=0.01;
            r_bg.x+=1;

        }

        if (r_bg.x <=0)
            r_bg.x+=1024;

        if (r_bg.x>=1024)
            r_bg.x+=-1024;


        //SDL_FillRect(g->screen,NULL,SDL_MapRGB(g->screen->format,0x00,0x00,0x00));
        SDL_BlitSurface(bg,&r_bg,g->screen,NULL);
        g->mode7(g->screen,tile,angle,posx,posy,&params);

        g->render(g->screen);
        ControlCheck();

    }

    delete g;
    return 0;
}
void ControlCheck()
{
    while(SDL_PollEvent(&e))
    {
    const Uint8*KeyStates=SDL_GetKeyboardState(NULL);
    turnleft=false;
    turnright=false;
    moveup=false;
    movedown=false;
    if (KeyStates[SDL_SCANCODE_ESCAPE])
        quit=true;

    if (KeyStates[SDL_SCANCODE_UP])
        moveup=true;

    if (KeyStates[SDL_SCANCODE_DOWN])
        movedown=true;

    if (KeyStates[SDL_SCANCODE_LEFT])
        turnleft=true;

    if (KeyStates[SDL_SCANCODE_RIGHT])
        turnright=true;


        if(e.type==SDL_QUIT)
            quit=true;
    }


}

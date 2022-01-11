#include <iostream>
#include "cgraphics.h"
using namespace std;


cgraphic *g;

SDL_Event e;
SDL_Surface *tile,*bg;
const int maxfps= 1000/60;
float posx=100,posy=100;
int quit;

float angle=0;
bool  moveup,movedown,turnleft,turnright;
Uint32 startTimer,delayTimer;
mode7params params,paramstop;


void ControlCheck();


int main(int argc, char *argv[])
{
    g=new cgraphic(1024,748);
    tile=SDL_LoadBMP("GFX/map.bmp");
    bg=SDL_LoadBMP("GFX/clouds.bmp");


    params.horizon=-350;
    params.scalex=500;
    params.scaley=500;
    params.space_z=20;


    paramstop.horizon=-350;
    paramstop.scalex=500;
    paramstop.scaley=500;
    paramstop.space_z=20;

    while (!quit)
    {
        startTimer=SDL_GetTicks();
        if (moveup)
        {
            posx+=SDL_cosf(angle)*4;
            posy+=SDL_sinf(angle)*4;
        }
        if (movedown)
        {
            posx-=SDL_cosf(angle)*2;
            posy-=SDL_sinf(angle)*2;
        }
        if(turnleft)
        {
            angle-=0.05;


        }
        if(turnright)
        {
            angle+=0.05;


        }




        SDL_FillRect(g->screen,NULL,SDL_MapRGB(g->screen->format,0xAA,0xAA,0xFF));

        g->mode7(g->screen,tile,angle,posx,posy,&params);
        g->mode7top(g->screen,bg,angle,-posx,-posy,&params);
        g->render(g->screen);
        ControlCheck();

    }

    delayTimer=SDL_GetTicks()-startTimer;
    if(delayTimer < maxfps)
        SDL_Delay(maxfps-delayTimer);
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

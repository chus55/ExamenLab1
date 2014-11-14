
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "PersonajeJugador.h"
#include "NPC.h"
#include "NPC2.h"
#include "NPC3.h"
#include <list>
#include <stdlib.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character, *game_over_win, *game_over_lose, *menu;
SDL_Rect rect_background,rect_character;

void loopGameOverWin()
{
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.type == SDL_KEYDOWN)
            {


                if(Event.key.keysym.sym == SDLK_ESCAPE)
                    return;
            }
        }

        SDL_RenderCopy(renderer, game_over_win, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}

void loopGameOverLose()
{
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.type == SDL_KEYDOWN)
            {


                if(Event.key.keysym.sym == SDLK_ESCAPE)
                    return;
            }
        }

        SDL_RenderCopy(renderer, game_over_lose, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}

void loopJuego1()
{
    bool jugador_vivo = true;
   list<Personaje*>personajes;
    personajes.push_back(new PersonajeJugador (0,0,renderer,&personajes));
    personajes.push_back(new NPC (50,175,renderer,&personajes));
    personajes.push_back(new NPC2 (225,150,renderer,&personajes));
    personajes.push_back(new NPC3 (175,80,renderer,&personajes));
    personajes.push_back(new NPC3 (125,50,renderer,&personajes));
    personajes.push_back(new NPC2 (190,150,renderer,&personajes));

    //Main Loop
    int frame=0;
    while(true)
    {
        frame++;
//        if(frame%100==0)
//            personajes.push_back(new NPC (100,rand() % 100,renderer,&personajes));
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.key.keysym.sym == SDLK_ESCAPE)
                    return;
        }

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->logic((Uint8*)SDL_GetKeyboardState( NULL ));

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->render(renderer);

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
        {
            if((*i)->player==true && (*i)->vivo==false)
            {
                jugador_vivo=false;
                personajes.erase(i);
                break;
            }
        }
        if(jugador_vivo==false)
        {
            loopGameOverLose();
            break;
        }

        if(personajes.size()==1)
        {
            loopGameOverWin();
            break;
        }


        SDL_RenderPresent(renderer);

        SDL_Delay(16.66);
    }
}

void loopMenu()
{

//Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.type == SDL_KEYDOWN)
            {


                if(Event.key.keysym.sym == SDLK_RETURN)
                    loopJuego1();

                    if(Event.key.keysym.sym == SDLK_DELETE)
                    return;
            }
        }

        SDL_RenderCopy(renderer, menu, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }

}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    game_over_win = IMG_LoadTexture(renderer,"assets/backgrounds/game_over_win.png");
    game_over_lose = IMG_LoadTexture(renderer,"assets/backgrounds/game_over_lose.jpg");
    menu = IMG_LoadTexture(renderer,"assets/backgrounds/menu.jpg ");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
//    SDL_QueryTexture(game_over_lose, NULL, NULL, &w, &h);
//    SDL_QueryTexture(game_over_win, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    character = IMG_LoadTexture(renderer, "assets/personaje/down1.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 100;
    rect_character.w = w;
    rect_character.h = h;

    loopMenu();

    return 0;
}

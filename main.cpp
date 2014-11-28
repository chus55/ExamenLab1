#include <iostream>
#include <fstream>
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "PersonajeJugador.h"
#include "NPC.h"
#include "NPC2.h"
#include "NPC3.h"
#include <list>
#include <stdlib.h>
#include <map>
#include <vector>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character, *game_over_win, *game_over_lose, *menu;
SDL_Rect rect_background,rect_character;

class Tile
{
public:
    int fuente_x;
    int fuente_y;
    int destino_x;
    int destino_y;
    Tile(int fuente_x, int fuente_y, int destino_x, int destino_y)
    {
        this-> fuente_x = fuente_x;
        this-> fuente_y = fuente_y;
        this-> destino_x = destino_x;
        this-> destino_y = destino_y;
    }
};
int randomizerX()
{
    return 1+rand()%(15-1);
}
int randomizerY()
{
    return 1+rand()%(8-1);
}

vector<Tile*> cargarTiles(string nombre_archivo)
{
    vector<Tile*>tiles;
    ifstream archivo(nombre_archivo.c_str());
    for(int destino_y =0; destino_y<8; destino_y++)
    {
        for(int destino_x =0; destino_x<16; destino_x++)
        {
            int fuente_x;
            int fuente_y;
            archivo>>fuente_x;
            archivo>>fuente_y;
            tiles.push_back(new Tile(fuente_x, fuente_y, destino_x, destino_y));
        }
    }
    archivo.close();
    return tiles;
}
vector<Tile*> cargarTiles2(string nombre_archivo)
{
    vector<Tile*>tiles;
    ifstream archivo(nombre_archivo.c_str());
    for(int destino_y =0; destino_y<1; destino_y++)
    {
        for(int destino_x =0; destino_x<1; destino_x++)
        {
            int fuente_x;
            int fuente_y;
            archivo>>fuente_x;
            archivo>>fuente_y;
            tiles.push_back(new Tile(fuente_x, fuente_y, destino_x, destino_y));
        }
    }
    archivo.close();
    return tiles;
}

void dibujarTile(SDL_Texture *tileset_texture, SDL_Renderer* renderer, int fuente_x, int fuente_y, int destino_x, int destino_y)
{
        SDL_Rect fuente, destino;
        fuente.x = 32*fuente_x;
        fuente.y = 32*fuente_y;
        fuente.w = 32;
        fuente.h = 32;

        destino.x = 32*destino_x;
        destino.y = 32*destino_y;
        destino.w = 32;
        destino.h = 32;

        SDL_RenderCopy(renderer, tileset_texture, &fuente, &destino);
};

void Save(string nombre_archivo, int x, int y)
{
    ofstream out(nombre_archivo.c_str());
    out<<x<<' ';
    out<<y;
    out.close();
}

//map Load(string nombre_archivo)
//{
//    ifstream in(nombre_archivo.c_str());
//    int x = 0;
//    int y = 0;
//    in>>x;
//    in>>y;
//    map<int,int> save;
//    save[x]=y;
//    return save;
//}

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
    ifstream in("save.txt");
    int x = 0;
    int y = 0;
    in>>x;
    in>>y;
    bool jugador_vivo = true;
    list<Personaje*>personajes;
    personajes.push_back(new PersonajeJugador (x,y,renderer,&personajes));
    personajes.push_back(new NPC (50,175,renderer,&personajes));
    personajes.push_back(new NPC2 (225,150,renderer,&personajes));
    personajes.push_back(new NPC3 (175,80,renderer,&personajes));
    personajes.push_back(new NPC3 (125,50,renderer,&personajes));
    personajes.push_back(new NPC2 (190,150,renderer,&personajes));

    SDL_Texture* tileset_texture = IMG_LoadTexture(renderer,"assets/backgrounds/terrain.png");
    vector<Tile*>tiles = cargarTiles("assets/tile.txt");
    vector<Tile*>tiles2 = cargarTiles2("assets/tile2.txt");
    int random1 = randomizerX();
    int random2 = randomizerY();

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
            if(Event.key.keysym.sym == SDLK_F1)
            {
                for(list<Personaje*>::iterator i = personajes.begin();
                        i!=personajes.end();
                        i++)
                {
                    if((*i)->player==true && (*i)->vivo==true)
                    {
                        int x = (*i)->rectangulo.x;
                        int y = (*i)->rectangulo.y;
                        Save("save.txt",x,y);
                    }
                }
            }
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        for(int i=0; i<tiles.size(); i++)
        {
            dibujarTile(tileset_texture, renderer,
                        tiles[i]->fuente_x, tiles[i]->fuente_y,
                        tiles[i]->destino_x, tiles[i]->destino_y);
        }
        for(int i=0; i<tiles2.size(); i++)
        {
            dibujarTile(tileset_texture, renderer,
                        tiles2[i]->fuente_x, tiles2[i]->fuente_y,
                        14, 5);
        }

//        dibujarTile(tileset_texture, renderer,15,0,5,4);
//        dibujarTile(tileset_texture, renderer,15,0,14,5);
//        dibujarTile(tileset_texture, renderer,15,0,1,3);
//        dibujarTile(tileset_texture, renderer,15,1,13,6);
//        dibujarTile(tileset_texture, renderer,15,1,11,1);
//        dibujarTile(tileset_texture, renderer,15,1,8,2);

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->logic((Uint8*)SDL_GetKeyboardState( NULL ));



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
        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
        {
            if((*i)->player==true && ((*i)->rectangulo.x==5*32 && (*i)->rectangulo.y==4*32)
               || ((*i)->rectangulo.x==14*32 && (*i)->rectangulo.y==5*32)
               || ((*i)->rectangulo.x==1*32 && (*i)->rectangulo.y==3*32)
               || ((*i)->rectangulo.x==13*32 && (*i)->rectangulo.y==6*32)
               || ((*i)->rectangulo.x==11*32 && (*i)->rectangulo.y==1*32)
               || ((*i)->rectangulo.x==8*32 && (*i)->rectangulo.y==2*32))
            {
                jugador_vivo=false;
                personajes.erase(i);
                break;
            }
        }
        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
        {
            if((*i)->player==true &&
                ((*i)->rectangulo.x==14*32 && (*i)->rectangulo.y==5*32)
               )
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
                {
                    Save("save.txt",0,0);
                    loopJuego1();
                }

                if(Event.key.keysym.sym == SDLK_DELETE)
                    return;

                if(Event.key.keysym.sym == SDLK_F2)
                        loopJuego1();
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

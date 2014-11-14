#ifndef PERSONAJE_H
#define PERSONAJE_H
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include <list>

using namespace std;

class Personaje
{
    public:
        SDL_Rect rectangulo;
        list<SDL_Texture*> texturas_up;
        list<SDL_Texture*> texturas_down;
        list<SDL_Texture*> texturas_left;
        list<SDL_Texture*> texturas_right;
        string orientacion;
        list<SDL_Texture*>::iterator textura_actual;
        list<Personaje*>*personajes;
        int frame;
        Personaje();
        bool player;
        bool vivo;
        virtual void logic(Uint8* currentKeyStates);
        virtual void render(SDL_Renderer* renderer);
        virtual ~Personaje();
        bool colision(SDL_Rect r1, SDL_Rect r2);
    protected:
    private:
};

#endif // PERSONAJE_H

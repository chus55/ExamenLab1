#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H

#include "Personaje.h"

class PersonajeJugador : public Personaje
{
    public:
        PersonajeJugador(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes);
        void logic(Uint8* currentKeyStates);
        virtual ~PersonajeJugador();
        virtual void render(SDL_Renderer* renderer);
        list<SDL_Texture*> ataque_arriba;
        list<SDL_Texture*> ataque_abajo;
        list<SDL_Texture*> ataque_derecha;
        list<SDL_Texture*> ataque_izquierda;
        string estado;
        int vida;
        SDL_Texture * rayo_texture;
        SDL_Texture * rayo2_texture;
        SDL_Rect rayo_rect;
        SDL_Rect rayo2_rect;
        bool rayo_activado;
        bool rayo2_activado;
        int rayo_frame_actual;
        int rayo_cooldown;
        string rayo_orientacion;
        string rayo2_orientacion;
    protected:
    private:
};

#endif // PERSONAJEJUGADOR_H

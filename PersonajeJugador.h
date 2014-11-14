#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H

#include "Personaje.h"

class PersonajeJugador : public Personaje
{
    public:
        PersonajeJugador(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes);
        void logic(Uint8* currentKeyStates);
        virtual ~PersonajeJugador();
        list<SDL_Texture*> ataque_arriba;
        list<SDL_Texture*> ataque_abajo;
        list<SDL_Texture*> ataque_derecha;
        list<SDL_Texture*> ataque_izquierda;
        string estado;
        int vida;
    protected:
    private:
};

#endif // PERSONAJEJUGADOR_H

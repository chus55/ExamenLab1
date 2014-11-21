#ifndef NPC3_H
#define NPC3_H

#include "Personaje.h"

class Personaje;

class NPC3 : public Personaje
{
    public:
        NPC3(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes);
        void logic(Uint8* currentKeyStates);
        virtual ~NPC3();
    protected:
    private:
};

#endif // NPC3_H

#ifndef NPC_H
#define NPC_H

#include "Personaje.h"

class Personaje;

class NPC : public Personaje
{
    public:
        NPC(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes);
        void logic(Uint8* currentKeyStates);
        virtual ~NPC();
    protected:
    private:
};

#endif // NPC_H

#ifndef NPC2_H
#define NPC2_H

#include "Personaje.h"

class Personaje;

class NPC2 : public Personaje
{
    public:
        NPC2(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes);
        void logic(Uint8* currentKeyStates);
        virtual ~NPC2();
    protected:
    private:
};

#endif // NPC2_H

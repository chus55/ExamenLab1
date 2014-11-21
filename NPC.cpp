#include "NPC.h"

NPC::NPC(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes)
{
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;
    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personajes/devil_down1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);

    texturas_down.push_back(textura);
    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personajes/devil_down2.png"));

    textura_actual=texturas_down.begin();

    orientacion="down";
    player = false;
    vivo = true;
}

NPC::~NPC()
{
    //dtor
}

void NPC::logic(Uint8* currentKeyStates)
{
    SDL_Rect temp = this->rectangulo;

    rectangulo.y++;
    if(rectangulo.y>250)
        rectangulo.y=0;

    for(list<Personaje*>::iterator i = personajes->begin();
            i!=personajes->end();
            i++)
    {
        if(this==(*i))
            continue;
        if(colision(this->rectangulo, (*i)->rectangulo))
            rectangulo=temp;
    }
}

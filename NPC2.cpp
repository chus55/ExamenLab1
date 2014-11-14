#include "NPC2.h"

NPC2::NPC2(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes)
{
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;
    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personajes/alien_right1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);

    texturas_down.push_back(textura);
    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personajes/alien_right2.png"));

    textura_actual=texturas_down.begin();

    orientacion="down";
    player = false;
    vivo = true;
}

NPC2::~NPC2()
{
    //dtor
}

void NPC2::logic(Uint8* currentKeyStates)
{
    SDL_Rect temp = this->rectangulo;

    rectangulo.x++;
    if(rectangulo.x>450)
        rectangulo.x=0;

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

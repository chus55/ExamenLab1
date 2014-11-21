#include "NPC3.h"
bool derecha = true;

NPC3::NPC3(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes)
{
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;
    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personajes/knight_right1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);

    texturas_down.push_back(textura);
    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personajes/knight_right2.png"));

    textura_actual=texturas_down.begin();

    orientacion="down";
    player = false;
    vivo = true;
}

NPC3::~NPC3()
{
    //dtor
}

void NPC3::logic(Uint8* currentKeyStates)
{
    SDL_Rect temp = this->rectangulo;
    if(derecha==true)
    rectangulo.x++;
    if(rectangulo.x>450)
        derecha=false;
    if(derecha==false)
        rectangulo.x--;
    if(rectangulo.x<0)
        derecha=true;

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

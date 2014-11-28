#include "PersonajeJugador.h"

PersonajeJugador::PersonajeJugador(int x, int y,SDL_Renderer* renderer,list<Personaje*>*personajes)
{
    this->rectangulo.x=x;
    this->rectangulo.y=y;
    this->personajes=personajes;

    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personajes/down1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);
    texturas_down.push_back(textura);

    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personajes/down2.png"));

    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personajes/up1.png"));
    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personajes/up2.png"));

    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personajes/izquierda1.png"));
    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personajes/izquierda2.png"));

    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personajes/derecha1.png"));
    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personajes/derecha2.png"));

    ataque_abajo.push_back(IMG_LoadTexture(renderer, "assets/personajes/ataque1.png"));
    ataque_derecha.push_back(IMG_LoadTexture(renderer, "assets/personajes/ataque2.png"));
    ataque_arriba.push_back(IMG_LoadTexture(renderer, "assets/personajes/ataque3.png"));
    ataque_izquierda.push_back(IMG_LoadTexture(renderer, "assets/personajes/ataque4.png"));

    orientacion="down";
    estado = "pasivo";
    player = true;
    vivo = true;
    vida=50;

    textura_actual = texturas_down.begin();
}

PersonajeJugador::~PersonajeJugador()
{
    //dtor
}

void PersonajeJugador::logic(Uint8* currentKeyStates)
{
    SDL_Rect temp = this->rectangulo;

    if(orientacion=="up" && estado=="ataque")
        {
            textura_actual=texturas_up.begin();
            estado = "pasivo";
        }
    if(orientacion=="down" && estado=="ataque")
        {
            textura_actual=texturas_down.begin();
            estado = "pasivo";
        }
    if(orientacion=="right" && estado=="ataque")
    {
            textura_actual=texturas_right.begin();
            estado = "pasivo";
    }
    if(orientacion=="left" && estado=="ataque")
        {
            textura_actual=texturas_left.begin();
            estado = "pasivo";
        }

    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        rectangulo.y-=1;
        if(orientacion!="up")
            textura_actual=texturas_up.begin();
        orientacion="up";
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        rectangulo.y+=1;
        if(orientacion!="down")
            textura_actual=texturas_down.begin();
        orientacion="down";
    }
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        rectangulo.x+=1;
        if(orientacion!="right")
            textura_actual=texturas_right.begin();
        orientacion="right";
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        rectangulo.x-=1;
        if(orientacion!="left")
            textura_actual=texturas_left.begin();
        orientacion="left";
    }
    if( currentKeyStates[ SDL_SCANCODE_SPACE] )
    {
        estado = "ataque";
        if(orientacion=="up")
        {
            textura_actual=ataque_arriba.begin();
        }
        if(orientacion=="down")
        {
            textura_actual=ataque_abajo.begin();
        }
        if(orientacion=="left")
        {
            textura_actual=ataque_izquierda.begin();
        }
        if(orientacion=="right")
        {
            textura_actual=ataque_derecha.begin();
        }
    }

    for(list<Personaje*>::iterator i = personajes->begin();i!=personajes->end();i++)
    {
        if(this==(*i))
            continue;
            if(colision(this->rectangulo, (*i)->rectangulo))
            {
                vida--;
            }
            if(vida==0)
            {
                vivo = false;
            }
        if(colision(this->rectangulo, (*i)->rectangulo) && estado=="ataque")
        {
            //rectangulo=temp;
            personajes->erase(i);
            break;
        }
    }
}

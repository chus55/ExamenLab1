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
    rayo_orientacion = orientacion;
    rayo2_orientacion = orientacion;
    estado = "pasivo";
    player = true;
    vivo = true;
    vida=50;
    rayo_texture = IMG_LoadTexture(renderer, "assets/ataques/rayo.png");
    rayo2_texture = IMG_LoadTexture(renderer, "assets/ataques/rayo2.png");
    SDL_QueryTexture(rayo_texture,NULL,NULL, &this->rayo_rect.w, &this->rayo_rect.h);
    SDL_QueryTexture(rayo2_texture,NULL,NULL, &this->rayo2_rect.w, &this->rayo2_rect.h);
    rayo_rect.x = 0;
    rayo_rect.y = 0;
    rayo2_rect.x = 0;
    rayo2_rect.y = 0;
    rayo_activado=false;
    rayo2_activado=false;

    rayo_cooldown = 100;
    rayo_frame_actual = 0;

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
    if(rayo_activado)
    {

        if(rayo_orientacion=="up")
        {
            rayo_rect.y -= 4;
        }
        if(rayo_orientacion=="down")
        {
            rayo_rect.y += 4;
        }
        if(rayo_orientacion=="left")
        {
            rayo_rect.x -= 4;
        }
        if(rayo_orientacion=="right")
        {
            rayo_rect.x += 4;
        }
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

    if( currentKeyStates[ SDL_SCANCODE_W] && rayo2_activado)
        {
            rayo2_rect.y -= 2;
        }
        if( currentKeyStates[ SDL_SCANCODE_S] && rayo2_activado)
        {
            rayo2_rect.y += 2;
        }
        if( currentKeyStates[ SDL_SCANCODE_A] && rayo2_activado)
        {
            rayo2_rect.x -= 2;
        }
        if( currentKeyStates[ SDL_SCANCODE_D] && rayo2_activado)
        {
            rayo2_rect.x += 2;
        }

    if(rayo_activado || rayo2_activado)
        rayo_frame_actual++;
    if(rayo_frame_actual>=rayo_cooldown)
    {
        rayo_activado = false;
        rayo2_activado = false;
    }

    if( currentKeyStates[ SDL_SCANCODE_Q] && !rayo_activado && !rayo2_activado)
    {
        rayo_orientacion = orientacion;
        rayo_activado=true;
        rayo_frame_actual = 0;
        rayo_rect.x = rectangulo.x;
        rayo_rect.y = rectangulo.y;
        estado = "ataque";
        if(orientacion=="up")
        {
            rayo_rect.y-=rectangulo.h;
        }
        if(orientacion=="down")
        {
            rayo_rect.y+=rectangulo.h;
        }
        if(orientacion=="left")
        {
            rayo_rect.x-=rectangulo.w;
        }
        if(orientacion=="right")
        {
            rayo_rect.x+=rectangulo.w;
        }

    }else if( currentKeyStates[ SDL_SCANCODE_E] && !rayo2_activado && !rayo_activado)
    {
        rayo2_orientacion = orientacion;
        rayo2_activado=true;
        rayo_frame_actual = 0;
        rayo2_rect.x = rectangulo.x;
        rayo2_rect.y = rectangulo.y;
        if(orientacion=="up")
        {
            rayo2_rect.y-=rectangulo.h;
        }
        if(orientacion=="down")
        {
            rayo2_rect.y+=rectangulo.h;
        }
        if(orientacion=="left")
        {
            rayo2_rect.x-=rectangulo.w;
        }
        if(orientacion=="right")
        {
            rayo2_rect.x+=rectangulo.w;
        }

    }else
    {
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
        if((colision(this->rayo_rect, (*i)->rectangulo) && rayo_activado) || (colision(this->rectangulo, (*i)->rectangulo) && estado=="ataque") || (colision(this->rayo2_rect, (*i)->rectangulo) && rayo2_activado))
        {
            //rectangulo=temp;
            personajes->erase(i);
            rayo_activado=false;
            rayo2_activado=false;
            break;
        }
    }
}

void PersonajeJugador::render(SDL_Renderer* renderer)
{
    Personaje::render(renderer);
    if(rayo_activado)
    {
        cout<<rayo_rect.y<<endl;
        SDL_RenderCopy(renderer, rayo_texture, NULL, &rayo_rect);
    }
    if(rayo2_activado)
    {
        SDL_RenderCopy(renderer, rayo2_texture, NULL, &rayo2_rect);
    }
}

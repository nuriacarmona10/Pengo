#include "Enemigo.h"
#include "iostream"

Enemigo::Enemigo(sf::Sprite *body, int posx, int posy)
{
    this->body = body;
    body->setPosition(posx,posy);

}
Enemigo::~Enemigo()
{
}
void Enemigo::Update()
{

}

void Enemigo::Draw(sf::RenderWindow &window, float percentTick)
{

    //float posx = prevPos.x * (1 - percentTick) + currentPos.x * percentTick;
    //float posy = prevPos.y * (1 - percentTick) + currentPos.y * percentTick;

    //body->setPosition(posx, posy);
    window.draw(*body);
}

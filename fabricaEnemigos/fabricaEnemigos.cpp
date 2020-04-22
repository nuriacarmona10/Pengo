#include "fabricaEnemigos.h"
#include <iostream>

fabricaEnemigos *fabricaEnemigos::instance = 0;

fabricaEnemigos::fabricaEnemigos()
{
    
    tex = new sf::Texture;
   if(!tex->loadFromFile("resources/Enemy.png")){
       std::cout<<"VA MAL ESTA MIERDA" <<std::endl;
   }
    body.setTexture(*tex);
    
}

fabricaEnemigos::~fabricaEnemigos()
{
}
fabricaEnemigos *fabricaEnemigos::getInstance()
{
    if (!instance)
    {
        instance = new fabricaEnemigos();
    }
    return instance;
}
Enemigo* fabricaEnemigos::crearEnemigo(int posx,int posy,int id)
{
    
    return new Enemigo(body,posx,posy, id);
}


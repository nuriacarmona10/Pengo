#ifndef FABRICAENEMIGOS_H
#define FABRICAENEMIGOS_H
#include "../Enemigo/Enemigo.h"
#include <SFML/Graphics.hpp>



class fabricaEnemigos
{
private:
    fabricaEnemigos(/* args */);
    static fabricaEnemigos* instance;
    sf::Sprite body;
    sf::Texture* tex;
public:
    ~fabricaEnemigos();
    static fabricaEnemigos* getInstance();
    Enemigo* crearEnemigo(int posx, int posy);
};

#endif
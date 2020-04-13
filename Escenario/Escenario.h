#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Enemigo/Enemigo.h"

#ifndef ESCENARIO_H
#define ESCENARIO_H

class Escenario
{
private:
    sf::Sprite *body;
    sf::Texture *tex;
    Escenario();
    std::vector<Enemigo *> enemigos;
    int **matriz;
    static Escenario *instance;

public:
    static Escenario *getInstance();
    void crearMatriz();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window, float percentTick);
    ~Escenario();
    void checkColisions(float timeElapsed);
    int** getMatriz();
};

#endif
#include <SFML/Graphics.hpp>

#ifndef ESCENARIO_H
#define ESCENARIO_H

class Escenario
{
private:
    sf::Sprite *body;
    sf::Texture *tex;
    Escenario();
    int** matriz;
    static Escenario *instance;

public:
    static Escenario *getInstance();
    void crearMatriz();
    void draw(sf::RenderWindow& window,float percentTick);
    ~Escenario();
};

#endif
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
    sf::Clock gameoverClock;
    std::vector<Enemigo *> enemigos;
    int **matriz;
    static Escenario *instance;
    int vida;
    bool gameover;
    std::vector<Enemigo *>::const_iterator it_enemy;
    //int **matrizVieja();

public:
    
    static Escenario *getInstance();
    //int **getMatrizVieja();
    void crearMatriz();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window, float percentTick);
    ~Escenario();
    void setVida();
    void checkColisions(float timeElapsed);
    int **getMatriz();
    void resetInstance();
    void resetEnemigos();
};

#endif
#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>

class Enemigo
{

private:
    sf::Sprite *body;
    sf::Texture *tex;
    bool muerto;
    int direccion;
    sf::Vector2f prevPos;
    sf::Vector2f velocity;
    sf::Vector2f currentPos;
    sf::IntRect rect;
    float tiempoTotal;
    sf::Vector2u imagenActual;
    bool Enpaso;

public:
    int getColumna();
    int getFila();
    void avanzar(int n, float deltaTime, sf::Vector2f velocity, int pos);
    bool checkColisions(int dir);
    void animacion(int row, float deltaTime, bool faceRight, int startFrame, int endFrame);
    Enemigo(sf::Sprite *body, int posx, int posy);
    ~Enemigo();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window, float percentTick);
};

#endif
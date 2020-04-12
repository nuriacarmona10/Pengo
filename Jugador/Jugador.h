#include <SFML/Graphics.hpp>
#include "../Escenario/Escenario.h"
#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador
{
public:
    static Jugador *getInstance();
    ~Jugador();
    void draw(sf::RenderWindow &window, float percentTick);
    void update(float deltaTime);
    void animacion(int row, float deltaTime, bool faceRight, int startFrame, int endFrame);
    void avanzar(int n,float deltaTime,sf::Vector2f velocity,int pos);

private:
    sf::IntRect rect;
    sf::Clock animationClock;
    bool Enpaso;
     sf::Vector2f posTecla;
    sf::Vector2f velocity;
    Jugador(/* args */);
    int ultimaTecla;
    sf::Sprite *body;
    sf::Texture *tex;
    static Jugador *instance;
    sf::Vector2f prevPos;
    sf::Vector2f currentPos;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
    enum Action
    {
        Idle,
        Punching,
        Shooting,
        Changing,
        Dying,
        Hit
    };
    Action accion;
};

#endif
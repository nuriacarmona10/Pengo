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
    void avanzar(int n, float deltaTime, sf::Vector2f velocity, int pos);
    bool checkColisions();
    bool checkColisionBlock();
    //getters and setters
    int getPosx();
    int getPosy();
    int getUltimaTecla();
    void updateMatriz(int fila, int colum);
    bool engolpe();
    bool getEngolpe();
    void setEngolpe(bool b);
    bool muriendo();
    void setMuriendo(bool b);
    void resetInstance();
    void moveBlock();
    bool getModoDios();

private:
    sf::IntRect rect;
    sf::Clock animationClock;
    sf::Clock dieClock;
    sf::Clock engolpeClock;
    sf::Clock PressGCLock;

    sf::Vector2i casillaViejaBlock;
    bool Enpaso;
    bool Muriendo;
    bool MovingBlock;
    bool modoDios;
    sf::Vector2f lastCasilla;
    sf::Vector2f posTecla;
    sf::Vector2f velocity;
    int vida;
    bool Engolpe;
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
};

#endif
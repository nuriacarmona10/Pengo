#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>

class Enemigo
{

private:
    sf::Sprite body;
    sf::Texture *tex;
    bool muerto;
    int id;
    int direccion;
    sf::Vector2i lastCasilla;
    sf::Vector2f posTecla; // posicion cuando le dio a la tec
    sf::Vector2f prevPos;
    sf::Vector2f velocity;
    sf::Vector2f currentPos;
    sf::Clock BloqueCLock;
    bool BloqueRoto;
    sf::IntRect rect;
    float tiempoTotal;
    sf::Vector2u imagenActual;
    sf::Vector2i BloqueAromper;
    bool Enpaso;
    bool MovingBlock;
    bool BrokenBlock;
    bool Muriendo;

public:
    int getColumna();
    int getFila();
    bool checkColisionBlock();
    void avanzar(int n, float deltaTime);
    bool checkColisions(int dir);
    void animacion(int row, float deltaTime, bool faceRight, int startFrame, int endFrame);
    Enemigo(sf::Sprite body, int posx, int posy);
    ~Enemigo();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window, float percentTick);
    void updateMatriz(int fila,int colum);
    int getDireccion();
    void setMuriendo();
    int getId();
   
};

#endif
#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>

class Enemigo
{

private:
    sf::Sprite *body;
    sf::Texture *tex;
    bool muerto;
    sf::Vector2f prevPos;
    sf::Vector2f currentPos;

public:
    Enemigo(sf::Sprite* body,int posx,int posy );
    ~Enemigo();
    void Update();
    void Draw(sf::RenderWindow &window, float percentTick);
};

#endif
#include "Enemigo.h"
#include "iostream"
#include "../Escenario/Escenario.h"
#include "../Jugador/Jugador.h"

#define kVel 3

Enemigo::Enemigo(sf::Sprite *body, int posx, int posy)
{
    this->body = body;
    body->setPosition(posx, posy);
    tiempoTotal = 0.0f;
    direccion = 3;
    Enpaso=false;
}
Enemigo::~Enemigo()
{
}
void Enemigo::Update(float deltaTime)
{

    velocity.x = 0;
    velocity.y = 0;
    prevPos.x = body->getPosition().x;
    prevPos.y = body->getPosition().y;
    if (Enpaso)
    {
        if (direccion == 1)
        {
            velocity.x = kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().x);
        }
        else if (direccion == 2)
        {
            velocity.x = -kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().x);
        }
        else if (direccion == 3)
        {
            velocity.y = +kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().y);
        }
        else if (direccion == 4)
        {
            velocity.y = -kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().y);
        }
    }
    else if (direccion == 1)
    { // derecha
        if (checkColisions(1))
        {
            animacion(3, deltaTime, true, 0, 3);
            velocity.x = kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().x);
        }
        else
        {
            direccion = rand() % (4 - 1 + 1) + 1; // (max-min+1)+min  me da un numero del 1 al 4
        }
    }
    if (direccion == 2)
    { // derecha
        if (checkColisions(2))
        {
            animacion(3, deltaTime, false, 0, 3);
            velocity.x = -kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().x);
        }
        else
        {
            direccion = rand() % (4 - 1 + 1) + 1;
        }
    }
    if (direccion == 3)
    { // derecha
        if (checkColisions(3))
        {
            animacion(2, deltaTime, true, 0, 3);
            velocity.y = kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().y);
        }
        else
        {
            direccion = rand() % (4 - 1 + 1) + 1;
        }
    }
    if (direccion == 4)
    { // derecha
        if (checkColisions(4))
        {
            animacion(1, deltaTime, true, 0, 3);
            velocity.y = -kVel;
            avanzar(direccion, deltaTime, velocity, body->getPosition().y);
        }
        else
        {
            direccion = rand() % (4 - 1 + 1) + 1;
        }
    }
    imagenActual.x = body->getPosition().x;
    imagenActual.y = body->getPosition().y;
}

void Enemigo::Draw(sf::RenderWindow &window, float percentTick)
{

    //float posx = prevPos.x * (1 - percentTick) + imagenActual.x * percentTick;
    //float posy = prevPos.y * (1 - percentTick) + currentPos.y * percentTick;

    //body->setPosition(posx, posy);
    window.draw(*body);
}
void Enemigo::animacion(int row, float deltaTime, bool faceRight, int startColum, int endColum)
{
    //rect = sf::IntRect(0 * 32, 10 * 32, 32, 32);
    float tiempoCambio = 0.2f;
    bool change = true;
    imagenActual.y = row;
    tiempoTotal += deltaTime;

    //comprueba si se ha cambiado la animacion para actualizar el frame inicial
    for (int i = startColum; i < endColum - 1; i++)
    {
        if (imagenActual.x == i)
            change = false;
    }
    if (change)
        imagenActual.x = startColum;

    //control para cambiar de sprite respecto al switch time
    if (tiempoTotal >= tiempoCambio)
    {
        tiempoTotal -= tiempoCambio;
        imagenActual.x++;
        if (imagenActual.x >= endColum)
        {
            imagenActual.x = startColum;
        }
    }

    rect.top = imagenActual.y * 32;

    //controlamos la orientacion del sprite

    if (faceRight)
    {
        rect = sf::IntRect(imagenActual.x * 32, imagenActual.y * 32, 32, 32);
    }

    else

    {

        rect = sf::IntRect((imagenActual.x + 1) * 32, imagenActual.y * 32, -32, 32);
    }

    body->setTextureRect(rect);
}
bool Enemigo::checkColisions(int dir)
{

    int **matriz = Escenario::getInstance()->getMatriz();
    //Jugador *player = Jugador::getInstance();
    sf::Vector2f destino;
    destino.x = getColumna();
    destino.y = getFila();

    if (dir == 1)
    {
        destino.x += 1;
    }
    else if (dir == 2)
    {
        destino.x -= 1;
    }
    else if (dir == 3)
    {
        destino.y += 1;
    }
    else if (dir == 4)
    {
        destino.y -= 1;
    }
    int casillay = destino.y;
    int casillax = destino.x;
    std::cout << "destino.x" << casillax << std::endl;
    std::cout << "destino.y" << casillay << std::endl;
    std::cout << "matriz colision" << matriz[casillay][casillax] << std::endl;

    if (matriz[casillay][casillax] == 2 || matriz[casillay][casillax] == 0 || matriz[casillay][casillax] == 5)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void Enemigo::avanzar(int dir, float deltaTime, sf::Vector2f velocity, int pos)
{
    // 1: derecha 2:izquierda 3:Down 4:Up

    int destino;
    Enpaso = true;
    int posJ = body->getPosition().x;

    if (dir == 1)
    {
        animacion(3, deltaTime, true, 0, 3);

        destino = abs(pos) + 32;
    }
    else if (dir == 2)
    {
        animacion(3, deltaTime, false, 0, 3);

        destino = abs(pos) - 32;
    }
    else if (dir == 3)
    {
        animacion(2, deltaTime, true, 0, 3);

        destino = abs(pos) + 32;
        posJ = body->getPosition().y;
    }
    else if (dir == 4)
    {
        animacion(1, deltaTime, true, 0, 3);

        destino = abs(pos) - 32;
        posJ = body->getPosition().y;
    }

    //aqui tengo que llamar al draw de alguna manera

    /*int esp = velocity.x * deltaTime + 1;*/

    //if (animationClock.getElapsedTime().asSeconds() > 0.002)
    //{
    // std::cout << "Tiempo:" << animationClock.getElapsedTime().asSeconds() << std::endl;
    //animationClock.restart();
    body->move(velocity);
    if (velocity.y == 0)
        posJ = body->getPosition().x;
    if (velocity.x == 0)
        posJ = body->getPosition().y;

    /* std::cout << "Esta:" << posJ << std::endl;

   std::cout << "quiere:" << destino << std::endl;*/
    //}
    if (posJ == destino)
    {
        Enpaso = false;
        //std::cout << "Enpaso:" << Enpaso << std::endl;
    }
}
int Enemigo::getColumna()
{
    return body->getPosition().x / 32;
}
int Enemigo::getFila()
{
    return body->getPosition().y / 32;
}
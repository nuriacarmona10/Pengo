#include "Escenario.h"
#include "../fabricaEnemigos/fabricaEnemigos.h"
#include "../Jugador/Jugador.h"

#include "iostream"
#define filas 20
#define columnas 23

Escenario *Escenario::instance = 0;

Escenario::Escenario(/* args */)
{
    matriz = new int *[filas];
    body = new sf::Sprite;
    tex = new sf::Texture;

    if (!tex->loadFromFile("resources/bloques32.png"))
    {
        std::cout << "Error cargando la imagen " << std::endl;
        exit(0);
    }
    body->setTexture(*tex);
    crearMatriz();
    sf::Vector2f pos;
    pos.x = 96;
    pos.y = 96;

    enemigos.push_back(fabricaEnemigos::getInstance()->crearEnemigo(96, 96));
}

Escenario::~Escenario()
{
}

void Escenario::update(float timeElapsed)
{

    checkColisions(timeElapsed);
}
void Escenario::checkColisions(float timeElapsed)
{
    int dir=-1;
    Jugador *player = Jugador::getInstance();
    sf::Vector2f destino;
    int playerx = player->getPosx(); // columna en la que esta 
    int playery = player->getPosy(); // fila en la que esta
    destino.x = playerx;
    destino.y = playery;
    if (player->getUltimaTecla() == 1)
    {
        destino.x = playerx + 1;
    }
    else if (player->getUltimaTecla() == 2)
    {
        destino.x = playerx - 1;
    }
    else if (player->getUltimaTecla() == 3)
    {
        destino.y = playery + 1;
    }
    else if (player->getUltimaTecla() == 4)
    {
        destino.y = playery - 1;
    }
    int casillay=destino.y;
    int casillax=destino.x;

    if (matriz[casillay][casillax] == 2)
    {
        Jugador::getInstance()->update(timeElapsed, player->getUltimaTecla());
    }
    else {
        Jugador::getInstance()->update(timeElapsed, dir);

    }
    
    Jugador::getInstance()->update(timeElapsed, dir);
}
void Escenario::draw(sf::RenderWindow &window, float percentTick)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (matriz[i][j] == 0)
            {
                body->setTextureRect(sf::IntRect(8 * 32, 3 * 32, 32, 32));
                body->setPosition(i * 32, j * 32);
                window.draw(*body);
            }
            else if (matriz[i][j] == 2)
            {
                body->setTextureRect(sf::IntRect(7 * 32, 0 * 32, 32, 32));
                body->setPosition(i * 32, j * 32);
                window.draw(*body);
            }
            else if (matriz[i][j] == 5)
            {
                body->setTextureRect(sf::IntRect(3 * 32, 1 * 32, 32, 32));
                body->setPosition(i * 32, j * 32);
                window.draw(*body);
            }
        }
    }

    enemigos[0]->Draw(window, percentTick);
}
void Escenario::crearMatriz()
{

    for (int i = 0; i < filas; i++)
    {
        matriz[i] = new int[columnas];
    }
    for (int i = 0; i < filas; i++)
    {
        std::cout << std::endl;

        for (int j = 0; j < columnas; j++)
        {

            if (i == 0 || i == filas - 1)
            {
                matriz[i][j] = 0;
            }
            else if (j == 0 || j == columnas - 1)
            {
                matriz[i][j] = 0;
            }
            else
            {
                int num = 1 + rand() % 4; // eso me saca 1 y 2 : 1 para vacio y 2 para bloques

                matriz[i][j] = num;
            }
            std::cout << matriz[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    // aquí saldrán los Snow-Bee
    matriz[3][3] = 4;
    matriz[18][21] = 4;
    matriz[15][17] = 4;
    //Aquí saldrán las gemas
    matriz[4][32] = 5;
    matriz[8][15] = 5;
    matriz[15][2] = 5;
    //aqui el zelda
    matriz[10][11] = 6;
}
Escenario *Escenario::getInstance()
{
    if (!instance)
    {
        instance = new Escenario();
    }
    return instance;
}
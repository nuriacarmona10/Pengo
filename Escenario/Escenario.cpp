#include "Escenario.h"
#include "../fabricaEnemigos/fabricaEnemigos.h"
#include "../Jugador/Jugador.h"

#include "iostream"
#define filas 20
#define columnas 20

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
    sf::Vector2f pos; // posicion enemigo
    pos.x = 96;
    pos.y = 96;

    enemigos.push_back(fabricaEnemigos::getInstance()->crearEnemigo(96, 96));
}

Escenario::~Escenario()
{
}

void Escenario::update(float timeElapsed)
{

    Jugador::getInstance()->update(timeElapsed);
    enemigos[0]->Update(timeElapsed);
    
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
                body->setPosition(j * 32, i * 32);
                window.draw(*body);
            }
            else if (matriz[i][j] == 2)
            {
                body->setTextureRect(sf::IntRect(7 * 32, 0 * 32, 32, 32));
                body->setPosition(j * 32, i * 32);
                window.draw(*body);
            }
            else if (matriz[i][j] == 5)
            {
                body->setTextureRect(sf::IntRect(3 * 32, 1 * 32, 32, 32));
                body->setPosition(j * 32, i * 32);
                window.draw(*body);
            }
            // std::cout << matriz[i][j] << "  ";
        }
        //std::cout << std::endl;
    }

    enemigos[0]->Draw(window, percentTick);
}
void Escenario::crearMatriz()
{
    std::cout << "MATRIZ CREAR" << std::endl;

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
                int num = rand() % (3 - 1 + 1) + 1; // eso me saca 1 y 2 : 1 para vacio y 2 para bloques

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
    matriz[10][10] = 6; // 10*32=320; 11*32=352
}
Escenario *Escenario::getInstance()
{
    if (!instance)
    {
        instance = new Escenario();
    }
    return instance;
}
int **Escenario::getMatriz()
{
    return matriz;
}
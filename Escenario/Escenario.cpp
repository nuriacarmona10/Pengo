#include "Escenario.h"
#include "../fabricaEnemigos/fabricaEnemigos.h"
#include "../Jugador/Jugador.h"

#include "iostream"
#define filas 20
#define columnas 20

Escenario *Escenario::instance = 0;

Escenario::Escenario(/* args */)
{
    contEnemys = 0;
    contEnemysNews = 0;
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
    vida = 2;
    enemigos.push_back(fabricaEnemigos::getInstance()->crearEnemigo(96, 96));
    enemigos.push_back(fabricaEnemigos::getInstance()->crearEnemigo(544, 320));
    enemigos.push_back(fabricaEnemigos::getInstance()->crearEnemigo(480, 64)); // arriba a la derecha
    gameover = false;
    win = false;
}

Escenario::~Escenario()
{
}

void Escenario::update(float timeElapsed)
{

    Jugador::getInstance()->update(timeElapsed);
    int cont = 0;
    for (it_enemy = enemigos.begin(); it_enemy != enemigos.end(); it_enemy++) // update de enemigos
    {
        enemigos[cont]->Update(timeElapsed);

        cont++;
    }
}

void Escenario::draw(sf::RenderWindow &window, float percentTick)
{
    if (!gameover && !win)
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
                else if (matriz[i][j] == 7)
                {

                    body->setTextureRect(sf::IntRect(2 * 32, 3 * 32, 32, 32));
                    body->setPosition(j * 32, i * 32);
                    window.draw(*body);
                }

                // std::cout << matriz[i][j] << "  ";
            }
            //std::cout << std::endl;
        }

        int cont = 0;
        for (it_enemy = enemigos.begin(); it_enemy != enemigos.end(); it_enemy++) // update de enemigos
        {
            if (enemigos[cont])
                enemigos[cont]->Draw(window, percentTick);

            cont++;
        }
        Jugador::getInstance()->draw(window, percentTick);
    }
    else if (gameover)
    {

        window.draw(*body);
        int time = gameoverClock.getElapsedTime().asSeconds();
        if (time > 2)
            resetInstance();
    }
    else if (win)
    {
        tex->loadFromFile("resources/win.jpg");
        body->setTexture(*tex);
        body->setPosition(220, 220);
        body->setOrigin(220, 220);
        body->setTextureRect(sf::IntRect(0, 0, 640, 640));
        window.draw(*body);
        window.draw(*body);
        int time = winClock.getElapsedTime().asSeconds();
        if (time > 2)
        {
            resetInstance();
            Jugador::getInstance()->resetInstance();
        }
    }
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
    matriz[10][17] = 4;
    matriz[2][15] = 4;
    //Aquí saldrán las gemas
    matriz[4][5] = 5;
    matriz[8][15] = 5;
    matriz[15][6] = 5;
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
void Escenario::resetInstance()
{
    delete instance;
    instance = NULL;
}
void Escenario::resetEnemigos(int fila, int columna)
{

    contEnemys++;
    int cont = 0;
    int i = 0;
    std::vector<Enemigo *>::const_iterator it{};
    for (it_enemy = enemigos.begin(); it_enemy != enemigos.end(); it_enemy++) // update de enemigos
    {
        // std::cout << "Enemigo Fila:  " << enemigos[cont]->getFila() << "  Enemigo Columna:  " << enemigos[cont]->getColumna() << std::endl;
        int siguientex = enemigos[cont]->getColumna();
        int siguientey = enemigos[cont]->getFila();
        if (enemigos[cont]->getDireccion() == 1)
        {
            siguientex += 1;
        }
        else if (enemigos[cont]->getDireccion() == 2)
        {
            siguientex -= 1;
        }
        else if (enemigos[cont]->getDireccion() == 3)
        {
            siguientey += 1;
        }
        else if (enemigos[cont]->getDireccion() == 4)
        {
            siguientey -= 1;
        }
        if ((enemigos[cont]->getColumna() == columna && enemigos[cont]->getFila()) == fila ||
            (enemigos[cont]->getColumna() == siguientex && enemigos[cont]->getFila() == siguientey))
        {
            i = cont;
            
            /*delete enemigos[cont];
            it_enemy = enemigos.erase(it_enemy);
            std::cout << "Entra a matar al enemigo" << std::endl;
            break;*/
        }
        /*else
        {
            ++it_enemy;
        }*/

        /* delete enemigos[cont];
            enemigos[cont] = enemigos.back();
            contEnemysNews++; */
    }

    //en la i tengo el que quiero eliminar
    if (enemigos[i] != enemigos.back()) // aqui compruebo que no sea el ultimo
    {
       std::cout<<"DIRECCION EN LA QUE VA : " <<enemigos[i]->getDireccion()<< std::endl;
       /* delete enemigos[i];
        enemigos[i] = enemigos.back();
        enemigos.pop_back();
        it_enemy=enemigos.end()-1;*/
    }
    else // si es el ultimo lo borro
    {
        enemigos.pop_back();
    }

    // ENEMIGO YA ELIMINADO

    if (contEnemysNews < 3)
        enemigos.push_back(fabricaEnemigos::getInstance()->crearEnemigo(256, 320)); // [8][10]
    if (contEnemys == 5)
    {
        std::cout << "Cuenta Enemigos Muertos: " << contEnemys << std::endl;
        win = true;
        winClock.restart();
    }

    cont++;
}
void Escenario::setVida()
{
    if (vida == 0)
    {
        tex->loadFromFile("resources/go.jpg");

        body->setTexture(*tex);
        body->setPosition(220, 300);
        body->setOrigin(220, 180);
        body->setTextureRect(sf::IntRect(0, 0, 640, 361));
        std::cout << "VIDAS: " << vida << std::endl;
        gameover = true;
        gameoverClock.restart();
    }
    else
    {
        vida--;
    }
}

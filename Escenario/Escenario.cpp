#include "Escenario.h"
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
}

Escenario::~Escenario()
{
}

Escenario *Escenario::getInstance()
{
    if (!instance)
    {
        instance = new Escenario();
    }
    return instance;
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
            else if(matriz[i][j]==2){
                 body->setTextureRect(sf::IntRect(7 * 32, 0 * 32, 32, 32));
                body->setPosition(i * 32, j * 32);
                window.draw(*body);
            }
            else if(matriz[i][j]==5) {
                body->setTextureRect(sf::IntRect(3 * 32, 1 * 32, 32, 32));
                body->setPosition(i * 32, j * 32);
                window.draw(*body);
            }
        }
    }
    
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
        std::cout<< std::endl;
    }
    // aquí saldrán los Snow-Bee
    /*matriz[3][3] = 4;
    matriz[20][30] = 3;
    matriz[15][17] = 3;*/
    //Aquí saldrán las gemas
    matriz[4][32] = 5;
    matriz[8][15] = 5;
    matriz[15][2] = 5;
    //aqui el zelda
    matriz[10][11]=6;

}
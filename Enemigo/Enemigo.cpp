#include "Enemigo.h"
#include "iostream"
#include "../Escenario/Escenario.h"
#include "../Jugador/Jugador.h"

#define kVel 4

Enemigo::Enemigo(sf::Sprite bodys, int posx, int posy)
{
    body = bodys;
    body.setPosition(posx, posy);
    body.setTextureRect(sf::IntRect(2 * 32, 0, 32, 32));
    tiempoTotal = 0.0f;
    direccion = 3;
    Enpaso = false;
    posTecla.x = posx;
    posTecla.y = posy;
    lastCasilla.x = posx / 32;
    lastCasilla.y = posy / 32;
    MovingBlock = false;
}
Enemigo::~Enemigo()
{
}
void Enemigo::Update(float deltaTime)
{

    velocity.x = 0;
    velocity.y = 0;
    prevPos.x = body.getPosition().x;
    prevPos.y = body.getPosition().y;
    
   /* std::cout << "Columna: " << getColumna() << std::endl;
    std::cout << "Fila: " << getFila() << std::endl;*/

    if (Enpaso)
    {
        // std::cout << "ENTRA 1" << std::endl;

        if (direccion == 1)
        {
            velocity.x = kVel;
            avanzar(direccion, deltaTime);
        }
        else if (direccion == 2)
        {
            velocity.x = -kVel;
            avanzar(direccion, deltaTime);
        }
        else if (direccion == 3)
        {
            velocity.y = +kVel;
            avanzar(direccion, deltaTime);
        }
        else if (direccion == 4)
        {
            velocity.y = -kVel;
            avanzar(direccion, deltaTime);
        }
    }

    else // si ya ha terminado el paso hasta la proxima casilla
    {
        velocity.x = 0;
        velocity.y = 0;

        if (!checkColisions(direccion)) // si no hay colision

        {
            animacion(3, deltaTime, true, 0, 3);
            /*if (direccion == 1 || direccion == 2) // I dont like this
                posTecla.y = body.getPosition().y;
            else
                posTecla.x = body.getPosition().x;*/

            avanzar(direccion, deltaTime);
        }

        else
        {

            direccion = rand() % (4 - 1 + 1) + 1; // (max-min+1)+min  me da un numero del 1 al 4
        }
        if (direccion == 1 || direccion == 2 || direccion == 3 || direccion == 4  )
        {
            checkColisionBlock();
        }

        imagenActual.x = posTecla.x;
        imagenActual.y = posTecla.y;
    }
    if(BrokenBlock) {
        animacion(4,deltaTime,true,0,4);
    }
    BrokenBlock=false;

}

void Enemigo::Draw(sf::RenderWindow &window, float percentTick)
{

    //float posx = prevPos.x * (1 - percentTick) + imagenActual.x * percentTick;
    //float posy = prevPos.y * (1 - percentTick) + currentPos.y * percentTick;

    //body.setPosition(posx, posy);
    window.draw(body);
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

    body.setTextureRect(rect);
}
bool Enemigo::checkColisions(int dir)
{
    Jugador *player = Jugador::getInstance();
    int **matriz = Escenario::getInstance()->getMatriz();
    //Jugador *player = Jugador::getInstance();
    sf::Vector2f destino;
    destino.x = getColumna();
    //std::cout << "Columna" << destino.x << std::endl;
    destino.y = getFila();
    //std::cout << "Fila " << destino.y << std::endl;

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
    // std::cout << "Comprobando destino:" << std::endl;
    /* std::cout << "destino.x" << casillax << std::endl;
    std::cout << "destino.y" << casillay << std::endl;
    std::cout << "matriz colision" << matriz[casillay][casillax] << std::endl;*/

    /* if (matriz[casillay][casillax] == 6)
    {   
        std::cout<<casillay<<" : "<< casillax << std::endl;
        player->engolpe();
        return true;
    }*/

    if (abs(body.getPosition().x - player->getPosx() * 32) <= 20 && abs(body.getPosition().y - player->getPosy() * 32) <= 20 && !player->muriendo() && !player->getModoDios())
    {
        if (!player->getEngolpe())
            player->setEngolpe(true);

        if (dir == 1 || dir == 3)
            direccion = 2;
        else if (dir == 2 || dir == 4)
            direccion = 1;
        return true;
    }
    else if (matriz[casillay][casillax] == 2 || matriz[casillay][casillax] == 0 || matriz[casillay][casillax] == 5)
    {
        // std::cout << " colision" <<  std::endl;

        return true;
    }

    else
    {
        //std::cout << "no colision" <<  std::endl;

        Enpaso = true;
        posTecla.x = destino.x * 32;
        posTecla.y = destino.y * 32;
        return false;
    }
}
void Enemigo::avanzar(int dir, float deltaTime)
{
    // 1: derecha 2:izquierda 3:Down 4:Up
    /* std::cout << "estoy en:" << body.getPosition().x << ", " << body.getPosition().y << std::endl;
       std::cout << "voy a:" << posTecla.x << ", " << posTecla.y << std::endl;
       std::cout << "direccion:" << dir << std::endl;*/
    int columna = 0;
    int fila = 0;

    //int destino = 0;
    Enpaso = true;
    //float posJ = body.getPosition().x;
    if (dir == 1)
    {
        animacion(3, deltaTime, true, 0, 3);
        velocity.x = kVel;
        columna = 1;
        //destino = posTecla.x + 32;
    }
    else if (dir == 2)
    {
        animacion(3, deltaTime, false, 0, 3);
        velocity.x = -kVel;
        columna = -1;
    }
    else if (dir == 3)
    {
        animacion(2, deltaTime, true, 0, 3);
        velocity.y = kVel;
        fila = 1;
    }
    else if (dir == 4)
    {
        animacion(1, deltaTime, true, 0, 5);
        velocity.y = -kVel;
        fila = -1;
    }

    //aqui tengo que llamar al draw de alguna manera

    /*int esp = velocity.x * deltaTime + 1;*/

    //if (animationClock.getElapsedTime().asSeconds() > 0.002)
    //{
    // std::cout << "Tiempo:" << animationClock.getElapsedTime().asSeconds() << std::endl;
    //animationClock.restart();
    body.move(velocity);
    /*if (velocity.y == 0)
        posJ = body.getPosition().x;
    if (velocity.x == 0)
        posJ = body.getPosition().y;*/

    /* std::cout << "Esta:" << posJ << std::endl;

   std::cout << "quiere:" << destino << std::endl;*/
    //}
    if (body.getPosition().x == posTecla.x && body.getPosition().y == posTecla.y)
    {
        Enpaso = false;
        updateMatriz(fila, columna); // fila y columna a la que va
        //std::cout << "Enpaso:" << Enpaso << std::endl;
    }
}
int Enemigo::getColumna()
{
    // std::cout << "Columna: " << abs(body.getPosition().x / 32 )<< std::endl;

    return body.getPosition().x/32;
}
int Enemigo::getFila()
{
    return body.getPosition().y/32;
}
void Enemigo::updateMatriz(int fila, int columna)
{
    int **matriz = Escenario::getInstance()->getMatriz();

    matriz[(int)lastCasilla.y][(int)lastCasilla.x] = 1;
    matriz[(int)lastCasilla.y + fila][(int)lastCasilla.x + columna] = 4;
    lastCasilla.x += columna;
    lastCasilla.y += fila;

    for (int i = 0; i < 20; i++)
    {
        // std::cout << "" << std::endl;
        for (int j = 0; j < 20; j++)
        {
            //  std::cout << matriz[i][j] << "  " << std::ends;
        }
    }
}
int Enemigo::getDireccion()
{
    return direccion;
}
bool Enemigo::checkColisionBlock()
{
    int **matriz = Escenario::getInstance()->getMatriz();
    sf::Vector2f destino;
    int enemyx = getColumna(); // columna en la que esta
    int enemyy = getFila();    // fila en la que esta
    destino.x = enemyx;
    destino.y = enemyy;
    sf::Vector2f siguiente;
    siguiente.x = enemyx;
    siguiente.y = enemyy;

    if (direccion == 1)
    {
        destino.x = enemyx + 1;
        siguiente.x = enemyx + 2;
    }
    else if (direccion == 2)
    {
        destino.x = enemyx - 1;
        siguiente.x = enemyx - 2;
    }
    else if (direccion == 3)
    {
        destino.y = enemyy + 1;
        siguiente.y = enemyy + 2;
    }
    else if (direccion == 4)
    {
        destino.y = enemyy - 1;
        siguiente.y = enemyy - 2;
    }
    int casillay = destino.y;
    int casillax = destino.x;
    int siguientex = siguiente.x;
    int siguientey = siguiente.y;

    /* std::cout << "player.x" << enemyx << std::endl;
   std::cout << "player.y" << enemyy << std::endl;
   std::cout << "destino.x" << casillax << std::endl;
   std::cout << "destino.y" << casillay << std::endl;
   std::cout << "matriz colision" << matriz[casillay][casillax] << std::endl;*/

    if (matriz[casillay][casillax] == 2)
    {
        // std::cout << "Fila que quiere:  " << casillay << "  Columna que quiere: " << casillax << std::endl;
        // std::cout << "Siguiente Fila : " << siguientey << "  Siguiente columna: " << siguientex << std::endl;

        if (matriz[siguientey][siguientex] == 2 || matriz[siguientey][siguientex] == 5 || matriz[siguientey][siguientex] == 0)
        {

            matriz[casillay][casillax] = 7; // aqui lo rompo
            BrokenBlock=true;
        }

        return true;
    }

    else
    {
        return false;
    }
}

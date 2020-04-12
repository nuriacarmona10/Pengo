#include "Jugador.h"
#include "iostream"
#define kVel 4;

Jugador *Jugador::instance = 0;

Jugador::Jugador(/* args */)
{
   tex = new sf::Texture;
   body = new sf::Sprite;
   tex->loadFromFile("resources/Zelda32.png");
   body->setPosition(320, 352);
   body->setTexture(*tex);
   switchTime = 0.2f;
   totalTime = 0.0f;
   Enpaso = false;
   animationClock.restart();
   posTecla.x = 0;
   posTecla.y = 0;
}
Jugador::~Jugador()
{
}
Jugador *Jugador::getInstance()
{
   if (!instance)
   {
      instance = new Jugador();
   }
   return instance;
}

void Jugador::update(float deltaTime, int dir)
{
   bool moveD = true;
   bool moveI = true;
   bool moveDw = true;
   bool moveUp = true;
   velocity.x = 0;
   velocity.y = 0;
   prevPos.x = body->getPosition().x;
   prevPos.y = body->getPosition().y;

  
    // significa que quiere ir contra un muro y vamos a bloquear el movimiento
      if (dir == 1)
         moveD = false;
      else if (dir == 2)
         moveI = false;
      else if (dir == 3)
         moveDw = false;
      else if (dir == 4)
         moveUp = false;
   
   if (Enpaso)
   {
      if (ultimaTecla == 1)
      {
         velocity.x = kVel;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.x);
      }
      else if (ultimaTecla == 2)
      {
         velocity.x = -kVel;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.x);
      }
      else if (ultimaTecla == 3)
      {
         velocity.y = +kVel;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.y);
      }
      else if (ultimaTecla == 4)
      {
         velocity.y = -kVel;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.y);
      }
   }

   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && moveD)
   {
      velocity.x = kVel;
      ultimaTecla = 1;
      posTecla.x = body->getPosition().x;
      avanzar(ultimaTecla, deltaTime, velocity, posTecla.x);
   }

   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && moveI)
   {
      velocity.x = -kVel;
      ultimaTecla = 2;
      posTecla.x = body->getPosition().x;

      avanzar(ultimaTecla, deltaTime, velocity, posTecla.x);
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && moveDw)
   {
      velocity.y = +kVel;
      ultimaTecla = 3;
      posTecla.y = body->getPosition().y;
      avanzar(ultimaTecla, deltaTime, velocity, posTecla.y);
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && moveUp)
   {
      velocity.y = -kVel;
      ultimaTecla = 4;
      posTecla.y = body->getPosition().y;
      avanzar(ultimaTecla, deltaTime, velocity, posTecla.y);
   }

   else if (velocity.x == 0.0 && velocity.y == 0.0)
   {
      if (ultimaTecla == 1)
      {
         animacion(11, deltaTime, true, 0, 7);
      }
      else if (ultimaTecla == 2)
      {
         animacion(11, deltaTime, false, 0, 7);
      }
      else if (ultimaTecla == 3)
      {
         animacion(10, deltaTime, true, 0, 7);
      }
      else if (ultimaTecla == 4)
      {
         animacion(12, deltaTime, true, 0, 7);
      }
      else
      {
         animacion(10, deltaTime, true, 0, 7);
      }
   }

   // body->move((velocity * deltaTime));

   currentPos.x = body->getPosition().x;
   currentPos.y = body->getPosition().y;
}
void Jugador::draw(sf::RenderWindow &window, float percentTick)
{
   // std::cout<< "Entra a DRAW" <<std::endl;
   /* std::cout << "Recta top:" << rect.top << std::endl;
   std::cout << "Recta left:" << rect.left << std::endl;*/

   float posx = prevPos.x * (1 - percentTick) + currentPos.x * percentTick;
   float posy = prevPos.y * (1 - percentTick) + currentPos.y * percentTick;

   // body->setPosition(body->getPosition().y, body->getPosition().x);

   window.draw(*body);
}
void Jugador::animacion(int row, float deltaTime, bool faceRight, int startFrame, int endFrame)
{
   //rect = sf::IntRect(0 * 32, 10 * 32, 32, 32);

   bool change = true;
   currentImage.y = row;
   totalTime += deltaTime;

   //comprueba si se ha cambiado la animacion para actualizar el frame inicial
   for (int i = startFrame; i < endFrame - 1; i++)
   {
      if (currentImage.x == i)
         change = false;
   }
   if (change)
      currentImage.x = startFrame;

   //control para cambiar de sprite respecto al switch time
   if (totalTime >= switchTime)
   {
      totalTime -= switchTime;
      currentImage.x++;
      if (currentImage.x >= endFrame)
      {
         currentImage.x = startFrame;
      }
   }

   rect.top = currentImage.y * 32;

   //controlamos la orientacion del sprite

   if (faceRight)
   {
      rect = sf::IntRect(currentImage.x * 32, currentImage.y * 32, 32, 32);
   }

   else

   {

      rect = sf::IntRect((currentImage.x + 1) * 32, currentImage.y * 32, -32, 32);
   }

   body->setTextureRect(rect);
}
void Jugador::avanzar(int dir, float deltaTime, sf::Vector2f velocity, int pos)
{
   // 1: derecha 2:izquierda 3:Down 4:Up

   int destino;
   Enpaso = true;
   float posJ = body->getPosition().x;
   if (dir == 1)
   {
      animacion(1, deltaTime, true, 0, 5);

      destino = abs(pos) + 32;
   }
   else if (dir == 2)
   {
      animacion(1, deltaTime, false, 0, 5);

      destino = abs(pos) - 32;
   }
   else if (dir == 3)
   {
      animacion(0, deltaTime, true, 0, 5);

      destino = abs(pos) + 32;
      posJ = body->getPosition().y;
   }
   else if (dir == 4)
   {
      animacion(2, deltaTime, true, 0, 5);

      destino = abs(pos) - 32;
      posJ = body->getPosition().y;
   }

   //aqui tengo que llamar al draw de alguna manera

   /*int esp = velocity.x * deltaTime + 1;*/

   //if (animationClock.getElapsedTime().asSeconds() > 0.002)
   //{
   std::cout << "Tiempo:" << animationClock.getElapsedTime().asSeconds() << std::endl;
   //animationClock.restart();
   body->move(velocity);
   if (velocity.y == 0)
      posJ = body->getPosition().x;
   if (velocity.x == 0)
      posJ = body->getPosition().y;

   std::cout << "Esta:" << posJ << std::endl;

   std::cout << "quiere:" << destino << std::endl;
   //}
   if (posJ == destino)
   {
      Enpaso = false;
      std::cout << "Enpaso:" << Enpaso << std::endl;
   }
}
int Jugador::getPosx()
{
   return body->getPosition().x / 32;
}
int Jugador::getPosy()
{
   return body->getPosition().y / 32;
}
int Jugador::getUltimaTecla()
{
   return ultimaTecla;
}
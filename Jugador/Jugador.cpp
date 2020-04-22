#include "Jugador.h"
#include "iostream"
#define kVel 8;

Jugador *Jugador::instance = 0;

Jugador::Jugador(/* args */)
{
   tex = new sf::Texture;
   body = new sf::Sprite;
   tex->loadFromFile("resources/Zelda32.png");
   body->setPosition(320, 320);
   body->setTexture(*tex);
   body->setTextureRect(sf::IntRect(0 * 32, 10 * 32, 32, 32));
   switchTime = 0.2f;
   totalTime = 0.0f;
   Enpaso = false;
   Engolpe = false;
   animationClock.restart();
   posTecla.x = 0;
   posTecla.y = 0;
   lastCasilla.x = 10;
   lastCasilla.y = 10;
   vida = 2;
   Muriendo = false;
   MovingBlock = false;
   modoDios = false;
   BrokenBlock = false;
   BloqueRoto = false;
   contadorcito = 0;
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

void Jugador::update(float deltaTime)
{

   velocity.x = 0;
   velocity.y = 0;
   prevPos.x = body->getPosition().x;
   prevPos.y = body->getPosition().y;

   // significa que quiere ir contra un muro y vamos a bloquear el movimiento

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
   else if (Muriendo)
   {
      animacion(9, deltaTime, true, 0, 11);
      //dieClock.restart();
      if (muriendo())
      {
         resetInstance();
         Escenario::getInstance()->setGameOver(true);
      }
   }

   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
   {
      velocity.x = kVel;
      ultimaTecla = 1;
      if (checkColisions())
      {
         posTecla.x = body->getPosition().x;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.x);
      }
   }

   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
   {
      velocity.x = -kVel;
      ultimaTecla = 2;
      if (checkColisions())
      {
         posTecla.x = body->getPosition().x;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.x);
      }
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
   {
      velocity.y = +kVel;
      ultimaTecla = 3;
      if (checkColisions())
      {
         posTecla.y = body->getPosition().y;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.y);
      }
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
   {
      velocity.y = -kVel;
      ultimaTecla = 4;
      if (checkColisions())
      {
         posTecla.y = body->getPosition().y;
         avanzar(ultimaTecla, deltaTime, velocity, posTecla.y);
      }
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
   {
      checkColisionBlock();

      // std::cout << "ha roto el bloque" << std::endl;
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
   {

      modoDios = true;
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
   {
      dieClock.restart();
      Muriendo = true;
   }
   else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
   {
      Escenario::getInstance()->playerWin();
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

   if (Engolpe && !Muriendo)
   {
      animacion(6, deltaTime, true, 0, 2);
      //engolpeClock.restart();
      //std::cout<<"TIEMPECITO"<<time<< std::endl;
      engolpe();
      vida--;
   }
   if (MovingBlock)
   {
      if (ultimaTecla == 1)
      {
         animacion(4, deltaTime, true, 0, 8);
      }
      else if (ultimaTecla == 2)
      {
         animacion(4, deltaTime, false, 0, 8);
      }
      else if (ultimaTecla == 3)
      {
         animacion(3, deltaTime, true, 0, 8);
      }
      else if (ultimaTecla == 4)
      {
         animacion(5, deltaTime, true, 0, 8);
      }

      moveBlock();
   }
   if (BrokenBlock)
   {

      if (ultimaTecla == 1)
      {
         animacion(4, deltaTime, true, 0, 8);
      }
      else if (ultimaTecla == 2)
      {
         animacion(4, deltaTime, false, 0, 8);
      }
      else if (ultimaTecla == 3)
      {
         animacion(3, deltaTime, true, 0, 8);
      }
      else if (ultimaTecla == 4)
      {
         animacion(5, deltaTime, true, 0, 8);
      }
      BrokenBlock = false;
   }
   if (!BloqueRoto)
   {
      int **matriz = Escenario::getInstance()->getMatriz();

      int time = BloqueCLock.getElapsedTime().asMilliseconds();
      std::cout << "TIEMPO BLOQUE" << time << std::endl;
      if (time > 0.5)
      {
         matriz[BloqueAromper.y][BloqueAromper.x] = 1;

         BloqueRoto = true;
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
bool Jugador::checkColisions()
{

   int **matriz = Escenario::getInstance()->getMatriz();
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
   int casillay = destino.y;
   int casillax = destino.x;

   std::vector<Enemigo *> enemigos = Escenario::getInstance()->getVectorEnemigos();

   for (int i = 0; i < enemigos.size(); i++)
   {
      if (abs(enemigos[i]->getColumna() * 32 - body->getPosition().x) <= 30 &&
          abs(enemigos[i]->getFila() * 32 - body->getPosition().y) <= 30)
      {
         if (Engolpe == false)
            setEngolpe(true);
      }
   }

   if (matriz[casillay][casillax] == 2 || matriz[casillay][casillax] == 0 || matriz[casillay][casillax] == 5)
   {
      return false;
   }
   /*else if(matriz[casillay][casillax] == 4 ) { // colisiona con el enemigo
       if(vida=0) {
          std::cout<<"HAS MUERTO" <<std::endl;
       }
       else {
          Engolpe=true;
          std::cout<<"Vidas: " <<vida<<std::endl;
          
          vida--;
       }

   }*/
   else
   {
      return true;
   }
}
void Jugador::avanzar(int dir, float deltaTime, sf::Vector2f velocity, int pos)
{
   // 1: derecha 2:izquierda 3:Down 4:Up

   int destino;
   Enpaso = true;
   float posJ = body->getPosition().x;
   int columna = 0;
   int fila = 0;
   if (dir == 1)
   {
      animacion(1, deltaTime, true, 0, 5);
      columna = 1;
      destino = abs(pos) + 32;
   }
   else if (dir == 2)
   {
      columna = -1;
      animacion(1, deltaTime, false, 0, 5);

      destino = abs(pos) - 32;
   }
   else if (dir == 3)
   {
      animacion(0, deltaTime, true, 0, 5);
      fila = +1;
      destino = abs(pos) + 32;
      posJ = body->getPosition().y;
   }
   else if (dir == 4)
   {
      animacion(2, deltaTime, true, 0, 5);
      fila = -1;
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
      updateMatriz(fila, columna);
      Enpaso = false;
      //std::cout << "Enpaso:" << Enpaso << std::endl;
   }
}
int Jugador::getPosx()
{
   return (body->getPosition().x / 32);
}
int Jugador::getPosy()
{
   return (body->getPosition().y / 32);
}
int Jugador::getUltimaTecla()
{
   return ultimaTecla;
}
void Jugador::updateMatriz(int fila, int columna)
{
   int **matriz = Escenario::getInstance()->getMatriz();

   matriz[(int)lastCasilla.y][(int)lastCasilla.x] = 1;
   matriz[(int)lastCasilla.y + fila][(int)lastCasilla.x + columna] = 6;
   lastCasilla.x += columna;
   lastCasilla.y += fila;

   /*for (int i = 0; i < 20; i++)
   {
        std::cout << "" << std::endl;
      for (int j = 0; j < 20; j++)
      {
          std::cout << matriz[i][j] << "  " << std::ends;
      }
   }*/
}
bool Jugador::engolpe()
{
   int time = engolpeClock.getElapsedTime().asSeconds();
   //   std::cout << "TIEMPECITO" <<time <<std::endl;

   if (Engolpe && time >= 2)
   {
      return true;
   }
   else
   {
      return false;
   }
   /*if (vida == 0)
   {
      if(!Muriendo){
      Muriendo = true;
      dieClock.restart();
      vida--;
      }
      std::cout << "MUERTE Y DESTRUCCION" << std::endl;
   }
   else
   {
      Engolpe=true;
   }*/
}
bool Jugador::checkColisionBlock()
{
   int **matriz = Escenario::getInstance()->getMatriz();
   Jugador *player = Jugador::getInstance();
   sf::Vector2f destino;
   int playerx = player->getPosx(); // columna en la que esta
   int playery = player->getPosy(); // fila en la que esta
   destino.x = playerx;
   destino.y = playery;
   sf::Vector2f siguiente;
   siguiente.x = playerx;
   siguiente.y = playery;
   sf::Vector2i comprobaciones;
   sf::Vector2i comprobaciones2;
   sf::Vector2i comprobaciones3;
   sf::Vector2i comprobaciones4;
   bool BloqueEjeY;
   bool BloqueEjeX;

   if (player->getUltimaTecla() == 1)
   {
      BloqueEjeX = true;
      destino.x = playerx + 1;
      siguiente.x = playerx + 2;
   }
   else if (player->getUltimaTecla() == 2)
   {
      BloqueEjeX = true;
      destino.x = playerx - 1;
      siguiente.x = playerx - 2;
   }
   else if (player->getUltimaTecla() == 3)
   {
      BloqueEjeY = true;

      destino.y = playery + 1;
      siguiente.y = playery + 2;
   }
   else if (player->getUltimaTecla() == 4)
   {
      BloqueEjeY = true;

      destino.y = playery - 1;
      siguiente.y = playery - 2;
   }
   if (BloqueEjeX)
   {
      comprobaciones.x = siguiente.x;
      comprobaciones.y = siguiente.y + 1;
      comprobaciones2.x = siguiente.x;
      comprobaciones2.y = siguiente.y - 1;
      comprobaciones3.x = siguiente.x;
      comprobaciones3.y = siguiente.y - 2;
      comprobaciones4.x = siguiente.x;
      comprobaciones4.y = siguiente.y + 2;
   }
   if (BloqueEjeY)
   {
      comprobaciones.x = siguiente.x - 1;
      comprobaciones.y = siguiente.y;
      comprobaciones2.x = siguiente.x + 1;
      comprobaciones2.y = siguiente.y;
      comprobaciones3.x = siguiente.x - 2;
      comprobaciones3.y = siguiente.y;
      comprobaciones4.x = siguiente.x + 2;
      comprobaciones4.y = siguiente.y;
   }
   int casillay = destino.y;
   int casillax = destino.x;
   int siguientex = siguiente.x;
   int siguientey = siguiente.y;
   BloqueCLock.restart();
   /* std::cout << "player.x" << playerx << std::endl;
   std::cout << "player.y" << playery << std::endl;
   std::cout << "destino.x" << casillax << std::endl;
   std::cout << "destino.y" << casillay << std::endl;
   std::cout << "matriz colision" << matriz[casillay][casillax] << std::endl;*/

   if (matriz[casillay][casillax] == 2) // hay bloque
   {
      // std::cout << "Fila que quiere:  " << casillay << "  Columna que quiere: " << casillax << std::endl;
      // std::cout << "Siguiente Fila : " << siguientey << "  Siguiente columna: " << siguientex << std::endl;

      if (matriz[casillay][casillax] == 4 || matriz[siguientey][siguientex] == 2 || matriz[siguientey][siguientex] == 5 || matriz[siguientey][siguientex] == 0)
      {

         matriz[casillay][casillax] = 7; // aqui le pongo un sprite de medio roto
         BloqueAromper.x = casillax;
         BloqueAromper.y = casillay;

         BrokenBlock = true;
         BloqueRoto = false;
         rompiendoBloque();
      }

      else if (matriz[siguientey][siguientex] == 1 || matriz[siguientey][siguientex] == 3)
      { // aqui lo muevo una vez y de ahi llamo a la funcion moveBlock que la llama el update
         MovingBlock = true;
         matriz[casillay][casillax] = 1;
         matriz[siguientey][siguientex] = 2;
         casillaViejaBlock.x = siguientex;
         casillaViejaBlock.y = siguientey;
      }
      std::vector<Enemigo *> enemigos = Escenario::getInstance()->getVectorEnemigos();

      /*std::cout << " Fila CasillaVieja :  " << casillaViejaBlock.y << "  Columna casillaVieja: " << casillaViejaBlock.x << std::endl;
   std::cout << "Siguiente Fila : " << siguientey << "  Siguiente columna: " << siguientex << std::endl;*/
      /*if (matriz[casillaViejaBlock.y][casillaViejaBlock.x] == 2) // si es un bloque azul
   {*/

      for (int i = 0; i < enemigos.size(); i++)
      {

         if (
             (enemigos[i]->getColumna() == siguientex && enemigos[i]->getFila() == siguientey) ||
             (enemigos[i]->getColumna() == casillax && enemigos[i]->getColumna() == casillay) ||
             matriz[casillaViejaBlock.y][casillaViejaBlock.x] == 4 ||
             matriz[siguientey][siguientex] == 4 || matriz[comprobaciones.y][comprobaciones.x] == 4 ||
             matriz[comprobaciones2.y][comprobaciones2.x] == 4) // enemigo
         {
            std::cout << "Entra a matar enemigo" << std::endl;

            Escenario::getInstance()->resetEnemigos(siguientey, siguientex);
            matriz[siguientey][siguientex] = 2;
            matriz[casillaViejaBlock.y][casillaViejaBlock.x] = 1;
         }
      }

      return true;
   }
   /*else if (matriz[casillay][casillax] == 5)
   {

      if (matriz[siguientey][siguientex] == 1 || matriz[siguientey][siguientex] == 3)
      { // aqui lo muevo una vez y de ahi llamo a la funcion moveBlock que la llama el update
         MovingBlock = true;
         matriz[casillay][casillax] = 1;
         matriz[siguientey][siguientex] = 5;
         casillaViejaBlock.x = siguientex;
         casillaViejaBlock.y = siguientey;
      }
      else if (matriz[siguientey][siguientex] == 4)
      { // aqui me encuentro a un enemigo
         // std::cout << "Entra a matar enemigo" << std::endl;
         Escenario::getInstance()->resetEnemigos(siguientey, siguientex);
         matriz[siguientey][siguientex] = 5;
         matriz[casillay][casillax] = 1;
      }

      return true;
   }*/

   else
   {
      return false;
   }
}
bool Jugador::muriendo()
{
   int time = dieClock.getElapsedTime().asSeconds();
   //std::cout << "tiempecito" << time << std::endl;
   if (Muriendo && time >= 3)
   {
      return true;
   }
   else
   {
      return false;
   }
}
void Jugador::setMuriendo(bool b)
{
   Muriendo = false;
}
void Jugador::resetInstance()
{
   delete instance;
   instance = NULL;
}
void Jugador::setEngolpe(bool b)
{
   engolpeClock.restart();
   Engolpe = b;
}
bool Jugador::getEngolpe()
{
   return Engolpe;
}
bool Jugador::getModoDios()
{
   return modoDios;
}
void Jugador::moveBlock()
{
   // std::cout << "Compruebo todo el puto rato" << contadorcito << std::endl;
   int **matriz = Escenario::getInstance()->getMatriz();
   int siguientex = casillaViejaBlock.x;
   int siguientey = casillaViejaBlock.y;
   sf::Vector2i comprobaciones;
   sf::Vector2i comprobaciones2;
   sf::Vector2i comprobaciones3;
   sf::Vector2i comprobaciones4;

   bool BloqueEjeY;
   bool BloqueEjeX;

   if (ultimaTecla == 1)
   {
      BloqueEjeX = true;
      siguientex += 1;
   }
   else if (ultimaTecla == 2)
   {
      BloqueEjeX = true;

      siguientex -= 1;
   }
   else if (ultimaTecla == 3)
   {
      BloqueEjeY = true;

      siguientey += 1;
   }
   else if (ultimaTecla == 4)
   {
      BloqueEjeY = true;

      siguientey -= 1;
   }

   if (BloqueEjeX)
   {
      comprobaciones.x = siguientex;
      comprobaciones.y = siguientey + 1;
      comprobaciones2.x = siguientex;
      comprobaciones2.y = siguientey - 1;
      comprobaciones3.x = siguientex;
      comprobaciones3.y = siguientey - 2;
      comprobaciones4.x = siguientex;
      comprobaciones4.y = siguientey + 2;
   }
   if (BloqueEjeY)
   {
      comprobaciones.x = siguientex - 1;
      comprobaciones.y = siguientey;
      comprobaciones2.x = siguientex + 1;
      comprobaciones2.y = siguientey;
      comprobaciones3.x = siguientex - 2;
      comprobaciones3.y = siguientey;
      comprobaciones4.x = siguientex + 2;
      comprobaciones4.y = siguientey;
   }
   std::vector<Enemigo *> enemigos = Escenario::getInstance()->getVectorEnemigos();

   /*std::cout << " Fila CasillaVieja :  " << casillaViejaBlock.y << "  Columna casillaVieja: " << casillaViejaBlock.x << std::endl;
   std::cout << "Siguiente Fila : " << siguientey << "  Siguiente columna: " << siguientex << std::endl;*/
   /*if (matriz[casillaViejaBlock.y][casillaViejaBlock.x] == 2) // si es un bloque azul
   {*/

   for (int i = 0; i < enemigos.size(); i++)
   {

      if (
          (enemigos[i]->getColumna() == siguientex && enemigos[i]->getFila() == siguientey) ||
          (enemigos[i]->getColumna() == casilla.x && enemigos[i]->getColumna() == casilla.y) ||
          matriz[casillaViejaBlock.y][casillaViejaBlock.x] == 4 ||
          matriz[siguientey][siguientex] == 4 || matriz[comprobaciones.y][comprobaciones.x] == 4 ||
          matriz[comprobaciones2.y][comprobaciones2.x] == 4) // enemigo
      {
         std::cout << "Entra a matar enemigo" << std::endl;

         Escenario::getInstance()->resetEnemigos(siguientey, siguientex);
         matriz[siguientey][siguientex] = 2;
         matriz[casillaViejaBlock.y][casillaViejaBlock.x] = 1;
      }
   }
   if (matriz[siguientey][siguientex] == 1 || matriz[siguientey][siguientex] == 3)
   {
      matriz[casillaViejaBlock.y][casillaViejaBlock.x] = 1;
      matriz[siguientey][siguientex] = 2;
      casillaViejaBlock.x = siguientex;
      casillaViejaBlock.y = siguientey;
   }
   else
   {
      MovingBlock = false;
   }
   //}
   /*if (matriz[casillaViejaBlock.y][casillaViejaBlock.x] == 5) // si es una gema
   {
      if (matriz[siguientey][siguientex] == 1 || matriz[siguientey][siguientex] == 3)
      {
         matriz[casillaViejaBlock.y][casillaViejaBlock.x] = 1;
         matriz[siguientey][siguientex] = 5;
         casillaViejaBlock.x = siguientex;
         casillaViejaBlock.y = siguientey;
      }
      else if (matriz[siguientey][siguientex] == 4)
      {
         //std::cout << "Entra a matar enemigo" << std::endl;
         Escenario::getInstance()->resetEnemigos(siguientey, siguientex);
         matriz[siguientey][siguientex] = 5;
         matriz[casillaViejaBlock.y][casillaViejaBlock.x] = 1;
      }
      else
      {
         MovingBlock = false;
      }
   }*/
   contadorcito++;
}

void Jugador::rompiendoBloque()
{
   BloqueCLock.restart();
}
void Jugador::modoEnDios()
{
   if (!modoDios)
      PressGCLock.restart();
}

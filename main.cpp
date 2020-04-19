#include <SFML/Graphics.hpp>
#include <iostream>
#include "time.h"
#include "include/config.h"
#include "ej_modulos/mimodulo.h"
#include "Escenario/Escenario.h"
#include "Jugador/Jugador.h"
#include "fabricaEnemigos/fabricaEnemigos.h"

#define UPDATE_TICK_TIME 1000 / 17

int main()
{
  srand(time(NULL));
  sf::Clock updateClock;

  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 640), "P0. Fundamentos de los Videojuegos. DCCIA");
  sf::Vector2i p;
  p.x = 700;
  p.y = 200;
  window.setPosition(p);

  //Le pongo el centroide donde corresponde
  // sprite.setOrigin(75 / 2, 75 / 2);
  //Cojo el sprite que me interesa por defecto del sheet
  //sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // Lo dispongo en el centro de la pantalla

  window.setFramerateLimit(60);
  int cont = 0;
  //Bucle del juego
  while (window.isOpen())
  {

    //Escenario::getInstance()->resetInstance();
    // Escenario::getInstance()->resetEnemigos();

    if (cont != 0)
    {
      Jugador::getInstance()->resetInstance();
      Escenario::getInstance()->setVida(); // esto lo hace siempre que el jugador muere
    }
    cont ++;

    while (!Jugador::getInstance()->engolpe())
    {
      float percentTick = std::min(1.f, (float)updateClock.getElapsedTime().asSeconds() * 1000 / 66.67f);
      //Bucle de obtención de eventos
      sf::Event event;
      window.clear();
      if (updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
      {
        float timeElapsed = updateClock.restart().asSeconds();
        Escenario::getInstance()->update(timeElapsed);
      }
      Escenario::getInstance()->draw(window, percentTick);
      //Jugador::getInstance()->draw(window, percentTick);

      window.display();
      while (window.pollEvent(event))
      {

        switch (event.type)
        {

        //Si se recibe el evento de cerrar la ventana la cierro
        case sf::Event::Closed:
          window.close();
          break;
        }
      }
    }
  }
  return 0;
}

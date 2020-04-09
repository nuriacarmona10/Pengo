#include <SFML/Graphics.hpp>
#include <iostream>
#include "Escenario/Escenario.h"
#include "ej_modulos/mimodulo.h"
#include "include/config.h"
#define UPDATE_TICK_TIME 1000/15

#define kVel 5

int main() {
  sf::RenderWindow window(sf::VideoMode(400, 560), "Pengo Game");
   window.setFramerateLimit(60);
  srand(time(NULL));
  Escenario::getInstance()->crearMatriz();
  Escenario::prueba();

  while (window.isOpen()) {
    

    window.clear();

    window.display();
  }

  return 0;
}
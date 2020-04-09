#ifndef ESCENARIO_H
#define ESCENARIO_H
#include <SFML/Graphics.hpp>

class Escenario {

public:
  void crearMatriz();
  static void prueba();
  static Escenario *getInstance();
  void draw(sf::RenderWindow &window, float percentTick);

private:
  int **matriz;
  Escenario();
  static Escenario *instance;
  
  sf::Sprite body;
};

#endif
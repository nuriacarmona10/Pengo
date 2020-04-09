#include "Escenario.h"

#define filas 35
#define columnas 25
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

Escenario *Escenario::instance = 0;
Escenario::Escenario() {
  sf::Texture tiles;
    if(!tiles.loadFromFile("resources/bloques.png"))
  body.setTexture(tiles);
  matriz = new int *[filas];
}

void Escenario::crearMatriz() {

  for (int i = 0; i < filas; i++) {
      std::cout << " JIJIJIJ"  << std::endl;
    matriz[i] = new int[columnas];
  }
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (i == 0 || i == filas - 1) {
        matriz[i][j] = 0;
      } else if (j == 0 && j == columnas - 1) {
        matriz[i][j] = 0;
      } else {
        int num = 1 + rand() % 2; // eso me saca 1 y 2 : 1 para vacio y 2 para bloques
        std::cout << " " << num << std::endl;
        if (num == 1) {
          matriz[i][j] = 1;
        } else {
          matriz[i][j] = 2;
        }
      }
    }
  }
  // aquí saldrán los Snow-Bee
  matriz[3][3] = 3;
  matriz[20][30] = 3;
  matriz[15][17] = 3;
  //Aquí saldrán las gemas
  matriz[4][32] = 4;
  matriz[8][15] = 4;
  matriz[15][2] = 4;
}
void Escenario::draw(sf::RenderWindow &window, float percentTick) {
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (matriz[i][j] == 0) {

        body.setTextureRect(sf::IntRect(3 * 16, 8 * 16, 16, 16));
        body.setPosition(i * 16, j * 16);
        window.draw(body);
      }
    }
  }
}

void Escenario::prueba() {
  std::cout << " HOLA" << std::endl;
}
Escenario *Escenario::getInstance() {
  if (!instance) {
    instance = new Escenario();
  }
  return instance;
}
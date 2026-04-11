#ifndef GAMEGLOBALE_H
#define GAMEGLOBALE_H
/*-------------------------------
  all global variable declaration
  -------------------------------
*/
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using namespace sf;

   const int WINDOW_WIDTH = 1600;
   const int WINDOW_HEIGHT = 900;
   int score = 0;

   struct Vec2{
    float x, y;
   };

  //  Level
   struct Platform{
    sf::FloatRect rect;
    bool solid;
   };

   const int MAX_PLATFORMS = 64;

   struct Level{
    Platform platforms[MAX_PLATFORMS];
    int platformCount;
    sf::Color bgColor;
    Vec2 spawnPoint;
   };

   
#endif
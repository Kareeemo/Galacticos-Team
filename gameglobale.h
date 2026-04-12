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

   // Player 

   const int MAX_PLAYERS = 2;
     struct Player{
      Vec2 position;
      Vec2 velocity;
      float width;
      float height;
      int health;
      int maxHealth;
      bool onGround;
      bool facingRight;
      bool isAlive;
      int score;
      bool inputLeft;
      bool inputRight;
      bool inputJump;
      bool inputAttack;
      bool isAttacking;
      float attackTimer;
      float attackCooldown;
      sf::FloatRect attackBox;
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
    Vec2 spawnPoints[MAX_PLAYERS];
   };

   struct GameState{
    Player players[MAX_PLAYERS];
    Level currentLevel;
    float deltaTime;
    bool paused;
    bool gameOver;
    
   };

    std::vector<Level> levels;
  


   
#endif
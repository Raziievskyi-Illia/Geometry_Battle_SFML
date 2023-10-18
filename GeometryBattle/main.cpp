#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <ctime>
#include <string>

int main()
{
    srand(time(NULL)); 
    Game g; 
     g.run();
  

}

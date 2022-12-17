#include <SFML/System.hpp>

#include "player.h"
#include "floor.h"

void handlePlatformSpawn(player player, std::vector<floor> *platforms, std::vector<floor> floors, int min_x, int range_x, 
                         int range_y, int min_y,sf::Clock platformclock, int *platdivider, int *xpos, int*ypos,
                         int xwin, int ywin){
  if(platforms->empty()){
    int signx = rand() % 2 + 1; // 1 is + 2 is -
    *xpos = player.getPlayerShape().getPosition().x + player.getPlayerShape().getSize().x/2 + (float)(rand() % range_x) + min_x;
    *ypos = floors[0].getFloorShape().getPosition().y - (float)(rand() % range_y) - min_y;

    if(signx == 2){
      *xpos = player.getPlayerShape().getPosition().x + player.getPlayerShape().getSize().x/2 - (float)(rand() % range_x) + min_x;
    }
    
    if(*xpos < xwin/16){
      *xpos = xwin/16;
    }

    if(*xpos + player.getPlayerShape().getSize().x*3 > xwin - xwin/16){
      *xpos = xwin - xwin/16 - player.getPlayerShape().getSize().x*3;
    }

    floor first(sf::Vector2f(player.getPlayerShape().getSize().x*3, xwin/32),
        sf::Vector2f(*xpos, *ypos));

    platforms->push_back(first);
  }

  if((int)platformclock.getElapsedTime().asSeconds()/ *platdivider >= 1){
    *platdivider+=2;
    int signx = rand() % 2 + 1; // 1 is + 2 is -
    *xpos = player.getPlayerShape().getPosition().x + player.getPlayerShape().getSize().x/2 + (float)(rand() % range_x) + min_x;
    *ypos = platforms->at(platforms->size()-1).getFloorShape().getPosition().y - (float)(rand() % range_y) - min_y;

    if(signx != 1 && platforms->at(platforms->size()-1).getFloorShape().getPosition().x == xwin/16){
      signx = 1;
    }

    if(signx != 2 && platforms->at(platforms->size()-1).getFloorShape().getPosition().x + platforms->at(platforms->size()-1).getFloorShape().getSize().x == xwin - xwin/16){
      signx = 2;
    }

    if(signx == 2){
      *xpos = player.getPlayerShape().getPosition().x + player.getPlayerShape().getSize().x/2 - (float)(rand() % range_x) - min_x;
    }

    if(*xpos < xwin/16){
      *xpos = xwin/16;
    }
    
    if(*xpos + player.getPlayerShape().getSize().x*3 > xwin - xwin/16){
      *xpos = xwin - xwin/16 - player.getPlayerShape().getSize().x*3;
    }

    floor newplat(sf::Vector2f(player.getPlayerShape().getSize().x*3, xwin/32),
        sf::Vector2f(*xpos, *ypos));

    platforms->push_back(newplat);
  }
}
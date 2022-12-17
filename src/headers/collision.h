#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "player.h"
#include "floor.h"

bool isColliding(player player, floor floor){
    if(player.getPlayerShape().getGlobalBounds().intersects(floor.getFloorShape().getGlobalBounds())){
        return true;
    }

    return false;
}

void handleCollisions(player *player, std::vector<floor> floors, bool *col_bottom){
    for(int i=0; i<floors.size(); i++){

      if(!floors[i].isCollidable()){
        continue;
      }

      sf::FloatRect playerBounds = player->getPlayerShape().getGlobalBounds();
      sf::FloatRect floorBounds = floors[i].getFloorShape().getGlobalBounds();

      player->updateNextPos();


      if(floorBounds.intersects(player->getNextPos())){
        sf::RectangleShape tmp = player->getPlayerShape();
        //(player going to the) bottom collision
        if(playerBounds.top < floorBounds.top
          && playerBounds.top + playerBounds.height < floorBounds.top + floorBounds.height
          && playerBounds.left < floorBounds.left + floorBounds.width
          && playerBounds.left + playerBounds.width > floorBounds.left){
            player->setYDirection(0);
            tmp.setPosition(playerBounds.left, floorBounds.top - playerBounds.height);
            player->setPlayerShape(tmp);
            *col_bottom = true;
          }
        //(player going to the) top collision
        if(playerBounds.top > floorBounds.top
          && playerBounds.top + playerBounds.height > floorBounds.top + floorBounds.height
          && playerBounds.left < floorBounds.left + floorBounds.width
          && playerBounds.left + playerBounds.width > floorBounds.left){
            player->setYDirection(0);
            tmp.setPosition(playerBounds.left, floorBounds.top + floorBounds.height);
            player->setPlayerShape(tmp);
          }
        //(player going to the) right collision
        if(playerBounds.left < floorBounds.left
          && playerBounds.left + playerBounds.width < floorBounds.left + floorBounds.width
          && playerBounds.top < floorBounds.top + floorBounds.height
          && playerBounds.top + playerBounds.height > floorBounds.top){
            player->setXDirection(0);
            tmp.setPosition(floorBounds.left - playerBounds.width, playerBounds.top);
            player->setPlayerShape(tmp);
          }
        //(player going to the) left collision
        if(playerBounds.left > floorBounds.left
          && playerBounds.left + playerBounds.width > floorBounds.left + floorBounds.width
          && playerBounds.top < floorBounds.top + floorBounds.height
          && playerBounds.top + playerBounds.height > floorBounds.top){
            player->setXDirection(0);
            tmp.setPosition(floorBounds.left + floorBounds.width, playerBounds.top);
            player->setPlayerShape(tmp);
          }
      }
    }
}

#pragma once
#include <SFML/System.hpp>

#include "player.h"
#include "floor.h"

void handleWallsMovement(player player, int xwin, int ywin, int *go_up, std::vector<floor> *floors){
if(player.getPlayerShape().getPosition().y - ywin/2 <= *go_up){
      *go_up = *go_up - (int)ywin/2;
      
      sf::RectangleShape tempr = floors->at(1).getFloorShape();
      sf::RectangleShape templ = floors->at(2).getFloorShape();

      tempr.setPosition(tempr.getPosition().x, tempr.getPosition().y -ywin/2);
      templ.setPosition(templ.getPosition().x, templ.getPosition().y -ywin/2);

      floors->at(1).setFloorShape(tempr);
      floors->at(2).setFloorShape(templ);
    }
}
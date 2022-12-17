#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class floor{

  private:
    sf::RectangleShape floorShape;
    bool collidable;

  public:
    floor(sf::Vector2f size, sf::Vector2f position);

    sf::RectangleShape getFloorShape();
    void setFloorShape(sf::RectangleShape floorShape);

    bool isCollidable();
    void setCollidable(bool collidable);

};

floor::floor(sf::Vector2f size, sf::Vector2f position){
  floorShape.setSize(size);
  floorShape.setPosition(position);

  setCollidable(true);
}

sf::RectangleShape floor::getFloorShape(){
  return floorShape;
}

void floor::setFloorShape(sf::RectangleShape floorShape){
  this->floorShape = floorShape;
}

bool floor::isCollidable(){
  return collidable;
}

void floor::setCollidable(bool collidable){
  this->collidable = collidable;
}

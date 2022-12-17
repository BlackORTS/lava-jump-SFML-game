#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class player{

    private:
        sf::RectangleShape playerShape;
        sf::FloatRect nextPos;
        sf::Vector2f direction;
        sf::Vector2f direction_past;
        float speed;

    public:
        player(sf::Vector2f size, sf::Vector2f startPos);

        void movePlayer(float DELTA);

        void setNextPos(sf::FloatRect nextPos);
        sf::FloatRect getNextPos();
        void updateNextPos();

        sf::RectangleShape getPlayerShape();
        void setPlayerShape(sf::RectangleShape playerShape);

        sf::Vector2f getDirection();
        void setDirection(sf::Vector2f direction);
        float getXDirection();
        void setXDirection(float x);
        float getYDirection();
        void setYDirection(float y);

        void setSpeed(float speed);
        float getSpeed();

};

player::player(sf::Vector2f size, sf::Vector2f startPos){
    playerShape.setSize(size);
    playerShape.setPosition(startPos);
    playerShape.setFillColor(sf::Color::Red);

    direction = sf::Vector2f(0.f, 0.f);

    setSpeed(1.f);
}

void player::movePlayer(float DELTA){
    playerShape.setPosition(playerShape.getPosition()+direction * DELTA * speed);
}

void player::setNextPos(sf::FloatRect nextPos){
    this->nextPos = nextPos;
}

sf::FloatRect player::getNextPos(){
    return nextPos;
}

void player::updateNextPos(){
    nextPos = playerShape.getGlobalBounds();
    nextPos.left += direction.x;
    nextPos.top += direction.y;
}

sf::RectangleShape player::getPlayerShape(){
    return playerShape;
}

void player::setPlayerShape(sf::RectangleShape playerShape){
    this->playerShape = playerShape;
}

sf::Vector2f player::getDirection(){
    return direction;
}

void player::setDirection(sf::Vector2f direction){
    this->direction = direction;
}

float player::getXDirection(){
    return direction.x;
}

void player::setXDirection(float x){
    direction.x = x;
}

float player::getYDirection(){
    return direction.y;
}

void player::setYDirection(float y){
    direction.y = y;
}

float player::getSpeed(){
    return speed;
}

void player::setSpeed(float speed){
    this->speed = speed;
}

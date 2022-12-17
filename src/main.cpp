#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <time.h>

#include "headers/player.h"
#include "headers/floor.h"

#include "headers/walls_m.h"
#include "headers/platforms_s.h"

#include "headers/collision.h"

const float xwin = 1280;
const float ywin = 720;

int main(){
  sf::RenderWindow window(sf::VideoMode(xwin, ywin), "shitty game with aabb collisions", sf::Style::Default);

  srand(time(NULL));

  //Independent FrameRate
  sf::Clock clock;
  float dt;
  float multiplier = 60.f;
  float DELTA;

  //view
  sf::View view;
  view.setSize(xwin, ywin);

  //player
  player p1(sf::Vector2f(xwin/24, xwin/24), sf::Vector2f(xwin/2-xwin/24/2, ywin/2-xwin/24/2));

  //floor
  std::vector<floor> floors;

  floor mfloor(sf::Vector2f(xwin, ywin), sf::Vector2f(0.f, ywin - ywin / 16));
  floor rwall(sf::Vector2f(xwin , ywin*10), sf::Vector2f(xwin - xwin/16, -ywin/6));
  floor lwall(sf::Vector2f(xwin , ywin*10), sf::Vector2f(-xwin + xwin/16, -ywin/6));

  floor lava(sf::Vector2f(xwin * 4, ywin*2), sf::Vector2f(-xwin*2, ywin+ywin/16*2));
  lava.setCollidable(false);
  sf::RectangleShape tmp = lava.getFloorShape();
  tmp.setFillColor(sf::Color::Yellow); 
  lava.setFloorShape(tmp);

  floors.push_back(mfloor);
  floors.push_back(rwall);
  floors.push_back(lwall);

  floors.push_back(lava);

  int go_up = ywin;

  //collision
  int curr_collisions = 0;
  bool col_bottom = false;

  //TEXTS
  sf::Font m_font;

  if(!m_font.loadFromFile("Fonts/ARCADECLASSIC.TTF")){
    printf("error!");
    window.close();
    return 0;
  }

  sf::Text text_x;
  std::string x_str = "player  x   ";
  text_x.setFont(m_font); text_x.setFillColor(sf::Color::Green);
  text_x.setCharacterSize(24);
  text_x.setString(x_str);
  text_x.setPosition(0, 20);

  sf::Text text_y;
  std::string y_str = "player  y   ";
  text_y = text_x;
  text_y.setString(y_str);
  text_y.setPosition(0, 40);

  sf::Text text_lava_y;
  std::string txtlavay_str = "lava  y   ";
  text_lava_y.setFont(m_font);
  text_lava_y.setCharacterSize(24);
  text_lava_y.setFillColor(sf::Color::Blue);
  text_lava_y.setString(txtlavay_str);
  
  //lock
  bool lock = false;

  //lavatime
  sf::Clock lavaclock;
  sf::Time lavatime;
  int divider = 5;
  float lava_speed = 30;
  const int lava_max_speed = ywin / 4.5; 

  //platforms
  std::vector<floor> platforms;
  sf::Clock platformclock;
  int platdivider = 2;
  int min_y = p1.getPlayerShape().getSize().y * 2;
  int max_y = p1.getPlayerShape().getSize().y * 4;
  int range_y = max_y -  min_y + 1;
  int xpos;

  int min_x = p1.getPlayerShape().getSize().x * 3;
  int max_x = p1.getPlayerShape().getSize().x * 7;
  int range_x = max_x - min_x + 1;
  int ypos;

 
  while (window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
        window.close();
      }
    }

    dt = clock.restart().asSeconds();
    DELTA = dt * multiplier;

    //MOVEMENT

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      p1.setXDirection(p1.getXDirection()-xwin/128);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      p1.setXDirection(p1.getXDirection()+xwin/128);
    }

    //GRAVITY
    for(int i=0; i<floors.size(); i++){
      if(isColliding(p1, floors[i])){
        curr_collisions++;
      }
    }

    if(curr_collisions == 0){
      p1.setYDirection(p1.getYDirection() + ywin/2000 * DELTA);
    }

    handlePlatformSpawn(p1, &platforms, floors, min_x, range_x, range_y, min_y, 
                        platformclock, &platdivider, &xpos, &ypos, xwin, ywin);

    //COLLISIONS
    handleCollisions(&p1, floors, &col_bottom); 
    handleCollisions(&p1, platforms, &col_bottom);
    
    if(p1.getPlayerShape().getGlobalBounds().intersects(floors[3].getFloorShape().getGlobalBounds())){
      window.close();
    }

    //JUMPING
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && p1.getYDirection() == 0){
      if(col_bottom == true){
        p1.setYDirection(-p1.getPlayerShape().getSize().x/4);
      }
    }

    //TEXT STUFF
    text_x.setString(x_str + std::to_string((int)p1.getPlayerShape().getPosition().x));
    text_y.setString(y_str + std::to_string((int)p1.getPlayerShape().getPosition().y));
    text_lava_y.setString(txtlavay_str + std::to_string((int)floors[3].getFloorShape().getPosition().y));

    //LAVA
    lavatime = lavaclock.getElapsedTime();

    if(lava_speed != lava_max_speed && (int)lavatime.asSeconds()/divider >= 1){
      lava_speed = lava_speed * 1.5;
    }

    if((int)lava_speed > lava_max_speed){
      lava_speed = lava_max_speed;
    }

    if((int)lavatime.asSeconds()/divider >= 1){
      sf::RectangleShape tmpp = floors[3].getFloorShape();
      tmpp.move(0, -lava_speed);
      floors[3].setFloorShape(tmpp);
      divider = divider + 2;
    }

    

    //Update
    p1.movePlayer(DELTA);

    p1.setXDirection(0.f);
    curr_collisions = 0;
    col_bottom = false;

    view.setCenter(sf::Vector2f(p1.getPlayerShape().getPosition().x + p1.getPlayerShape().getSize().x/2
                    , p1.getPlayerShape().getPosition().y + p1.getPlayerShape().getSize().y/2 - ywin/6));

    handleWallsMovement(p1, xwin, ywin, &go_up, &floors);

    //Draw
    window.clear();

    window.setView(view);
    
    for(int i=0; i<floors.size(); i++){
      window.draw(floors[i].getFloorShape());
    }
    for(int i=0; i<platforms.size(); i++){
      window.draw(platforms[i].getFloorShape());
    }
     
    window.draw(p1.getPlayerShape());

    window.setView(window.getDefaultView());
    window.draw(text_x);
    window.draw(text_y);
    window.draw(text_lava_y);

    window.display();

  }

  return 0;
}

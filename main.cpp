#include "Header.h"

#pragma warning(disable : 4996)

using namespace sf;

int main()
{
  srand(time(NULL));
  RenderWindow window(VideoMode(530, 800), "Life");
  
  auto image = sf::Image{};
  image.loadFromFile("icon.jpg");
  window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());


  Color background_color = Color(138, 155, 110);
  Color button_color = Color(243, 243, 251);
  
  Font font;
  font.loadFromFile("VA-11Hall-A6pxBold.ttf");
  Font font2;
  font2.loadFromFile("times.ttf");

  Creaturs* grid[10][10];
  int display_grid[10][10];
  int step_counter = 0;
 
  Texture t;
  t.loadFromFile("2.jpg");
  Sprite s(t);
  
  //Filling in the field with empty cells
  int entity_counter = 0;
  int enitty_limitt = 15;

  CreatursSpawn(grid, display_grid);
  
  RectangleShape background = SetBackgroundParameters(0, 0, 530, 800, background_color);
  
  RectangleShape button_umen = SetButtonParameters(15, 10, 50, 50, button_color);
  RectangleShape button_paus = SetButtonParameters(75, 10, 185, 50, button_color);
  RectangleShape button_uvel = SetButtonParameters(270, 10, 50, 50, button_color);
  RectangleShape button_step = SetButtonParameters(415, 10, 100, 50, button_color);
  RectangleShape button_reset = SetBackgroundParameters(15, 70, 305, 50, button_color);
  RectangleShape timer_background = SetButtonParameters(415, 70, 100, 50, button_color);

  Text t_umen = SetTextParameters("<<", 20, 20, 25, font2, Text::Bold, Color::Black);
  Text t_paus = SetTextParameters("Start / Pause", 86, 20, 20, font, Text::Bold, Color::Black);
  Text t_uvel = SetTextParameters(">>", 283, 20, 25, font2, Text::Bold, Color::Black);
  Text t_reset = SetTextParameters("Reset", 133, 80, 25, font, Text::Bold, Color::Black);
  Text t_step = SetTextParameters("Step", 435, 20, 25, font, Text::Bold, Color::Black);


  Clock clock;
  int time = 0;
  bool play = false;
  int delay = 1001;
  int delay_stap = 200;

  //Main window cycle
  while (window.isOpen()){
    
    
    
    Event event;

    //Step counter
    
    
    std::string step_counter_str = std::to_string(step_counter);
    Text step_counter_text = SetTextParameters(step_counter_str, 435, 80, 25, font, Text::Bold, Color::Black);

    //Mouse position
    Vector2i pos = Mouse::getPosition(window);
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }

      //Mouse Click
      if (event.type == Event::MouseButtonPressed) {
        //Left Click
        if (event.key.code == Mouse::Left) {
          if (CheakClikOnButton(pos, button_step) && !play) {
            step_counter++;
            system("CLS");
            Step(grid);
            UpdateDisplayGrid(grid, display_grid);
          }

          if (CheakClikOnButton(pos, button_paus)) {
            play = !play;
          }

          if (CheakClikOnButton(pos, button_umen)) {
            if (delay <= 2000) {
              delay += delay_stap;
            }
          }

          if (CheakClikOnButton(pos, button_uvel)) {
            if (delay >= 0) {
              delay -= delay_stap;
            }
          }

          if (CheakClikOnButton(pos, button_reset)) {
            step_counter = 0;
            play = false;
            CreatursSpawn(grid, display_grid);
            
          }
        }
  
        //Right Click
        else if (event.key.code == Mouse::Right){
       
        }
      }     
    }

    if (play && clock.getElapsedTime().asMilliseconds() >= delay) {
      step_counter++;
      Step(grid);
      UpdateDisplayGrid(grid, display_grid);

      time++;
      clock.restart();
    }



    window.clear(Color(195, 195, 195, 255));
 
    window.draw(background);
    window.draw(button_umen);
    window.draw(button_paus);
    window.draw(button_uvel);
    window.draw(button_step);
    window.draw(button_reset);
    window.draw(timer_background);

    window.draw(t_umen);
    window.draw(t_paus);
    window.draw(t_uvel);
    window.draw(t_step);
    window.draw(t_reset);
    window.draw(step_counter_text);

    
    //Drawing cells
    float scale = 1.6;
    int w = 32;

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        s.setTextureRect(IntRect(display_grid[i][j] * w, 0, w, w));
        s.setPosition(i * w * scale + 10, j * w * scale + 280);
        s.setScale(scale, scale);
        window.draw(s);
      }
    }
  
    //FieldRendering(window, s, display_grid, grid);

    window.display();
    //system("CLS");
  }
  
  return 0;
}
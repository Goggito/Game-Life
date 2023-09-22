#pragma once
#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include "Class.h"


sf::RectangleShape SetBackgroundParameters(int x_pos, int y_pos, float width, float height, sf::Color color) {
  sf::RectangleShape background;
  background.setSize(sf::Vector2f(width, height));
  background.setPosition(sf::Vector2f(x_pos, y_pos));
  background.setFillColor(color);

  return background;
}

sf::RectangleShape SetButtonParameters(int x_pos, int y_pos, float width, float height, sf::Color color) {
  sf::RectangleShape button;
  button.setSize(sf::Vector2f(width, height));
  button.setPosition(sf::Vector2f(x_pos, y_pos));
  button.setFillColor(color);

  return button;
}

sf::Text SetTextParameters(sf::String content, int x_pos, int y_pos, int size, sf::Font& font, sf::Text::Style style, sf::Color color) {
  sf::Text text;
  text.setString(content);
  text.setPosition(x_pos, y_pos);
  text.setCharacterSize(size);
  text.setFont(font);
  text.setStyle(style);
  text.setColor(color);
  
  return text;
}

bool CheakClikOnButton(sf::Vector2i pos, sf::RectangleShape& button) {
  if ((pos.x > button.getPosition().x && pos.x < button.getSize().x + button.getPosition().x)
    && (pos.y > button.getPosition().y && pos.y < button.getSize().y + button.getPosition().y)) {
    return true;
  }
  return false;
}



void CreatursSpawn(Creaturs* grid[10][10], int display_grid[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      display_grid[i][j] = 0;
      grid[i][j] = new Void();
    }
  }

  int random;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      random = rand() % 25;
      if (random <=4) {
        //Bush
        Plant* plant = new Plant(i, j);
        grid[i][j] = plant;
        display_grid[i][j] = plant -> GetImageIndex();
      }
      
      if (random >= 5 && random <= 7) {
        //Rabit
        Herbivore* herb = new Herbivore(i, j);
        grid[i][j] = herb;
        display_grid[i][j] = herb->GetImageIndex();
      }
      
      if (random >= 8 && random <= 9) {
        //Wolf
        Predatory* pred = new Predatory(i, j);
        grid[i][j] = pred;
        display_grid[i][j] = pred->GetImageIndex();
      }
    }
  }

}

void ReplPlants(Creaturs* grid[10][10]) {

  for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (grid[i][j]->GetImageIndex() == 0) {
          int x = rand() % 4;
          if (x == 0) {
            grid[i][j] = new Plant(i, j);
          }
        }       
      }
    }

}

void CheckWolfPopul(Creaturs* grid[10][10]) {
  int wolf_min = 5;
  int wolf_counter = 0;
  int scale = -1;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      scale = grid[i][j]->GetImageIndex();
      if (scale == 1 || scale == 2) {
        wolf_counter++;
      }
    }
  }

  int x = wolf_min - wolf_counter;

  if (x > 0) {
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < 10; j++) {
        scale = grid[0][j]->GetImageIndex();
        if ((scale == 0 || (3 <= scale && scale <= 6)) && x > 0) {
          grid[0][j] = new Predatory(0, j);
          x--;
        }
      }

    }
  }

}

void UpdateDisplayGrid(Creaturs* grid[10][10], int display_grid[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      display_grid[i][j] = grid[i][j]->GetImageIndex();
    }
  }
}

void Step(Creaturs* grid[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (grid[i][j]->GetImageIndex() != 0) { 

        if (grid[i][j]->GetMoving()) {
          grid[i][j]->Move(grid);
        }
      }
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      grid[i][j]->SetMoving(true);
    }
  }
  CheckWolfPopul(grid);
  ReplPlants(grid);
}

void CheackTable(Creaturs* grid[10][10], int display_grid[10][10]) {
  std::cout << std::endl << std::endl << "Grid Display" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << std::endl;
    for (int j = 0; j < 10; j++) {
      std::cout << grid[j][i]->GetImageIndex() << " ";

    }
  }

  std::cout << std::endl << std::endl << "Grid" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << std::endl;
    for (int j = 0; j < 10; j++) {
      std::cout << display_grid[j][i] << " ";

    }
  }
}
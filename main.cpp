#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "blocks.hpp"

int main()
{
  srand(time(NULL));
  Square field[10][22];
  for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 22; j++)
	{
	  field[i][j].setColor(0, 0, 0);
	  field[i][j].setOff();
	}
    }

  sf::RenderWindow window(sf::VideoMode(10 * TETRIS_BOX_SIZE, 20 * TETRIS_BOX_SIZE), "Tetris");
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(30);
  
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      window.clear(sf::Color::Black);
      drawField(field, window);
      window.display();
    }

  return 0;
}

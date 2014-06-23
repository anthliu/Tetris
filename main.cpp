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
  window.setFramerateLimit(10);

  Block theBlock(randomBlock());
  theBlock.initBlock(field);
  int curFrame = 0;
  
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
	  theBlock.update(field, LEFT);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
	  theBlock.update(field, RIGHT);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
	  theBlock.turn(field);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
	  curFrame = 0;
	  if (!theBlock.update(field, DOWN))
	    {
	      theBlock.reset(randomBlock());
	      theBlock.initBlock(field);
	    }
        }

      if (curFrame == GAME_SPEED)
	{
	  curFrame = 0;
	  if (!theBlock.update(field, DOWN))
	    {
	      theBlock.reset(randomBlock());
	      theBlock.initBlock(field);
	    }
	} else
	{
	  curFrame++;
	}

      window.clear(sf::Color::Black);
      drawField(field, window);
      window.display();
    }

  return 0;
}

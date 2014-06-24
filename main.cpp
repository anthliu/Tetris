#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "blocks.hpp"

void frameCheck(int& score, Block& theBlock, Square field[10][22], sf::RenderWindow& window);

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
  int score = 0;
  
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
	  frameCheck(score, theBlock, field, window);
        }

      if (curFrame == GAME_SPEED)
	{
	  curFrame = 0;
	  frameCheck(score,theBlock, field, window);
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

void frameCheck(int& score, Block& theBlock, Square field[10][22], sf::RenderWindow& window)
{
  if (!theBlock.update(field, DOWN))
    {
      score += updateField(field);
      if (checkGameOver(field))
	{
	  window.close();
	  printf("Game Over!\n");
	  printf("Score: %d\n", score * 100);
	  exit(0);
	}
      theBlock.reset(randomBlock());
      theBlock.initBlock(field);
    }
}

#include <SFML/Graphics.hpp>
#include "blocks.hpp"

void Square::setColor(int r, int g, int b)
{
  color.r = r;
  color.g = g;
  color.b = b;
}

void Square::setOn()
{
  on = true;
}

void Square::setOff()
{
  on = false;
}

bool Square::getState()
{
  return on;
}

sf::Color Square::getColor()
{
  return color;
}

Block::Block(BlockType type)
{
  reset(type);
}

void Block::reset(BlockType type)
{
  if (type == I_BLOCK)
    {
      coordinates[0][0] = 2;
      coordinates[0][1] = 1;

      coordinates[1][0] = 3;
      coordinates[1][1] = 1;
      
      coordinates[2][0] = 4;
      coordinates[2][1] = 1;

      coordinates[3][0] = 5;
      coordinates[3][1] = 1;
    }
}

void Block::initBlock(Square field[10][22])
{
  for (int i = 0; i < 4; i++)
    {
      field[coordinates[i][0]][coordinates[i][1]].setOn();
    }
}

void drawField(Square field[10][22], sf::RenderWindow& window)
{
  sf::RectangleShape rectangle(sf::Vector2f(TETRIS_BOX_SIZE, TETRIS_BOX_SIZE));
  int xPos = 0;
  int yPos = -2 * TETRIS_BOX_SIZE;//the areas that are not shown to the player

  for (int j = 0; j < 22; j++)
    {
      xPos = 0;
      for (int i = 0; i < 10; i++)
	{
	  if (field[i][j].getState())
	    {
	      rectangle.move(xPos, yPos);
	      window.draw(rectangle);
	    }
	  xPos += TETRIS_BOX_SIZE;
	}
      yPos += TETRIS_BOX_SIZE;
    }
}

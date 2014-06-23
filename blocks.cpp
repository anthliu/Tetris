#include <stdio.h>
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

BlockType randomBlock()
{
  return static_cast<BlockType>(rand() % 7);
}

Block::Block(BlockType type)
{
  reset(type);
}

void Block::reset(BlockType type)
{
  bType = type;
  if (type == I_BLOCK)
    {
      coordinates[0][0] = 3;
      coordinates[0][1] = 1;

      coordinates[1][0] = 4;
      coordinates[1][1] = 1;
      
      coordinates[2][0] = 5;
      coordinates[2][1] = 1;

      coordinates[3][0] = 6;
      coordinates[3][1] = 1;
    } else if (type == J_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 0;

      coordinates[1][0] = 5;
      coordinates[1][1] = 0;
      
      coordinates[2][0] = 6;
      coordinates[2][1] = 0;

      coordinates[3][0] = 6;
      coordinates[3][1] = 1;
    } else if (type == L_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 1;

      coordinates[1][0] = 5;
      coordinates[1][1] = 1;
      
      coordinates[2][0] = 6;
      coordinates[2][1] = 1;

      coordinates[3][0] = 6;
      coordinates[3][1] = 0;
    } else if (type == O_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 0;

      coordinates[1][0] = 5;
      coordinates[1][1] = 0;
      
      coordinates[2][0] = 4;
      coordinates[2][1] = 1;

      coordinates[3][0] = 5;
      coordinates[3][1] = 1;
    } else if (type == S_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 1;

      coordinates[1][0] = 5;
      coordinates[1][1] = 1;
      
      coordinates[2][0] = 5;
      coordinates[2][1] = 0;

      coordinates[3][0] = 6;
      coordinates[3][1] = 0;
    } else if (type == T_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 0;

      coordinates[1][0] = 5;
      coordinates[1][1] = 0;
      
      coordinates[2][0] = 6;
      coordinates[2][1] = 0;

      coordinates[3][0] = 5;
      coordinates[3][1] = 1;
    } else
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 0;

      coordinates[1][0] = 5;
      coordinates[1][1] = 0;
      
      coordinates[2][0] = 5;
      coordinates[2][1] = 1;

      coordinates[3][0] = 6;
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

bool Block::testField(int coordinatePair[2], Direction dir)
{
  int updateX, updateY;
  if (dir == DOWN)
    {
      updateX = 0;
      updateY = 1;
    } else if (dir == RIGHT)
    {
      updateX = 1;
      updateY = 0;
    } else if (dir == LEFT)
    {
      updateX = -1;
      updateY = 0;
    } else
    {
      updateX = 0;
      updateY = -1;
    }

  if (coordinatePair[0] + updateX >= 10 or coordinatePair[0] + updateX < 0 or coordinatePair[1] + updateY >= 22 or coordinatePair[1] + updateY < 0)
    {
      return false;
    }
  return true;
}

bool Block::update(Square field[10][22], Direction dir)
{
  /*Returns false if the block is on the floor/on another block/block cannot move in that direction*/
  int updateX, updateY;
  if (dir == DOWN)
    {
      updateX = 0;
      updateY = 1;
    } else if (dir == RIGHT)
    {
      updateX = 1;
      updateY = 0;
    } else if (dir == LEFT)
    {
      updateX = -1;
      updateY = 0;
    } else
    {
      updateX = 0;
      updateY = -1;
    }

  for (int i = 0; i < 4; i++)
    {
      field[coordinates[i][0]][coordinates[i][1]].setOff();
    }

  bool doUpdate = true;//true = update it, false = don't
  for (int j = 0; j < 4; j++)
    {
      if (field[coordinates[j][0] + updateX][coordinates[j][1] + updateY].getState() or !testField(coordinates[j], dir))
	{
	  doUpdate = false;
	}
    }
  if (doUpdate == true)
    {
      for (int k = 0; k < 4; k++)
	{
	  coordinates[k][0] += updateX;
	  coordinates[k][1] += updateY;
	}
    }

  initBlock(field);

  return doUpdate;
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
	      rectangle.setPosition(xPos, yPos);
	      window.draw(rectangle);
	    }
	  xPos += TETRIS_BOX_SIZE;
	}
      yPos += TETRIS_BOX_SIZE;
    }
}

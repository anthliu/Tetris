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
  /*coordinate 4 will designate the center square (except for the O_BLOCK), the one rotated around*/
  bType = type;
  if (type == I_BLOCK)
    {
      coordinates[0][0] = 3;
      coordinates[0][1] = 1;

      coordinates[1][0] = 6;
      coordinates[1][1] = 1;
      
      coordinates[2][0] = 5;
      coordinates[2][1] = 1;

      coordinates[3][0] = 4;
      coordinates[3][1] = 1;
    } else if (type == J_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 0;

      coordinates[1][0] = 6;
      coordinates[1][1] = 1;
      
      coordinates[2][0] = 6;
      coordinates[2][1] = 0;

      coordinates[3][0] = 5;
      coordinates[3][1] = 0;
    } else if (type == L_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 1;

      coordinates[1][0] = 6;
      coordinates[1][1] = 0;
      
      coordinates[2][0] = 6;
      coordinates[2][1] = 1;

      coordinates[3][0] = 5;
      coordinates[3][1] = 1;
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

      coordinates[1][0] = 6;
      coordinates[1][1] = 0;
      
      coordinates[2][0] = 5;
      coordinates[2][1] = 0;

      coordinates[3][0] = 5;
      coordinates[3][1] = 1;
    } else if (type == T_BLOCK)
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 0;

      coordinates[1][0] = 5;
      coordinates[1][1] = 1;
      
      coordinates[2][0] = 6;
      coordinates[2][1] = 0;

      coordinates[3][0] = 5;
      coordinates[3][1] = 0;
    } else//Z_BLOCK
    {
      coordinates[0][0] = 4;
      coordinates[0][1] = 1;

      coordinates[1][0] = 6;
      coordinates[1][1] = 0;
      
      coordinates[2][0] = 5;
      coordinates[2][1] = 1;

      coordinates[3][0] = 5;
      coordinates[3][1] = 0;
    }
}

void Block::initBlock(Square field[10][22])
{
  for (int i = 0; i < 4; i++)
    {
      field[coordinates[i][0]][coordinates[i][1]].setOn();
    }
}

bool Block::testField(int coordinatePair[2])
{
  if (coordinatePair[0] >= 10 or coordinatePair[0] < 0 or coordinatePair[1] >= 22 or coordinatePair[1] < 0)
    {
      return false;
    }
  return true;
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

bool Block::turn(Square field[10][22])
{
  int tempCoord[4][2];
  tempCoord[3][0] = coordinates[3][0];
  tempCoord[3][1] = coordinates[3][1];
  for (int i; i < 3; i++)
    {
      //rotate(x, y) = (y, -x)
      tempCoord[i][0] = coordinates[3][0] + (coordinates[i][1] - coordinates[3][1]);
      tempCoord[i][1] = coordinates[3][1] - (coordinates[i][0] - coordinates[3][0]);
    }

  for (int i = 0; i < 4; i++)
    {
      field[coordinates[i][0]][coordinates[i][1]].setOff();
    }

  bool doUpdate = true;//true = update it, false = don't
  for (int j = 0; j < 4; j++)
    {
      if (field[tempCoord[j][0]][tempCoord[j][1]].getState() or !testField(tempCoord[j]))
	{
	  doUpdate = false;
	}
    }
  if (doUpdate == true)
    {
      for (int k = 0; k < 4; k++)
	{
	  coordinates[k][0] = tempCoord[k][0];
	  coordinates[k][1] = tempCoord[k][1];
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

int updateField(Square field[10][22])
{
  /*check and update for completed rows and return score*/
  int score = 0;
  bool check;
  int xPos;
  for(int i = 21; i >= 2; i--)
    {
      xPos = 0;
      check = true;
      while(check == true)
	{
	  if (xPos == 10)
	    {
	      score++;
	      for (int j = i; j >= 2; j--)
		{
		  for (int k = 0; k < 10; k++)
		    {
		      if (field[k][j - 1].getState())
			{
			  field[k][j - 1].setOff();
			  field[k][j].setOn();
			}
		      else
			field[k][j].setOff();
		    }
		}
	      i++;
	    }
	  if (!field[xPos][i].getState())
	    {
	      check = false;
	    }
	  xPos++;
	}
    }

  return score * score;
}

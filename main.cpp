#include <iostream>
#include <SFML/Graphics.hpp>

#define TETRIS_BOX_SIZE 30

class Square
{
  sf::Color color;
  bool on;
public:
  void setColor(int r, int g, int b)
  {
    color.r = r;
    color.g = g;
    color.b = b;
  }
  void setOn()
  {
    on = true;
  }
  void setOff()
  {
    on = false;
  }
  bool getState()
  {
    return on;
  }
};

void drawField(Square field[10][22], sf::RenderWindow& window)
{
  sf::RectangleShape rectangle(sf::Vector2f(TETRIS_BOX_SIZE, TETRIS_BOX_SIZE));
  int xPos = 0;
  int yPos = 0;

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


int main()
{

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

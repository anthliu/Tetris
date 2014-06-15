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
};

int main()
{

  Square field[22][10];
  for (int i = 0; i < 22; i++)
    {
      for (int j = 0; j < 10; j++)
	{
	  field[i][j].setColor(0, 0, 0);
	  field[i][j].setOff();
	}
    }

  sf::RenderWindow window(sf::VideoMode(10 * TETRIS_BOX_SIZE, 20 * TETRIS_BOX_SIZE), "Tetris");
  
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      window.clear(sf::Color::Black);
      window.display();
    }

  return 0;
}

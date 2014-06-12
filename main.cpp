#include <iostream>
#include <SFML/Graphics.hpp>

#define TETRIS_BOX_SIZE 30

int main()
{
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

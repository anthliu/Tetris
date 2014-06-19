#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <SFML/Graphics.hpp>
#define TETRIS_BOX_SIZE 30

class Square
{
  sf::Color color;
  bool on;
public:
  void setColor(int r, int g, int b);
  void setOn();
  void setOff();
  bool getState();
  sf::Color getColor();
};

enum BlockType {I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK};

class Block
{
  int coordinates[4][2];
  sf::Color color;
  BlockType bType;
public:
  Block(BlockType type);
  void reset(BlockType type);
  void initBlock(Square field[10][22]);

};

void drawField(Square field[10][22], sf::RenderWindow& window);

#endif

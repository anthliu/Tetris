#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <SFML/Graphics.hpp>
#define TETRIS_BOX_SIZE 30
#define GAME_SPEED 15

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
enum Direction {UP, RIGHT, DOWN, LEFT};

BlockType randomBlock();

class Block
{
  int coordinates[4][2];
  sf::Color color;
  BlockType bType;

  bool testField(int coordinatePair[2], Square field[10][22]);
public:
  Block(BlockType type);
  void reset(BlockType type);
  void initBlock(Square field[10][22]);
  bool update(Square field[10][22], Direction dir);

};

void drawField(Square field[10][22], sf::RenderWindow& window);

#endif

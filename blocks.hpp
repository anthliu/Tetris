#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <SFML/Graphics.hpp>
#define TETRIS_BOX_SIZE 30
#define GAME_SPEED 5

int randHue();

class Square
{
  sf::Color color;
  bool on;
public:
  void setColor(sf::Color newColor);
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

  bool testField(int coordinatePair[2]);
  bool testField(int coordinatePair[2], Direction dir);
public:
  Block(BlockType type, sf::Color);
  void reset(BlockType type, sf::Color);
  void initBlock(Square field[10][22]);
  bool update(Square field[10][22], Direction dir);
  bool turn(Square field[10][22]);
};

void drawField(Square field[10][22], sf::RenderWindow& window);
int updateField(Square field[10][22]);//check and update for completed rows and return score
bool checkGameOver(Square field[10][22]);

#endif

#ifndef PADDLE_HPP
#define PADDLE_HPP
#include "../object.hpp"
class Paddle : public Object{
public:
  enum{
    PLAYER1,
    PLAYER2,
    PC
  }mode;
  using Object::Object;
  void update();
};
#endif

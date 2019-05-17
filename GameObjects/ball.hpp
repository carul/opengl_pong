#ifndef BALL_HPP
#define BALL_HPP
#include "../object.hpp"
#include <math.h>

class Ball : public Object{
public:
  float angle = M_PI;
  float speedmodif = 0.8;
  using Object::Object;
  void update();
  void animateColor();
  void reset();
};

#endif

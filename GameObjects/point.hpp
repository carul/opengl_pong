#ifndef POINT_HPP
#define POINT_HPP
#include "../object.hpp"

class Point : public Object{
public:
  using Object::Object;
  int player = 0;
  void setPlayer(int player);
  void setColor(float r, float g, float b, float a);
  void update();
  ~Point() = default;
};

#endif

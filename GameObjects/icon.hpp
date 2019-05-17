#ifndef ICON_HPP
#define ICON_HPP
#include "../object.hpp"

class Icon : public Object{
public:
  bool activated = false;
  using Object::Object;
  void setColor(float r, float g, float b, float a);
};

#endif

#include "icon.hpp"


void Icon::setColor(float r, float g, float b, float a){
  for(auto &&vtx:this->vertices){
    vtx.color[0]=r;
    vtx.color[1]=g;
    vtx.color[2]=b;
    vtx.color[3]=a;
  }
}

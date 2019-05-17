#include "point.hpp"

void Point::setPlayer(int player){
  this->player = player;
  if(player == 1){
    this->setColor(0.9f, 0.8f, 0.1f, 0.4f);
  }
  if(player == 2){
    this->setColor(0.9f, 0.0f, 0.1f, 0.4f);
  }
}

void Point::setColor(float r, float g, float b, float a){
  for(auto &&vtx:this->vertices){
    vtx.color[0]=r;
    vtx.color[1]=g;
    vtx.color[2]=b;
    vtx.color[3]=a;
  }
}


void Point::update(){

}

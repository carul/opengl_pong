#include "ball.hpp"
#include "point.hpp"
#include <cmath>
#include <random>
#include <iostream>

void Ball::animateColor(){
  unsigned int vtx = (rand() % this->vertices.size());
  Vertex * vert = this->getVertex(vtx);
  unsigned short col = (rand()%3);
  vert->color[col] += ((rand()%2)*2-1)*0.05f;
  if(vert->color[col] >= 1.0f)
    vert->color[col] = 1.0f;
  else if(vert->color[col] <= 0.0f)
    vert->color[col] = 1.0f;
}

void Ball::update(){
  this->speedmodif += DELTATIME*0.02;
  this->move(speedmodif*DELTATIME*cos(angle), speedmodif*DELTATIME*sin(angle));
  animateColor();
  float boundingLeft, boundingRight, boundingTop, boundingBottom;
  boundingLeft = this->vertices.at(0).position[0];
  boundingRight = this->vertices.at(3).position[0];
  boundingBottom = this->vertices.at(1).position[1];
  boundingTop = this->vertices.at(4).position[1];
  if(boundingLeft < -0.96f){
    this->setPosition(0.0f, 0.0f);
    this->speedmodif = 0.8f;
    this->angle = 0;
    Point * point = new Point(GL_STATIC_DRAW);
    point->create(POINT_DATA);
    point->indice(POINT_INDICES);
    point->setPlayer(2);
    point->name = "POINT";
    point->setPosition(0.93f - 0.03f*scorep2, 0.9f);
    scorep2++;
    GAMEOBJECTS.push_back(point);
  }
  if(boundingRight > 0.96f){
    this->setPosition(0.0f, 0.0f);
    this->speedmodif = 0.8f;
    this->angle = M_PI;
    Point * point = new Point(GL_STATIC_DRAW);
    point->create(POINT_DATA);
    point->indice(POINT_INDICES);
    point->setPlayer(1);
    point->name = "POINT";
    point->setPosition(-0.95f + 0.03f*scorep1, 0.9f);
    scorep1++;
    GAMEOBJECTS.push_back(point);
  }
  Object * paddle1 = Object::find("PADDLE1");
  Object * paddle2 = Object::find("PADDLE2");

  if(boundingLeft < -0.2f && paddle1 != NULL){ //interaction with left paddle
    Vertex * leftTop = paddle1->getVertex(0);
    Vertex * rightBottom = paddle1->getVertex(2);
    if(boundingLeft <= rightBottom->position[0] && boundingLeft > leftTop->position[0]
    && boundingBottom <= leftTop->position[1] && boundingTop >= rightBottom->position[1]){
      this->angle = 0;
      float spany = leftTop->position[1]-rightBottom->position[1]+BALL_WIDTH*2;
      float dy = (leftTop->position[1]+rightBottom->position[1])/2-(boundingTop+boundingBottom)/2;
      this->angle -= asin(1.9*dy/spany);
    }
  }

  if(boundingRight > 0.2f && paddle2 != NULL){//interaction with right paddle
    Vertex * leftTop=paddle2->getVertex(3);
    Vertex * rightBottom=paddle2->getVertex(1);
    if(boundingRight >= leftTop->position[0] && boundingRight < rightBottom->position[0]
    && boundingBottom <= leftTop->position[1] && boundingTop >= rightBottom->position[1]){
      this->angle = M_PI;
      float spany = leftTop->position[1]-rightBottom->position[1]+BALL_WIDTH*2;
      float dy = (leftTop->position[1]+rightBottom->position[1])/2-(boundingTop+boundingBottom)/2;
      this->angle += asin(1.9*dy/spany);
    }
  }

  if(boundingTop >= BORDER_WIDTH){
    this->angle = -this->angle;
    float dy = boundingTop - BORDER_WIDTH;
    this->move(0, -dy);
  }

  if(boundingBottom <= -BORDER_WIDTH){
    this->angle = -this->angle;
    float dy = boundingBottom+BORDER_WIDTH;
    this->move(0, -dy);
  }
}

void Ball::reset(){
  this->setPosition(0.0f, 0.0f);
  this->angle = M_PI*(rand()%2);
}

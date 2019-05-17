#include "paddle.hpp"
#include "ball.hpp"
#include "../defines.hpp"

void Paddle::update(){
  if(this->mode == PLAYER1){
    if(W_PRESSED && this->getVertex(0)->position[1]<0.955){
      this->move(0, DELTATIME);
      if(this->getVertex(0)->position[1] > 0.955)
        this->move(0, -this->getVertex(0)->position[1]+0.955);
    }
    if(S_PRESSED && this->getVertex(1)->position[1]>-0.955){
      this->move(0, -DELTATIME);
      if(this->getVertex(1)->position[1] < -0.955)
        this->move(0, -0.955-this->getVertex(1)->position[1]);
    }
  }
  if(this->mode == PLAYER2){
    if(UP_PRESSED && this->getVertex(0)->position[1]<0.955){
      this->move(0, DELTATIME);
      if(this->getVertex(0)->position[1] > 0.955)
        this->move(0, -this->getVertex(0)->position[1]+0.955);
    }
    if(DOWN_PRESSED && this->getVertex(1)->position[1] > -0.955){
      this->move(0, -DELTATIME);
      if(this->getVertex(1)->position[1] < -0.955)
        this->move(0, -0.955-this->getVertex(1)->position[1]);
    }
  }
  if(this->mode == PC){
    Ball * ball = (Ball *)Object::find("BALL");
    float cn_y = (this->getVertex(0)->position[1] + this->getVertex(1)->position[1])/2;
    float bally = ball->getVertex(0)->position[1];
    float rmodif = 0.0f;
    int trg = 0;
    if(ball->getVertex(0)->position[0] > 0.7f){
      float cn_size = fabs(this->getVertex(0)->position[1]-this->getVertex(1)->position[1]);
      float p_mov =  fabs(cn_size/2 - fabs(cn_y-bally))/(cn_size/2);
      if(p_mov != 0)
        rmodif = (float)(rand()%(int)floor(p_mov*1000))/1000;
      rmodif *= (rand()%2)*2-1;
      if(p_mov > 0.1)
        trg = (rand()%2)*2-1;
    }

    if((bally > cn_y && this->getVertex(0)->position[1] < 0.955) || trg == 1){
      this->move(0, DELTATIME*(1+rmodif));
      if(this->getVertex(0)->position[1] > 0.955)
        this->move(0, -this->getVertex(0)->position[1]+0.955);
    }
    else if((bally < cn_y && this->getVertex(1)->position[1] > -0.955)|| trg ==-1){
      this->move(0, -DELTATIME*(1+rmodif));
      if(this->getVertex(1)->position[1] < -0.955)
        this->move(0, -0.955-this->getVertex(1)->position[1]);
    }
  }
}

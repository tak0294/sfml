//
//  RaceScene.cpp
//  sfml
//
//  Created by 三田村卓哉 on 2016/06/16.
//  Copyright © 2016年 三田村卓哉. All rights reserved.
//

#include <algorithm>
#include <stdio.h>
#include <math.h>
#include "library/InputSystem.h"
#include "library/Video.h"
#include "RaceScene.h"
#include "mover/PlayerCar.h"

void RaceScene::setup() {
    Scene::setup();
    
    for(int ii=0;ii<roadLength;ii++) {
        this->coursePositionVector.push_back(ii*1000);
        Mover *mv = new Mover();
        mv->setTexture("img/road3.jpg");
        this->courseSprites.push_back(mv);
    }
    
    endPoint.x = 0;
    endPoint.y = 2500;
    
    /////////
    // BG
    /////////
    Video::tiledBgFromFile(Video::BG_1, "city.png", Video::BG_TILED_VERTICAL, 0);

    /////////
    // Player Car.
    /////////
    playerCar = new PlayerCar();
    playerCar->pos.x = 300;
    playerCar->pos.y = 240;
    playerCar->scale.x = 2;
    playerCar->scale.y = 2;
    
    playerCar->setTexture("img/ferrari_straight1.png");
}

void RaceScene::drawCourse2() {
    sf::Vector2<double> startPoint;
    sf::Vector2<double> processPoint;
    
    startPoint.x = 0;
    startPoint.y = 600;
    
    
    processPoint.x = 0;
    processPoint.y = endPoint.y * 0.62;
    
    for(int ii=roadLength-1;ii>=0;ii--) {
    
        double t = this->coursePositionVector[ii] * 0.00001;
        
        double p_x = Video::calcBezierX(t, startPoint.x, endPoint.x, processPoint.x);
        double p_y = Video::calcBezierY(t, startPoint.y, endPoint.y, processPoint.y);
        
        p_x += carPositionX;
//        p_y += 500;
        
        //////////////////////////////////////////////////////
        // 道路.
        //////////////////////////////////////////////////////
        double focus = 10;
        sf::Vector2<double> perspectivePoint =
            Video::calcPerspectivePoint(focus, p_x, p_y, this->coursePositionVector[ii] * 0.001);
        perspectivePoint.y *= 0.4;
        
        ///////////////////////////////////////////////////////
        // 道路右側.
        ///////////////////////////////////////////////////////
        sf::Vector2<double> perspectivePointRightSide =
        Video::calcPerspectivePoint(focus, p_x + 600, p_y - 500, this->coursePositionVector[ii] * 0.001);
        perspectivePointRightSide.y *= 0.4;
        
        ///////////////////////////////////////////////////////
        // 道路左側.
        ///////////////////////////////////////////////////////
        sf::Vector2<double> perspectivePointLeftSide =
        Video::calcPerspectivePoint(focus, p_x - 2650, p_y - 500, this->coursePositionVector[ii] * 0.001);
        perspectivePointLeftSide.y *= 0.4;
        
        double scale = Video::calcScaleFromZ(focus, this->coursePositionVector[ii] * 0.001);
        
        this->courseSprites[ii]->pos.x = perspectivePoint.x + 320;
        this->courseSprites[ii]->pos.y = perspectivePoint.y + 100;
        this->courseSprites[ii]->scale.x = scale * 2.5;
        this->courseSprites[ii]->scale.y = scale * 0.3;
        
        
        this->courseSprites[ii]->draw();
        Video::drawRect(perspectivePointRightSide.x + 320 , perspectivePointRightSide.y + 100, 2000 * scale, 300*scale, sf::Color::White, sf::Color::Blue);
        Video::drawRect(perspectivePointLeftSide.x + 320 , perspectivePointLeftSide.y + 100, 2000 * scale, 300*scale, sf::Color::White, sf::Color::Blue);
        
        this->coursePositionVector[ii] -= speed;
        if(this->coursePositionVector[ii] < 0) {
            this->coursePositionVector[ii] = getLargestCoursePosition() + 1000;
        }
    }
    
    // Zソート.
    std::sort(this->coursePositionVector.begin(), this->coursePositionVector.end());
}

int RaceScene::getLargestCoursePosition() {
    int tmpPosition = 0;
    for(int ii=0;ii<roadLength;ii++) {
        if(coursePositionVector[ii] > tmpPosition) {
            tmpPosition = coursePositionVector[ii];
        }
    }
    return tmpPosition;
}



void RaceScene::draw(sf::RenderWindow &window) {
    this->drawCourse2();
    Video::drawRect(0, 300, 640, 180, sf::Color::Black);;
    
    this->playerCar->draw();
}

void RaceScene::update() {
    if(InputSystem::isRight) {
        r += 0.1;
//        endPoint.x += 100;
        carPositionX -= 5;
    }
    if(InputSystem::isLeft) {
        r -= 0.1;
//        endPoint.x -= 100;
        carPositionX += 5;
    }
    
    if(InputSystem::isUp) {
        p += 0.001;
        speed += 100;
        if(speed > 1000) {
            speed = 1000;
        }
    }
    if(InputSystem::isDown) {
        p -= 0.001;
    }
    
    if(InputSystem::isA) {
        endPoint.y -= 50;
    }
    if(InputSystem::isB) {
        endPoint.y += 50;
    }
    
    speed *= 0.98;
}




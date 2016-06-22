//
//  RaceScene.h
//  sfml
//
//  Created by 三田村卓哉 on 2016/06/16.
//  Copyright © 2016年 三田村卓哉. All rights reserved.
//

#ifndef RaceScene_h
#define RaceScene_h

#include "library/Scene.h"
#include "library/Mover.h"
#include "mover/PlayerCar.h"

class RaceScene : public Scene {

private:
    double r = 0;
    double p = 0.95;
    int roadLength = 300;
    std::vector<Mover*> courseSprites;
    std::vector<int> coursePositionVector;
    sf::Vector2<double> endPoint;
    int speed = 0;
    
    void drawCourse1();
    void drawCourse2();
    int getLargestCoursePosition();
    
    double carPositionX = 0;
    PlayerCar *playerCar;
    
public:
    void setup();
    void draw(sf::RenderWindow &window);
    void update();
};

#endif /* RaceScene_h */

//
//  TestScene.hpp
//  sfml
//
//  Created by 三田村卓哉 on 2016/06/15.
//  Copyright © 2016年 三田村卓哉. All rights reserved.
//

#ifndef TestScene_hpp
#define TestScene_hpp

#include <stdio.h>
#include "library/GameManager.h"
#include "library/Scene.h"
#include "library/Mover.h"
#include "library/ParticleSystem.h"

#include "mover/TestPumpkin.hpp"

/***************************************************************************************
 * TestScene Class.
 ***************************************************************************************/
class TestScene : public Scene {
    TestPumpkin *mover2;
    ParticleSystem *psys;
    
public:
    void setup();
    void draw(sf::RenderWindow &window);
    void update();
};


#endif /* TestScene_hpp */

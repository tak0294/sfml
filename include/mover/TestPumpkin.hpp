//
//  TestPumpkin.hpp
//  sfml
//
//  Created by 三田村卓哉 on 2016/06/15.
//  Copyright © 2016年 三田村卓哉. All rights reserved.
//

#ifndef TestPumpkin_hpp
#define TestPumpkin_hpp

#include <stdio.h>
#include "library/Mover.h"

/***************************************************************************************
 * TestPumpkin Class.
 ***************************************************************************************/
class TestPumpkin : public Mover {
    
public:
    void update();
    sf::Vector2f dst_scale;
};

#endif /* TestPumpkin_hpp */

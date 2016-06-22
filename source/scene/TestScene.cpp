//
//  TestScene.cpp
//  sfml
//
//  Created by 三田村卓哉 on 2016/06/15.
//  Copyright © 2016年 三田村卓哉. All rights reserved.
//

#include "ResourcePath.hpp"
#include "library/Scene.h"
#include "TestScene.hpp"

#include "mover/TestPumpkin.hpp"

void TestScene::setup() {
    Scene::setup();
    //	Video::addSpritePixelShader(Video::SP_1, Video::PS_PIXELIZE);
    //	Video::addSpritePixelShader(Video::SP_1, Video::PS_RASTER);
    
    ///////////////////////////////////////////////////////
    //	BG Layers.
    ///////////////////////////////////////////////////////
    //	Video::tiledBgFromFile(Video::BG_2, resourcePath() + "pumpkin064.png");
    Video::tiledBgFromFile(Video::BG_2, resourcePath() + "fire.jpg", Video::BG_TILED_HORIZONTAL, 500);
    // Video::tiledBgFromFile(Video::BG_2, "flame.png", Video::BG_TILED_HORIZONTAL, 800);
    //	Video::addBgPixelShader(Video::BG_2, Video::PS_PIXELIZE);
    Video::addBgPixelShader(Video::BG_2, Video::PS_RASTER);
    //	Video::setBgScrollDirection(Video::BG_2, Video::DIRECTION_LEFT_DOWN);
    //	Video::setBgScrollSpeed(Video::BG_2, 2);
    
    Video::tiledBgFromFile(Video::BG_1, resourcePath() + "city.png", Video::BG_TILED_HORIZONTAL, 500);
    
    mover2 = new TestPumpkin();
    mover2->setTexture(resourcePath() + "pumpkin064.png");
    mover2->pos.y = 250;
    mover2->scale.x = mover2->scale.y = 1.5f;
    
    ///////////////////////////////////////////////////////
    //	ParticleSystem setup.
    ///////////////////////////////////////////////////////
    psys = new ParticleSystem();
    psys->addColor(sf::Color::Red);
    psys->addColor(sf::Color::Yellow);
    psys->addColor(sf::Color::Blue);
}

void TestScene::draw(sf::RenderWindow &window) {
    psys->draw();
    Video::drawRect(mover2->pos.x, mover2->pos.y, 100, 100, sf::Color::Red, sf::Color::Black);
    Video::drawRect(10, 10, 50, 100);
    
    this->mover2->draw();
    Video::drawText(L"こんにちは!!", Video::FONT_NORMAL, 10, 100, 24 * mover2->pos.x * 0.01);
}

void TestScene::update() {
    if(InputSystem::isRight) {
        mover2->pos.x += 4.0f;
        psys->add(mover2->pos.x, mover2->pos.y);
    }
    
    if(InputSystem::isLeft) {
        mover2->pos.x -= 4.0f;
        psys->add(mover2->pos.x, mover2->pos.y);
    }
    if(InputSystem::isDown) {
        mover2->pos.y += 4.0f;
        psys->add(mover2->pos.x, mover2->pos.y);
    }
    
    if(InputSystem::isUp) {
        mover2->pos.y -= 4.0f;
        psys->add(mover2->pos.x, mover2->pos.y);
    }
    
    if(InputSystem::isA) {
        mover2->scale.x = mover2->scale.y = 7;
        Video::clearBg(Video::BG_1);
    }
    psys->update();
    mover2->update();
    frame++;
}



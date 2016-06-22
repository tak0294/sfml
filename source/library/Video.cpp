#include "library/Video.h"
#include "library/Shader/ShaderInclude.h"
#include <stdio.h>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"


/**
 * Declare real symbols.
 */
int Video::m_width;
int Video::m_height;
sf::Vector2u Video::m_bgSizes[BG_LAYER_NUM];
sf::Vector2i Video::m_bgPositions[BG_LAYER_NUM];
Video::ScrollDirection Video::m_scrollDirections[BG_LAYER_NUM];
sf::RenderTexture Video::m_bgLayers[BG_LAYER_NUM];
sf::RenderTexture Video::m_spriteLayers[SPRITE_LAYER_NUM];
Shader* Video::m_bgShader[BG_LAYER_NUM];
Shader* Video::m_spriteShader[SPRITE_LAYER_NUM];
sf::Clock Video::videoClock;

sf::RenderWindow Video::window;
int Video::m_bgScrollSpeeds[BG_LAYER_NUM];
std::unordered_map<std::string, sf::Texture*> Video::m_textureStore;

///////////////////////////////////////////////////////////////////
//	Layer Sprites
///////////////////////////////////////////////////////////////////
sf::Sprite Video::m_spSprites[SPRITE_LAYER_NUM];
sf::Sprite Video::m_bgSprites[BG_LAYER_NUM];

///////////////////////////////////////////////////////////////////
//	Shape ref
///////////////////////////////////////////////////////////////////
sf::RectangleShape Video::m_rectShape;

///////////////////////////////////////////////////////////////////
// FontTypes.
///////////////////////////////////////////////////////////////////
sf::Font Video::m_fonts[FONT_TYPE_NUM];

///////////////////////////////////////////////////////////////////
// ShaderScripts.
///////////////////////////////////////////////////////////////////
std::string Video::m_vertexShaderScripts[VERTEX_SHADER_NUM];
ShaderScript* Video::m_pixelShaderScripts[PIXEL_SHADER_NUM];

void Video::setupPixelShaderScripts() {
	m_pixelShaderScripts[Video::PS_RASTER]      = new PS_Wave();
	m_pixelShaderScripts[Video::PS_PIXELIZE] 	= new PS_Pixel();
}

void Video::setupFonts() {
	m_fonts[FONT_NORMAL].loadFromFile(resourcePath() + "yutapon.ttf");
}

/**
 *	SDL初期化.
 */
void Video::initialize(int w, int h) {
	m_width = w;
	m_height = h;
    //window.create(sf::VideoMode(w, h), "SFML works!!!", sf::Style::Fullscreen);
    window.create(sf::VideoMode(w, h), "SFML works!!!");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    for(int ii=0;ii<BG_LAYER_NUM;ii++) {
    	m_scrollDirections[ii] = DIRECTION_NONE;
    	m_bgScrollSpeeds[ii]   = 0;
    	m_bgShader[ii] = new Shader();
    }

    for(int ii=0;ii<SPRITE_LAYER_NUM;ii++) {
    	m_spriteShader[ii] = new Shader();
    	m_spriteLayers[ii].create(w, h);
    	m_spriteLayers[ii].display();
	}

    //Shader scripts setup
    Video::setupPixelShaderScripts();

    //Font setup.
    Video::setupFonts();
}

/**
 * フルスクリーン切り替え.
 */
void Video::toggleFullScreen() {
	//SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}


/////////////////////////////////////////////////////////////////////////////////
// テクスチャ読み込み＆キャッシュ.
/////////////////////////////////////////////////////////////////////////////////
sf::Texture* Video::loadTexture(std::string filePath) {
    if(Video::m_textureStore[filePath] == NULL) {
        sf::Texture *tex = new sf::Texture;
        tex->loadFromFile(resourcePath() + filePath);
        Video::m_textureStore[filePath] = tex;
    }
    
    return Video::m_textureStore[filePath];
}

/////////////////////////////////////////////////////////////////////////////////
// ベジェ曲線の計算.
/////////////////////////////////////////////////////////////////////////////////
/**
 * X座標を求める.
 * @param double t -> 0.0~1.0の間
 * @param double startX -> 始点
 * @param double endX   -> 終点
 * @param double processX -> 作用点
 */
double Video::calcBezierX(double t, double startX, double endX, double processX) {
    return (1-t)*(1-t)*startX + 2*(1-t)*t*processX + t*t*endX;
}

/**
 * Y座標を求める.
 * @param double t -> 0.0~1.0の間
 * @param double startY -> 始点
 * @param double endY   -> 終点
 * @param double processY -> 作用点
 */
double Video::calcBezierY(double t, double startY, double endY, double processY) {
    return (1-t)*(1-t)*startY + 2*(1-t)*t*processY + t*t*endY;
}


/**
 * 透視投影座標へ変換する.
 */
sf::Vector2<double> Video::calcPerspectivePoint(double focus, double x, double y, double z) {
    sf::Vector2<double> res;
    res.x = (focus / (z + focus)) * x;
    res.y = (focus / (z + focus)) * y;
    return res;
}

/**
 * Z座標からスケールを計算する.
 */
double Video::calcScaleFromZ(double focus, double z) {
    return focus/(focus + z);
}


/**
 * 背景スクロール方向設定.
 */
void Video::setBgScrollDirection(BgLayer layer, ScrollDirection direction) {
	m_scrollDirections[layer] = direction;
}

/**
 * 背景スクロール速度設定.
 */
void Video::setBgScrollSpeed(BgLayer layer, int speed) {
	m_bgScrollSpeeds[layer] = speed;
}


/**
 * 背景
 */
void Video::bgFromFile(BgLayer layer, std::string image_filename) {
	Video::bgFromFile(layer, image_filename, 0, 0);
}


/**
 * 背景
 */
void Video::bgFromFile(BgLayer layer, std::string image_filename, int x, int y) {
    sf::Texture *backgroundTexture = Video::loadTexture(image_filename);
	m_bgSizes[layer] = backgroundTexture->getSize();
	m_bgLayers[layer].create(m_bgSizes[layer].x, m_bgSizes[layer].y);

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(*backgroundTexture);
	m_bgLayers[layer].draw(backgroundSprite);
	m_bgPositions[layer].x = x;
	m_bgPositions[layer].y = y;
	m_bgLayers[layer].display();
}

/**
 * 背景.
 */
void Video::tiledBgFromFile(BgLayer layer, std::string image_filename) {
	Video::tiledBgFromFile(layer, image_filename, BG_TILED_BOTH, 0);
}



/**
 * 背景.
 */
void Video::tiledBgFromFile(BgLayer layer, std::string image_filename, BgTiledType tiledType, int offset) {
    sf::Texture *backgroundTexture = Video::loadTexture(image_filename);
	sf::Sprite backgroundSprite;
	m_bgSizes[layer] = backgroundTexture->getSize();
	
	int w = m_width + m_bgSizes[layer].x*2;
	int h = m_height + m_bgSizes[layer].y*2;
	
	m_bgLayers[layer].create(w, h);
	backgroundSprite.setTexture(*backgroundTexture);

	////////////////////////////////////////////
	// BgTiledTypeによって敷き詰め方を変える.
	////////////////////////////////////////////
	if(tiledType == BG_TILED_BOTH) {
		for(int ii=0;ii<h;ii+=m_bgSizes[layer].y) {
			for(int jj=0;jj<w;jj+=m_bgSizes[layer].x) {
				backgroundSprite.setPosition(jj, ii);
				m_bgLayers[layer].draw(backgroundSprite);
			}
		}
	}else if(tiledType == BG_TILED_HORIZONTAL) {
		for(int jj=0;jj<w;jj+=m_bgSizes[layer].x) {
			backgroundSprite.setPosition(jj, offset);
			m_bgLayers[layer].draw(backgroundSprite);
		}
	}else if(tiledType == BG_TILED_VERTICAL) {
		for(int ii=0;ii<h;ii+=m_bgSizes[layer].y) {
			backgroundSprite.setPosition(offset, ii);
			m_bgLayers[layer].draw(backgroundSprite);
		}
	}
	m_bgPositions[layer].x = -m_bgSizes[layer].x;
	m_bgPositions[layer].y = -m_bgSizes[layer].y;
	m_bgLayers[layer].display();
}

/**
 * 背景スクロール.
 */
void Video::scrollBg() {

	for(int layer=0;layer<BG_LAYER_NUM;layer++) {
		for(int ii=0;ii<m_bgScrollSpeeds[layer];ii++) {
			if(m_scrollDirections[layer] == DIRECTION_VERTICAL) {
				m_bgPositions[layer].y += 1;
			}else if(m_scrollDirections[layer] == DIRECTION_HORIZONTAL) {
				m_bgPositions[layer].x += 1;
			}else if(m_scrollDirections[layer] == DIRECTION_LEFT_DOWN) {
				m_bgPositions[layer].x -= 1;
				m_bgPositions[layer].y += 1;
			}else if(m_scrollDirections[layer] == DIRECTION_RIGHT_DOWN) {
				m_bgPositions[layer].x += 1;
				m_bgPositions[layer].y += 1;
			}
		    
		    if(m_scrollDirections[layer] == DIRECTION_VERTICAL ||
		       m_scrollDirections[layer] == DIRECTION_LEFT_DOWN ||
		       m_scrollDirections[layer] == DIRECTION_RIGHT_DOWN) {
			    if(m_bgPositions[layer].y == 0) {
					m_bgPositions[layer].x = -m_bgSizes[layer].x;
					m_bgPositions[layer].y = -m_bgSizes[layer].y;
			    }
		    }else{
		    	if(m_bgPositions[layer].x == 0) {
					m_bgPositions[layer].x = -m_bgSizes[layer].x;
			    }
		    }
		}

	}
}

/**
 * 背景描画.
 */
void Video::drawBg(sf::RenderWindow &window) {
	for(int layer=0;layer<BG_LAYER_NUM;layer++) {
		m_bgSprites[layer].setTexture(m_bgLayers[layer].getTexture());
		m_bgSprites[layer].setPosition((float)m_bgPositions[layer].x, (float)m_bgPositions[layer].y);
		//shader
		m_bgShader[layer]->buildShader();
	    window.draw(m_bgSprites[layer], &m_bgShader[layer]->m_shader);
	}
}

/**
 * 背景消去.
 */
void Video::clearBg(BgLayer layer) {
	m_bgLayers[layer].clear();
}

void Video::clearSpriteAll() {
	for(int layer=0;layer<SPRITE_LAYER_NUM;layer++) {
		m_spriteLayers[layer].clear(sf::Color::Transparent);
	}
}

/**
 * 背景用Shader設定.
 */
void Video::addBgPixelShader(BgLayer layer, PixelShader shaderType) {
	m_bgShader[layer]->addShaderScript(m_pixelShaderScripts[shaderType]);
}

/**
 * スプライト用Shader設定.
 */
void Video::addSpritePixelShader(SpriteLayer layer, PixelShader shaderType) {
	m_spriteShader[layer]->addShaderScript(m_pixelShaderScripts[shaderType]);
}


/**
 * スプライト描画.
 */
void Video::drawSprite(SpriteLayer layer, sf::Drawable &sprite) {
	m_spriteLayers[layer].draw(sprite);
}

void Video::flipSpriteToWindow(sf::RenderWindow &window) {
	for(int layer=0;layer<SPRITE_LAYER_NUM;layer++) {
		m_spSprites[layer].setTexture(m_spriteLayers[layer].getTexture());
		m_spriteShader[layer]->buildShader();
		window.draw(m_spSprites[layer], &m_spriteShader[layer]->m_shader);
	}
}

/**
 * テキスト描画.
 */
void Video::drawText(wchar_t *str, Video::FontType fontType, int x, int y) {
	Video::drawText(str, fontType, x, y, DEFAULT_FONT_SIZE);
}

void Video::drawText(wchar_t *str, Video::FontType fontType, int x, int y, int size) {
	sf::Text text(str, m_fonts[fontType], size);
	text.setPosition(x, y);
	// window.draw(text);
	// m_bgLayers[BG_2].draw(text);
	m_spriteLayers[SP_1].draw(text);
}




///////////////////////////////////////////////////////////////////
//	図形描画.
///////////////////////////////////////////////////////////////////
void Video::drawRect(float x, float y, float width, float height) {
    Video::drawRect(x, y, width, height, sf::Color::White);
}
void Video::drawRect(float x, float y, float width, float height, sf::Color fillColor) {
    Video::drawRect(x, y, width, height, fillColor, sf::Color::White);
}
void Video::drawRect(float x, float y, float width, float height, sf::Color fillColor, sf::Color borderColor) {
    m_rectShape.setSize(sf::Vector2f(width, height));
    m_rectShape.setPosition(x, y);
    m_rectShape.setFillColor(fillColor);
    m_rectShape.setOutlineColor(borderColor);
    m_rectShape.setOutlineThickness(1);
    m_spriteLayers[SP_1].draw(m_rectShape);
}






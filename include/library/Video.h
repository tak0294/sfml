#ifndef VIDEO_SYSTEM_H
#define VIDEO_SYSTEM_H
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include "library/Shader/Shader.h"
#include "library/Shader/ShaderScript.h"

const int BG_LAYER_NUM = 2;
const int SPRITE_LAYER_NUM = 1;
const int PIXEL_SHADER_NUM = 3;
const int VERTEX_SHADER_NUM = 3;
const int FONT_TYPE_NUM = 1;
const int DEFAULT_FONT_SIZE = 12;

/***************************************************************************************
 * Video Class.
 ***************************************************************************************/
class Video {

/***
 * enum
 */
public:
	enum ScrollDirection {
		DIRECTION_NONE = 0,
		DIRECTION_VERTICAL = 1,
		DIRECTION_HORIZONTAL = 2,
		DIRECTION_RIGHT_DOWN = 3,
		DIRECTION_LEFT_DOWN = 4,
	};
	enum BgLayer {
		BG_1 = 0, 
		BG_2 = 1,
		BG_3 = 2,
	};
	enum SpriteLayer {
		SP_1 = 0, 
		SP_2 = 1,
	};
	enum PixelShader {
		PS_NONE = 0,
		PS_RASTER = 1,
		PS_PIXELIZE = 2,
	};
	enum VertexShader {
		VS_NONE = 0,
		VS_WATER = 1,
	};
	enum BgTiledType {
		BG_TILED_BOTH = 0,
		BG_TILED_VERTICAL = 1,
		BG_TILED_HORIZONTAL = 2,
	};
	enum FontType {
		FONT_NORMAL = 0
	};

/**
 * private members.
 */
private:
	static int m_width;
	static int m_height;
	static sf::Vector2u m_bgSizes[BG_LAYER_NUM];
	static sf::Vector2i m_bgPositions[BG_LAYER_NUM];
	static ScrollDirection m_scrollDirections[BG_LAYER_NUM];
	static sf::RenderTexture m_bgLayers[BG_LAYER_NUM];
	static sf::RenderTexture m_spriteLayers[SPRITE_LAYER_NUM];
	static int m_bgScrollSpeeds[BG_LAYER_NUM];
	static Shader* m_bgShader[BG_LAYER_NUM];
	static Shader* m_spriteShader[SPRITE_LAYER_NUM];
	static ShaderScript* m_pixelShaderScripts[PIXEL_SHADER_NUM];
	static std::string m_vertexShaderScripts[VERTEX_SHADER_NUM];
	static sf::Font m_fonts[FONT_TYPE_NUM];
	//////////////////
	// Layer Sprite 
	//////////////////
	static sf::Sprite m_spSprites[SPRITE_LAYER_NUM];
	static sf::Sprite m_bgSprites[BG_LAYER_NUM];

    //////////////////
    // Shape ref.
    //////////////////
    static sf::RectangleShape m_rectShape;
    
    //////////////////
    // Bitmap Store.
    //////////////////
    static std::unordered_map<std::string, sf::Texture*> m_textureStore;

/**
 * public member.
 */
public:
	static void setupPixelShaderScripts();
	static void setupFonts();
	static void initialize(int, int);
	static void toggleFullScreen();
	static void tiledBgFromFile(BgLayer layer, std::string image_filename);
	static void tiledBgFromFile(BgLayer layer, std::string image_filename, BgTiledType tiledType, int offset);
	static void bgFromFile(BgLayer layer, std::string image_filename);
	static void bgFromFile(BgLayer layer, std::string image_filename, int x, int y);

	static void drawText(wchar_t *str, Video::FontType fontType, int x, int y);
	static void drawText(wchar_t *str, Video::FontType fontType, int x, int y, int size);
    
    ///////////////////////////////////////////////////////////////////
    // Load Texture.
    ///////////////////////////////////////////////////////////////////
    static sf::Texture* loadTexture(std::string filePath);
    
    ///////////////////////////////////////////////////////////////////
    // Mathmatic methods.
    ///////////////////////////////////////////////////////////////////
    static double calcBezierX(double t, double startX, double endX, double processX);
    static double calcBezierY(double t, double startY, double endY, double processY);
    static sf::Vector2<double> calcPerspectivePoint(double focus, double x, double y, double z);
    static double calcScaleFromZ(double focus, double z);
    
    ///////////////////////////////////////////////////////////////////
    //	Draw shapes
    ///////////////////////////////////////////////////////////////////
    static void drawRect(float x, float y, float width, float height, sf::Color fillColor, sf::Color borderColor);
    static void drawRect(float x, float y, float width, float height, sf::Color fillColor);
    static void drawRect(float x, float y, float width, float height);
    
	static void drawBg(sf::RenderWindow &window);
	static void clearBg(BgLayer layer);
	static void clearSpriteAll();
	static void scrollBg();
	static void setBgScrollDirection(BgLayer layer, ScrollDirection direction);
	static void setBgScrollSpeed(BgLayer layer, int speed);
	static void addBgPixelShader(BgLayer layer, PixelShader shaderType);
	static void addSpritePixelShader(SpriteLayer layer, PixelShader shaderType);
	static void drawSprite(SpriteLayer layer, sf::Drawable &sprite);
	static void flipSpriteToWindow(sf::RenderWindow &window);
	static sf::RenderWindow window;
	static sf::Clock videoClock;
};

#endif
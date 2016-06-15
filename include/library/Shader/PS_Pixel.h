#ifndef PS_PIXEL_H
#define PS_PIXEL_H

#include "library/Shader/ShaderScript.h"

class PS_Pixel : public ShaderScript {
public:
	void setShaderScript(){
	/////////////////////////////////////
	// Header.
	/////////////////////////////////////
	m_headerScript = "\
					  uniform float pixel_threshold;\
					  ";

	/////////////////////////////////////
	// Main.
	/////////////////////////////////////		  
	m_mainScript = "\
                    float factor = 1.0 / (pixel_threshold + 0.001); \
					pos.x = floor(pos.x * factor + 0.5) / factor; \
					pos.y = floor(pos.y * factor + 0.5) / factor;\
					";
	};
	

	void setShaderParams(sf::Shader &shader){
		shader.setParameter("pixel_threshold", 0.003);
	};

};

#endif

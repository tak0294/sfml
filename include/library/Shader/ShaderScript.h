#ifndef SHADER_SCRIPT_H
#define SHADER_SCRIPT_H

#include <SFML/Graphics.hpp>
#include <string>

class ShaderScript{

public:
	virtual void setShaderScript();
	virtual void setShaderParams(sf::Shader &shader);

	std::string m_mainScript;
	std::string m_headerScript;
};

#endif